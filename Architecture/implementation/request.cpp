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
    if (other.getreqType() != list_users || other.getreqType() != list_CR)
        throw runtime_error("[server] : Error creating request_list from request constructor. reqtype incompatible");
}
request_list::request_list(const request_list &other) : request(other)
{
    if (other.getreqType() != list_users || other.getreqType() != list_CR)
        throw runtime_error("[server] : Error creating request_list from request_list constructor. reqtype incompatible");
}
request_list::request_list(request_t req_type) : request(req_type)
{
    if (req_type != list_users || req_type != list_CR)
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
    os << "Chatroom     : " << req.getChatroom() << '\n';
    return os;
}

// // // // // request_create_CR_end // // // // //