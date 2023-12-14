#include "../headers/includes.h"
#include "../headers/request.h"
int request::counter = 0;

vector<string> request::request_mapper{"connect_CR",
                                       "list_CR",
                                       "create_CR",
                                       "join_CR",
                                       "leave_CR",
                                       "delete_CR",
                                       "BROADCAST_MESSAGE",
                                       "list_users",
                                       "PRIVATE_MESSAGE",
                                       "DISCONNECT",
                                       "connect_USR"};

request::request()
{
    this->req_type = connect_CR;
    this->request_id = -1;
    this->from = "";
}

request::request(request_t req_type)
{
    request::counter++;
    this->req_type = req_type;
    this->request_id = counter;
    this->from = "";
}

request::request(const request &other)
{
    this->req_type = other.getreqType();
    this->request_id = other.getrequestId();
    this->from = other.getFrom();
}

int request::getrequestId() const { return request_id; }
void request::setRequestId(int requestId) { request_id = requestId; }

request_t request::getreqType() const { return req_type; }
void request::setReqType(const request_t &reqType) { req_type = reqType; }

string request::getFrom() const { return from; }
void request::setFrom(const string &from_) { from = from_; }

ostream &operator<<(ostream &os, const request &req)
{
    os << "Request ID   : " << req.getrequestId() << "\n";
    os << "Request type : " << request::request_mapper[req.getreqType()] << '\n';
    os << "From         : " << req.getFrom() << '\n';
    return os;
}

// request_connect_start

request_connect::request_connect(string user_name) : request(connect_USR)
{
    setUserName(user_name);
}
request_connect::request_connect() : request()
{
    setUserName("");
}

request_connect::request_connect(const request &other) : request(other)
{
    setUserName("");
}

request_connect::request_connect(const request_connect &other) : request(other)
{
    setUserName(other.getuserName());
}

string request_connect::getuserName() const { return user_name; }
void request_connect::setUserName(const string &userName) { user_name = userName; }
ostream &operator<<(ostream &os, const request_connect &req)
{
    os << static_cast<const request &>(req);
    os << "Username     : " << req.getuserName() << '\n';
    return os;
}

// request_connect_end

// request_list,request_create_CR,request_JLD_CR,request_broadcast_message,request_private_message,request_disconnect

// // // // // request_list_start // // // // //
request_list::request_list() : request(list_CR) {}
request_list::request_list(const request &other) : request(other)
{
    if (other.getreqType() != list_users && other.getreqType() != list_CR)
        throw runtime_error("[server] : Error creating request_list from request constructor. reqtype incompatible");
}
request_list::request_list(const request_list &other) : request(other)
{
    if (other.getreqType() != list_users && other.getreqType() != list_CR)
        throw runtime_error("[server] : Error creating request_list from request_list constructor. reqtype incompatible");
}
request_list::request_list(request_t req_type) : request(req_type)
{
    if (req_type != list_users && req_type != list_CR)
        throw runtime_error("[server] : Error creating request_list from request_t constructor. reqtype incompatible");
}
ostream &operator<<(ostream &os, const request_list &req)
{
    os << static_cast<const request &>(req);
    return os;
}
// // // // // request_list_end // // // // //

// // // // // request_create_CR_start // // // // //

request_create_CR::request_create_CR() : request(create_CR)
{
}
request_create_CR::request_create_CR(const request &other) : request(other)
{
    if (other.getreqType() != create_CR)
        throw runtime_error("[server] : Error creating request_create_CR from request constructor. reqtype incompatible");
}
request_create_CR::request_create_CR(const request_create_CR &other) : request(other)
{
    if (other.getreqType() != create_CR)
        throw runtime_error("[server] : Error creating request_create_CR from request constructor. reqtype incompatible");

    // Add copy constructor for chatroom
    setChatroom(other.getChatroom());
}
request_create_CR::request_create_CR(chatroom_t chatroom) : request(create_CR)
{
    setChatroom(chatroom);
}

chatroom_t request_create_CR::getChatroom() const { return chatroom; }
void request_create_CR::setChatroom(const chatroom_t &chatroom_) { chatroom = chatroom_; }
ostream &operator<<(ostream &os, const request_create_CR &req)
{
    os << static_cast<const request &>(req);
    os << "Chatroom     : \n";
    os << "- - - - - - - - - - - - -\n";
    os << req.getChatroom() << '\n';
    os << "- - - - - - - - - - - - -\n";
    return os;
}

// // // // // request_create_CR_end // // // // //

// // // // // request_create_CR_start // // // // //
request_JLD_CR::request_JLD_CR() : request()
{
    setReqType(leave_CR);
}

request_JLD_CR::request_JLD_CR(request_t req_type, int chatroom_ID) : request(req_type)
{
    // if
    if (req_type != join_CR && req_type != leave_CR && req_type != delete_CR)
        throw runtime_error("[server] : Error creating request_JLD_CR from request_t constructor. reqtype incompatible");
    setChatroomID(chatroom_ID);
}
request_JLD_CR::request_JLD_CR(const request &other, int chatroom_ID) : request(other)
{
    if (other.getreqType() != join_CR && other.getreqType() != leave_CR && other.getreqType() != delete_CR)
        throw runtime_error("[server] : Error creating request_JLD_CR from request constructor. reqtype incompatible");
    setChatroomID(chatroom_ID);
}
request_JLD_CR::request_JLD_CR(const request_JLD_CR &other) : request(other)
{
    if (other.getreqType() != join_CR && other.getreqType() != leave_CR && other.getreqType() != delete_CR)
        throw runtime_error("[server] : Error creating request_JLD_CR from request_JLD_CR constructor. reqtype incompatible");
    setChatroomID(other.getchatroomID());
}

int request_JLD_CR::getchatroomID() const { return chatroom_ID; }
void request_JLD_CR::setChatroomID(int chatroomID) { chatroom_ID = chatroomID; }
ostream &operator<<(ostream &os, const request_JLD_CR &req)
{
    os << static_cast<const request &>(req);
    os << "Chatroom ID  : " << req.getchatroomID() << '\n';
    return os;
}
// // // // // request_create_CR_end // // // // //
// // // // // request_broadcast_message_start // // // // //
request_broadcast_message::request_broadcast_message() : request()
{
    setReqType(BROADCAST_MESSAGE);
}
request_broadcast_message::request_broadcast_message(int chatroom_ID, message_t message) : request(BROADCAST_MESSAGE)
{

    setChatroomID(chatroom_ID);
    setMessage(message);
}
request_broadcast_message::request_broadcast_message(const request &other, int chatroom_ID, message_t message) : request(other)
{

    if (other.getreqType() != BROADCAST_MESSAGE)
        throw runtime_error("[server] : Error creating request_broadcast_message from request constructor. reqtype incompatible");
    setChatroomID(chatroom_ID);
    setMessage(message);
}
request_broadcast_message::request_broadcast_message(const request_broadcast_message &other) : request(other)
{
    if (other.getreqType() != BROADCAST_MESSAGE)
        throw runtime_error("[server] : Error creating request_broadcast_message from request constructor. reqtype incompatible");
    setChatroomID(other.getchatroomID());
    setMessage(other.getMessage());
}

// request_broadcast_message(int chatroom_ID, message_t message);

int request_broadcast_message::getchatroomID() const { return chatroom_ID; }
void request_broadcast_message::setChatroomID(int chatroomID) { chatroom_ID = chatroomID; }

message_t request_broadcast_message::getMessage() const { return message; }
void request_broadcast_message::setMessage(const message_t &message_) { message = message_t(message_); }
ostream &operator<<(ostream &os, const request_broadcast_message &req)
{
    os << static_cast<const request &>(req);
    os << "Chatroom id     : " << req.getchatroomID() << '\n';
    os << "- - - - - - - - - - - - - - \n";
    os << "Message         : \n";
    os << req.getMessage() << '\n';
    os << "- - - - - - - - - - - - - - \n";
    return os;
}
// // // // // request_broadcast_message_end // // // // //

// // // // // request_private_message_start // // // // //
request_private_message::request_private_message() : request() { setReqType(PRIVATE_MESSAGE); }
request_private_message::request_private_message(id user_id, message_t message) : request(PRIVATE_MESSAGE)
{
    setUserId(user_id);
    setMessage(message);
}
request_private_message::request_private_message(const request &other, id user_id, message_t message) : request(other)
{
    if (other.getreqType() != PRIVATE_MESSAGE)
        throw runtime_error("[server] : Error creating request_private_message from request constructor. reqtype incompatible");
    setUserId(user_id);
    setMessage(message);
}
request_private_message::request_private_message(const request_private_message &other) : request(other)
{
    if (other.getreqType() != PRIVATE_MESSAGE)
        throw runtime_error("[server] : Error creating request_private_message from request constructor. reqtype incompatible");
    setUserId(other.getuserId());
    setMessage(other.getMessage());
}

// request_private_message(id user_id, message_t message);

id request_private_message::getuserId() const { return user_id; }
void request_private_message::setUserId(id userId) { user_id = userId; }

message_t request_private_message::getMessage() const { return message; }
void request_private_message::setMessage(const message_t &message_) { message = message_t(message_); }
ostream &operator<<(ostream &os, const request_private_message &req)
{
    os << static_cast<const request &>(req);
    os << "Chatroom id     : " << req.getuserId() << '\n';
    os << "- - - - - - - - - - - - - - \n";
    os << "Message         : \n";
    os << req.getMessage() << '\n';
    os << "- - - - - - - - - - - - - - \n";
    return os;
}
// // // // // request_private_message_end // // // // //
// // // // // request_disconnect_start // // // // //
request_disconnect::request_disconnect() : request() { setReqType(DISCONNECT); };
request_disconnect::request_disconnect(const request &other) : request(other)
{
    if (other.getreqType() != DISCONNECT)
        throw runtime_error("[server] : Error creating request_disconnect from request constructor. reqtype incompatible");
}
request_disconnect::request_disconnect(const request_disconnect &other) : request(other)
{
    if (other.getreqType() != DISCONNECT)
        throw runtime_error("[server] : Error creating request_disconnect from request constructor. reqtype incompatible");
}

// request_disconnect();
ostream &operator<<(ostream &os, const request_disconnect &req)
{
    os << static_cast<const request &>(req);
    return os;
}
// // // // // request_disconnect_end // // // // //