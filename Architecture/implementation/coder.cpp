#include "../headers/coder.h"
#include "../headers/request.h"

char coder::sep = '\u001F'; // non-printable characters
char coder::sep_req_repl = '\u0009';
char coder::sep_req_repl_main = '\u0006';
string coder::encode_chatroom_t(chatroom_t chatroom, bool req_or_repl)
{
    // to_add from time_t to time
    // request encoding : id sep capacity sep created sep name sep description
    // reply encoding   : id sep capacity sep  size sep created sep name sep description
    string extra = "";
    if (req_or_repl)
        extra = coder::sep + to_string((int)chatroom.getMembers().size());

    return to_string(chatroom.getchatroomID()) + coder::sep + to_string(chatroom.getCapacity()) + extra + coder::sep + to_string(chatroom.getCreated()) + coder::sep + chatroom.getName() + coder::sep + chatroom.getDescription() + coder::sep;
}

chatroom_t coder::decode_chatroom_t(string chatroom_str, bool req_or_repl)
{

    // request encoding : capacity sep created sep name sep description
    // reply encoding   : capacity sep  size sep created sep name sep description
    // stoi(string) -> integer try accept
    vector<string> content = split(chatroom_str, coder::sep);
    if (content.size() > 6 || content.size() < 5)
        throw runtime_error("[server] : invalid encoding for chatroom_t");
    if (content.size() == 6 && !req_or_repl)
        throw runtime_error("[server] : invalid encoding for chatroom_t. Expected reply decoding instead of request ");
    if (content.size() == 5 && req_or_repl)
        throw runtime_error("[server] : invalid encoding for chatroom_t. Expected request decoding instead of reply ");
    chatroom_t chatroom;

    int offset = 1;
    chatroom.setChatroomID(stoi(content[0]));
    chatroom.setCapacity(stoi(content[1]));

    if (req_or_repl)
    {
        offset = 2;
    }
    chatroom.setCreated((time_t)stoi(content[1 + offset]));
    chatroom.setName(content[2 + offset]);
    chatroom.setDescription(content[3 + offset]);

    return chatroom;
}

string coder::encode_chatroom_t(chatroom_t chatroom)
{
    // encoding : id sep capacity sep size sep owner sep created sep [ member_1,member_2,…, member_n ] sep name sep description
    // forbidden , in naming
    string members_encoding = "";
    set<id> members = chatroom.getMembers();
    set<id>::iterator itr = members.begin();
    for (; itr != members.end(); itr++)
    {
        members_encoding += (*itr);
        if (next(itr) != members.end())
            members_encoding += ',';
    }
    // members_encoding += "]";
    return to_string(chatroom.getchatroomID()) + coder::sep + to_string(chatroom.getCapacity()) + coder::sep + to_string((int)chatroom.getMembers().size()) + coder::sep +
           chatroom.getOwner() + coder::sep + to_string(chatroom.getCreated()) + coder::sep + members_encoding + coder::sep +
           chatroom.getName() + coder::sep + chatroom.getDescription() + coder::sep;
}

chatroom_t coder::decode_chatroom_t(string chatroom_str)
{

    // encoding :  id sep capacity sep size sep owner sep created sep  member_1,member_2,…, member_n  sep name sep description
    // forbidden , in naming
    vector<string> content = split(chatroom_str, coder::sep);
    if (content.size() != 8)
        throw runtime_error("[server] :  invalid encoding for main chatroom_t.");
    chatroom_t chatroom;
    vector<string> members = split(content[5], ',');

    chatroom.setCapacity(stoi(content[1]));
    chatroom.setChatroomID(stoi(content[0]));

    chatroom.setOwner(content[3]);
    chatroom.setCreated(stoi(content[4]));
    chatroom.setName(content[6]);
    chatroom.setDescription(content[7]);

    for (string member : members)
        chatroom.add_member(member);

    return chatroom;
    // Continue from here.
}

string coder::encode_message_t(message_t message)
{
    // Encoding scheme: sender sep created sep content
    // return

    return message.getSender() + coder::sep + to_string(message.getCreated()) + coder::sep + message.getContent() + coder::sep;
}

message_t coder::decode_message_t(string message_t_str)
{

    // Encoding scheme: sender sep created sep content
    vector<string> content = split(message_t_str, coder::sep);
    if (content.size() != 3)
        throw runtime_error("[server] :  invalid encoding for message_t. Message : " + message_t_str);
    message_t message;
    message.setSender(content[0]);
    message.setCreated(stoi(content[1]));
    message.setContent(content[2]);
    return message;
}

string coder::encode_request(request req)
{
    // Encoding scheme : req_type sep_req_repl_main request_id sep_req_repl_main from
    return to_string(req.getreqType()) + coder::sep_req_repl_main +
           to_string(req.getrequestId()) + coder::sep_req_repl_main + req.getFrom() + coder::sep_req_repl_main;
}

request coder::decode_request(string req_str)
{
    // Encoding scheme : req_type sep_req_repl_main request_id sep_req_repl_main from
    vector<string> content = split(req_str, coder::sep_req_repl_main);
    // cout << content.size() << '\n';
    if (content.size() != 3)
        throw runtime_error("[server] :  invalid encoding for request. Request : " + req_str);
    request req;
    req.setReqType((request_t)stoi(content[0]));
    req.setRequestId(stoi(content[1]));
    req.setFrom(content[2]);
    return req;
}

string coder::encode_request_connect(request_connect req)
{
    // encode_request(req) sep_req_repl user_name sep_req_repl
    return coder::encode_request(req) + coder::sep_req_repl + req.getuserName() + coder::sep_req_repl;
}

request_connect coder::decode_request_connect(string req_str)
{
    // encode_request(req) sep_req_repl user_name sep_req_repl
    vector<string> content = split(req_str, coder::sep_req_repl);
    // cout << content.size() << '\n';
    if (content.size() != 2)
        throw runtime_error("[server] :  invalid encoding for request_connect. Request : " + req_str);
    // Add try catch blocks for each one
    request main_req = coder::decode_request(content[0]);
    request_connect req(main_req);
    req.setUserName(content[1]);
    return req;
}

string coder::encode_request_list(request_list req)
{
    // encoding scheme : encode_request(req)
    return coder::encode_request(req);
}

request_list coder::decode_request_list(string req_str)
{
    request main_req = coder::decode_request(req_str);
    return request_list(main_req);
}

string coder::encode_request_create_CR(request_create_CR req)
{
    // Encoding scheme : request sep_req_repl encode_chatroom_t_request(chatroom) sep_req_repl
    return coder::encode_request(req) + coder::sep_req_repl + coder::encode_chatroom_t(req.getChatroom(), false) + coder::sep_req_repl;
}
request_create_CR coder::decode_request_create_CR(string req_str)
{
    vector<string> content = split(req_str, coder::sep_req_repl);
    if (content.size() != 2)
        throw runtime_error("[server] :  invalid encoding for request_create_CR. Request : " + req_str);
    // Encoding scheme : request sep_req_repl encode_chatroom_t_request(chatroom) sep_req_repl
    request main_req = coder::decode_request(content[0]);
    request_create_CR req(main_req);
    chatroom_t chatroom = coder::decode_chatroom_t(content[1], false);
    req.setChatroom(chatroom);
    return req;
}

string coder::encode_request_JLD_CR(request_JLD_CR req)
{
    // Encoding scheme : request sep_req_repl chatroom_id sep_req_repl
    return coder::encode_request(req) + coder::sep_req_repl + to_string(req.getchatroomID()) + coder::sep_req_repl;
}
request_JLD_CR coder::decode_request_JLD_CR(string req_str)
{
    vector<string> content = split(req_str, coder::sep_req_repl);
    if (content.size() != 2)
        throw runtime_error("[server] :  invalid encoding for request_JLD_CR. Request : " + req_str);
    // Try except
    // Realisation : incosistency in classes reperesentation.
    request main_req = coder::decode_request(content[0]);
    int chatroom_id = stoi(content[1]);
    request_JLD_CR req(main_req, chatroom_id);
    return req;
}

string coder::encode_request_broadcast_message(request_broadcast_message req)
{
    // request sep_req_repl chatroom_id sep_req_repl encode_message_t(message) sep_req_repl
    return coder::encode_request(req) + coder::sep_req_repl + to_string(req.getchatroomID()) +
           coder::sep_req_repl + coder::encode_message_t(req.getMessage()) + coder::sep_req_repl;
}
request_broadcast_message coder::decode_request_broadcast_message(string req_str)
{
    vector<string> content = split(req_str, coder::sep_req_repl);
    if (content.size() != 3)
        throw runtime_error("[server] :  invalid encoding for request_broadcast_message. Request : " + req_str);

    // Try except
    request main_req = coder::decode_request(content[0]);
    int chatroom_id = stoi(content[1]);
    message_t message = coder::decode_message_t(content[2]);
    return request_broadcast_message(main_req, chatroom_id, message);
}

string coder::encode_request_private_message(request_private_message req)
{
    // request sep_req_repl user_id sep_req_repl encode_message_t(message) sep_req_repl

    return coder::encode_request(req) + coder::sep_req_repl + req.getuserId() +
           coder::sep_req_repl + coder::encode_message_t(req.getMessage()) + coder::sep_req_repl;
}
request_private_message coder::decode_request_private_message(string req_str)
{
    vector<string> content = split(req_str, coder::sep_req_repl);
    if (content.size() != 3)
        throw runtime_error("[server] :  invalid encoding for request_private_message. Request : " + req_str);

    // Try except
    request main_req = coder::decode_request(content[0]);
    id user_id = content[1];
    message_t message = coder::decode_message_t(content[2]);
    return request_private_message(main_req, user_id, message);
}

// // // // // // Coder (reply's version) // // // // // //

string coder::encode_reply(reply rep)
{
    // encoding scheme: rep_type sep_req_repl_main reply_id sep_req_repl_main status sep_req_repl_main server_message sep_req_repl_main
    return to_string((int)rep.getrepType()) + coder::sep_req_repl_main + to_string(rep.getreplyId()) + coder::sep_req_repl_main +
           to_string(rep.getStatus()) + coder::sep_req_repl_main + rep.getserverMessage() + coder::sep_req_repl_main;
}

reply coder::decode_reply(string rep_str)
{
    vector<string> content = split(rep_str, coder::sep_req_repl_main);
    if (content.size() != 4)
        throw runtime_error("[server] : invalid reply encoding. Encoding: " + rep_str);
    reply main_reply;
    // add try catch blocks
    main_reply.setRepType((request_t)stoi(content[0]));
    main_reply.setReplyId(stoi(content[1]));
    main_reply.setStatus(stoi(content[2]));
    main_reply.setServerMessage(content[3]);

    return main_reply;
}

string coder::encode_reply_connect(reply_connect rep)
{
    // encoding scheme : reply
    return encode_reply(rep);
}
reply_connect coder::decode_reply_connect(string rep_str)
{
    reply main_reply = decode_reply(rep_str);
    return reply_connect(main_reply);
}

string coder::encode_reply_disconnect(reply_disconnect rep)
{
    // encoding scheme : reply
    return encode_reply(rep);
}
reply_disconnect coder::decode_reply_disconnect(string rep_str)
{
    reply main_reply = decode_reply(rep_str);
    return reply_connect(main_reply);
}

string coder::encode_reply_list_CR(reply_list_CR rep)
{
    // encoding scheme : reply sep_req_repl item1 sep_req_repl item2 sep_req_repl item3 sep_req_repl … sep_req_repl itemK sep_req_repl
    string chatrooms_encoding = "";
    vector<chatroom_t> chatrooms = rep.getChatrooms();
    vector<string> chatrooms_encodings(chatrooms.size(), " ");
    for (int i = 0; i < chatrooms.size(); i++)
    {
        chatrooms_encodings[i] = coder::encode_chatroom_t(chatrooms[i]);
        cout << chatrooms_encodings[i] << '\n';
        chatrooms_encoding += chatrooms_encodings[i];
        if (i + 1 == chatrooms.size())
            break;
        chatrooms_encoding += coder::sep_req_repl;
    }
    // cout << "\n EncodingReply: " << coder::encode_reply(rep) << '\n';
    // string encodingS = coder::encode_reply(rep) + coder::sep_req_repl + chatrooms_encoding + coder::sep_req_repl;
    // vector<string> OKAY = split(encodingS, coder::sep_req_repl);
    // cout << OKAY.size() << '\n';
    // cout.flush();
    // cout << "decoding of encoding: " << coder::decode_reply(OKAY[0]) << '\n';
    return coder::encode_reply(rep) + coder::sep_req_repl + chatrooms_encoding + coder::sep_req_repl;
}
reply_list_CR coder::decode_reply_list_CR(string rep_str)
{
    vector<string> content = split(rep_str, coder::sep_req_repl);
    if (content.size() < 1)
        throw runtime_error("[server] : invalid reply_list_CR encoding. Encoding: " + rep_str);

    reply main_reply = coder::decode_reply(content[0]);
    vector<chatroom_t> chatrooms;
    for (size_t index = 1; index < content.size(); index++)
    {
        chatrooms.emplace_back(coder::decode_chatroom_t(content[index]));
    }
    reply_list_CR rep(main_reply, chatrooms);
    // add try catch block
    return rep;
}

string coder::encode_reply_create_CR(reply_create_CR rep)
{
    // reply sep_req_repl chatroom sep_req_repl
    return coder::encode_reply(rep) + coder::sep_req_repl + coder::encode_chatroom_t(rep.getChatroom()) + coder::sep_req_repl;
}
reply_create_CR coder::decode_reply_create_CR(string rep_str)
{
    vector<string> content = split(rep_str, coder::sep_req_repl);
    if (content.size() != 2)
        throw runtime_error("[server] : invalid reply_create_CR encoding. Encoding: " + rep_str);
    reply main_reply = coder::decode_reply(content[0]);
    chatroom_t chatroom = coder::decode_chatroom_t(content[1]);
    return reply_create_CR(main_reply, chatroom);
}

string coder::encode_reply_JLD_CR(reply_JLD_CR rep)
{
    // reply sep_req_repl chatroom_id sep_req_repl
    return coder::encode_reply(rep) + coder::sep_req_repl + to_string(rep.getChatroomId()) + coder::sep_req_repl;
}
reply_JLD_CR coder::decode_reply_JLD_CR(string rep_str)
{
    vector<string> content = split(rep_str, coder::sep_req_repl);
    if (content.size() != 2)
        throw runtime_error("[server] : invalid reply_JLD_CR encoding. Encoding: " + rep_str);
    reply main_reply = coder::decode_reply(content[0]);
    int chatroom_id = stoi(content[1]);
    return reply_JLD_CR(main_reply, chatroom_id);
}

string coder::encode_reply_broadcast_message(reply_broadcast_message rep)
{
    // reply sep_req_repl chatroom_id sep_req_repl encode_message_t(message) sep_req_repl
    return coder::encode_reply(rep) + coder::sep_req_repl + to_string(rep.getChatroomId()) + coder::sep_req_repl + coder::encode_message_t(rep.getMessage()) + coder::sep_req_repl;
}
reply_broadcast_message coder::decode_reply_broadcast_message(string rep_str)
{
    vector<string> content = split(rep_str, coder::sep_req_repl);
    if (content.size() != 3)
        throw runtime_error("[server] : invalid reply_broadcast_message encoding. Encoding: " + rep_str);

    reply main_reply = coder::decode_reply(content[0]);
    int chatroom_id = stoi(content[1]);
    message_t message = coder::decode_message_t(content[2]);
    return reply_broadcast_message(main_reply, chatroom_id, message);
}

string coder::encode_reply_private_message(reply_private_message rep)
{
    // reply sep_req_repl user_id sep_req_repl encode_message_t(message) sep_req_repl
    return coder::encode_reply(rep) + coder::sep_req_repl + rep.getuserId() + coder::sep_req_repl + coder::encode_message_t(rep.getMessage()) + coder::sep_req_repl;
}
reply_private_message coder::decode_reply_private_message(string rep_str)
{
    vector<string> content = split(rep_str, coder::sep_req_repl);
    if (content.size() != 3)
        throw runtime_error("[server] : invalid reply_broadcast_message encoding. Encoding: " + rep_str);

    reply main_reply = coder::decode_reply(content[0]);
    id user_id = content[1];
    message_t message = coder::decode_message_t(content[2]);

    return reply_private_message(main_reply, user_id, message);
}

string coder::encode_reply_list_users(reply_list_users rep)
{
    string users_encoding = "";
    vector<id> usrs = rep.getUsers();
    for (size_t index = 1; index < usrs.size(); index++)
    {
        users_encoding += usrs[index];
        if (index + 1 != usrs.size())
            users_encoding += coder::sep_req_repl;
    }
    return coder::encode_reply(rep) + coder::sep_req_repl + users_encoding + coder::sep_req_repl;
}
reply_list_users coder::decode_reply_list_users(string rep_str)
{
    vector<string> content = split(rep_str, coder::sep_req_repl);
    if (content.size() < 1)
        throw runtime_error("[server] : invalid reply_list_CR encoding. Encoding: " + rep_str);
    reply main_reply = coder::decode_reply(content[0]);
    vector<id> users;
    for (size_t index = 1; index < content.size(); index++)
    {
        users.emplace_back(content[index]);
    }
    reply_list_users rep(main_reply, users);
    // add try catch blocks

    return rep;
}

string coder::encode_request_disconnect(request_disconnect req)
{
    return coder::encode_request(req);
}
request_disconnect coder::decode_request_disconnect(string req_str)
{
    return request_disconnect(coder::decode_request(req_str));
}
// // // // // Coder (reply's version) end // // // // // //

// // // // // main_encoding_decoding_start // // // // // //

request_t coder::get_encode_request_type(string req_str)
{
    vector<string> content = split(req_str, coder::sep_req_repl);
    if (content.size() == 0)
        throw runtime_error("[server] : invalid req_str encoding inside get_encode_request_type");
    request main_req = coder::decode_request(content[0]);
    return main_req.getreqType();
}
request_t coder::get_encode_reply_type(string rep_str)
{
    vector<string> content = split(rep_str, coder::sep_req_repl);
    if (content.size() == 0)
        throw runtime_error("[server] : invalid req_str encoding inside get_encode_request_type");
    reply main_rep = coder::decode_reply(content[0]);
    return main_rep.getrepType();
}

string coder::get_request_t_str(request req)
{
    return request::request_mapper[req.getreqType()];
}
string coder::get_request_t_str(reply rep)
{
    return request::request_mapper[rep.getrepType()];
}
string coder::get_request_t_str(request_t req_type)
{
    return request::request_mapper[req_type];
}
// string coder::main_encode_request(request req)
// {
//     switch (req.getreqType())
//     {
//     case connect_CR:
//         return encode_request(req);
//         break;
//     case list_CR:
//         return encode_request_list((request_list)req);
//         // Handle list_CR
//         break;
//     case create_CR:
//         return encode_request_create_CR((request_create_CR)req);
//         // Handle create_CR
//         break;
//     case join_CR:

//         // Handle join_CR
//         return encode_request_JLD_CR((request_JLD_CR)req);
//         break;
//     case leave_CR:
//         // Handle leave_CR
//         return encode_request_JLD_CR((request_JLD_CR)req);
//         break;
//     case delete_CR:
//         // Handle delete_CR
//         return encode_request_JLD_CR((request_JLD_CR)req);
//         break;
//     case BROADCAST_MESSAGE:
//         // Handle BROADCAST_MESSAGE
//         return encode_request_broadcast_message((request_broadcast_message)req);
//         break;
//     case list_users:
//         // Handle list_users
//         return encode_request_list((request_list)req);
//         break;
//     case PRIVATE_MESSAGE:

//         // Handle PRIVATE_MESSAGE
//         return encode_request_private_message((request_private_message)req);
//         break;
//     case DISCONNECT:
//         // Handle DISCONNECT
//         // Add request disconnect
//         return "";
//         break;
//     case connect_USR:
//         // Handle connect_USR
//         // return encode_req //
//         return encode_request_connect((request_connect)req);
//         break;
//     default:
//         // Handle invalid request type
//         break;
//     }
//     throw runtime_error("[server] : error encoding request");
//     return "ERROR";
// }
// request coder::main_decode_request(string req_str);

// string coder::main_encode_reply(reply rep);
// reply coder::main_decode_reply(string rep_str);
// // // // // main_encoding_decoding_end // // // // // //