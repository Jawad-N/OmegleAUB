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

request_connect::request_connect(string user_name)
{
    setUserName(user_name);
    setReqType(connect_USR);
}
request_connect::request_connect()
{
    setUserName("");
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