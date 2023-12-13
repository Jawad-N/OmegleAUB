#include "../headers/coder.h"

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

    return to_string(chatroom.getchatroomID()) + coder::sep + to_string(chatroom.getCapacity()) + extra + coder::sep + to_string(chatroom.getCreated()) + coder::sep + chatroom.getName() + coder::sep + chatroom.getDescription();
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
           chatroom.getName() + coder::sep + chatroom.getDescription();
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

    return message.getSender() + coder::sep + to_string(message.getCreated()) + coder::sep + message.getContent();
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
