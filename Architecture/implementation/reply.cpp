#include "../headers/reply.h"
#include "../headers/request.h"
// // // // Main reply class begin // // // //

reply::reply()
{
    setReplyId(-1);
    setRepType(connect_USR);
    setStatus(302);
    setServerMessage("");
}

reply::reply(request_t rep_type) : reply()
{
    setRepType(rep_type);
}
reply::reply(int reply_id, request_t rep_type, int status, string server_message)
{
    setReplyId(reply_id);
    setRepType(rep_type);
    setStatus(status);
    setServerMessage(server_message);
}

reply::reply(const reply &other)
{
    setReplyId(other.getreplyId());
    setRepType(other.getrepType());
    setStatus(other.getStatus());
    setServerMessage(other.getserverMessage());
}
int reply::getreplyId() const { return reply_id; }
void reply::setReplyId(int replyId) { reply_id = replyId; }

request_t reply::getrepType() const { return rep_type; }
void reply::setRepType(const request_t &repType) { rep_type = repType; }

int reply::getStatus() const { return status; }
void reply::setStatus(int status_) { status = status_; }

string reply::getserverMessage() const { return server_message; }
void reply::setServerMessage(const string &serverMessage) { this->server_message = string(serverMessage); }

ostream &operator<<(ostream &os, const reply &rep)
{
    os << "Reply   ID      : " << rep.getreplyId() << "\n";
    os << "Reply   type    : " << request::request_mapper[rep.getrepType()] << '\n';
    os << "Status code     : " << rep.getStatus() << '\n';
    os << "Server message  : " << rep.getserverMessage() << '\n';
    return os;
}
// // // // Main reply class end // // // //

// // // // Main reply_connect class begin // // // //
reply_connect::reply_connect() : reply(connect_CR) {}
reply_connect::reply_connect(int reply_id, int status, string server_message) : reply(reply_id, connect_CR, status, server_message)
{
}
reply_connect::reply_connect(const reply &other) : reply(other)
{
    if (other.getrepType() != connect_CR)
        throw runtime_error("[server] : error creating reply_connect. Invalid rep_type");
}
reply_connect::reply_connect(const reply_connect &other) : reply(other)
{
    if (other.getrepType() != connect_CR)
        throw runtime_error("[server] : error creating reply_connect. Invalid rep_type");
}
ostream &operator<<(ostream &os, const reply_connect &rep)
{
    os << static_cast<const reply &>(rep);
    return os;
}
// // // // Main reply_connect class end // // // //

// // // // Main reply_list_CR class begin // // // //

reply_list_CR::reply_list_CR() : reply(list_CR) {}
reply_list_CR::reply_list_CR(int reply_id, int status, string server_message, vector<chatroom_t> chatrooms) : reply(reply_id, list_CR, status, server_message)
{
    setChatrooms(vector<chatroom_t>(chatrooms));
}
reply_list_CR::reply_list_CR(const reply &other, vector<chatroom_t> chatrooms) : reply(other)
{
    if (other.getrepType() != list_CR)
        throw runtime_error("[server] : error creating reply_list_CR in reply constructor. Invalid rep_type");
    setChatrooms(vector<chatroom_t>(chatrooms));
}
reply_list_CR::reply_list_CR(const reply_list_CR &other) : reply(other)
{
    if (other.getrepType() != list_CR)
        throw runtime_error("[server] : error creating reply_list_CR in reply_list_CR constructor. Invalid rep_type");
    setChatrooms(vector<chatroom_t>(other.getChatrooms()));
}

vector<chatroom_t> reply_list_CR::getChatrooms() const { return vector<chatroom_t>(chatrooms); }
void reply_list_CR::setChatrooms(const vector<chatroom_t> &chatrooms_) { chatrooms = chatrooms_; }

ostream &operator<<(ostream &os, const reply_list_CR &rep)
{
    os << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
    os << static_cast<const reply &>(rep);
    os << "- - - - - - - - - - - - - - \n";
    os << "ChatRooms       : \n";

    for (chatroom_t &chatroom : rep.getChatrooms())
    {
        os << "- - - - - - - - \n";
        os << chatroom << '\n';
        os << "- - - - - - - - \n";
    }

    os << "- - - - - - - - - - - - - - \n";
    os << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
    return os;
}
// // // // Main reply_list_CR class end // // // //

// // // // Main reply_create_CR class start // // // //
reply_create_CR::reply_create_CR() : reply(create_CR)
{
}
reply_create_CR::reply_create_CR(int reply_id, int status, string server_message, chatroom_t chatroom) : reply(reply_id, create_CR, status, server_message)
{
    setChatroom(chatroom);
}
reply_create_CR::reply_create_CR(const reply &other, chatroom_t chatroom) : reply(other)
{
    if (other.getrepType() != create_CR)
        throw runtime_error("[server] : error creating reply_create_CR in reply constructor. Invalid rep_type");
    setChatroom(chatroom);
}
reply_create_CR::reply_create_CR(const reply_create_CR &other) : reply(other)
{
    if (other.getrepType() != create_CR)
        throw runtime_error("[server] : error creating reply_create_CR in reply constructor. Invalid rep_type");
    setChatroom(other.getChatroom());
}
chatroom_t reply_create_CR::getChatroom() const { return chatroom; }

void reply_create_CR::setChatroom(const chatroom_t &chatroom_) { chatroom = chatroom_t(chatroom_); }

ostream &operator<<(ostream &os, const reply_create_CR &rep)
{
    os << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
    os << static_cast<const reply &>(rep);
    os << "Chatroom        : \n"
       << rep.getChatroom() << '\n';
    os << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
    return os;
}
// // // // Main reply_reply_create_CR class end // // // //

// // // // Main reply_create_CR class start // // // //

reply_JLD_CR::reply_JLD_CR() : reply(leave_CR) {}
reply_JLD_CR::reply_JLD_CR(request_t rep_type) : reply(rep_type)
{
}
reply_JLD_CR::reply_JLD_CR(int reply_id, request_t rep_type, int status, string server_message, int chatroom_id) : reply(reply_id, rep_type, status, server_message)
{
    // if getType not valid throw runtime error
    if (rep_type != join_CR && rep_type != leave_CR && rep_type != delete_CR)
        throw runtime_error("[server] : error creating reply_JLD_CR in rep_type constructor. Invalid rep_type");
    setChatroomId(chatroom_id);
}
reply_JLD_CR::reply_JLD_CR(const reply &other, int chatroom_id) : reply(other)
{
    if (other.getrepType() != join_CR && other.getrepType() != leave_CR && other.getrepType() != delete_CR)
        throw runtime_error("[server] : error creating reply_JLD_CR in reply constructor. Invalid rep_type");
    setChatroomId(chatroom_id);
}
reply_JLD_CR::reply_JLD_CR(const reply_JLD_CR &other) : reply(other)
{
    if (other.getrepType() != join_CR && other.getrepType() != leave_CR && other.getrepType() != delete_CR)
        throw runtime_error("[server] : error creating reply_JLD_CR in reply_JLD_CR constructor. Invalid rep_type");

    setChatroomId(other.getChatroomId());
}
int reply_JLD_CR::getChatroomId() const { return chatroom_id; }
void reply_JLD_CR::setChatroomId(int chatroomId) { chatroom_id = chatroomId; }

ostream &operator<<(ostream &os, const reply_JLD_CR &rep)
{
    os << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
    os << static_cast<const reply &>(rep);
    os << "Chatroom id     : " << rep.getChatroomId() << '\n';
    os << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
    return os;
}

// // // // Main reply_reply_create_CR class end // // // //

// // // // Main reply_broadcast_message class start // // // //
reply_broadcast_message::reply_broadcast_message() : reply(BROADCAST_MESSAGE) {}
reply_broadcast_message::reply_broadcast_message(int reply_id, int status, string server_message, int chatroom_id, message_t message) : reply(reply_id, BROADCAST_MESSAGE, status, server_message)
{
    setChatroomId(chatroom_id);
    setMessage(message_t(message));
}
reply_broadcast_message::reply_broadcast_message(const reply &other, int chatroom_id, message_t message) : reply(other)
{
    if (other.getrepType() != BROADCAST_MESSAGE)
        throw runtime_error("[server] : error creating reply_JLD_CR in reply constructor. Invalid rep_type");
    setChatroomId(chatroom_id);
    setMessage(message_t(message));
}
reply_broadcast_message::reply_broadcast_message(const reply_broadcast_message &other) : reply(other)
{
    if (other.getrepType() != BROADCAST_MESSAGE)
        throw runtime_error("[server] : error creating reply_JLD_CR in reply constructor. Invalid rep_type");
    setChatroomId(other.getChatroomId());
    setMessage(message_t(other.getMessage()));
}

int reply_broadcast_message::getChatroomId() const { return chatroom_id; }
void reply_broadcast_message::setChatroomId(int chatroomId) { chatroom_id = chatroomId; }

message_t reply_broadcast_message::getMessage() const { return message; }
void reply_broadcast_message::setMessage(const message_t &message_) { message = message_; }

ostream &operator<<(ostream &os, const reply_broadcast_message &rep)
{
    os << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
    os << static_cast<const reply &>(rep);
    os << "Chatroom id     : " << rep.getChatroomId() << '\n';
    os << "- - - - - - - - - - - - - - \n";
    os << "Message         : \n";
    os << rep.getMessage() << '\n';
    os << "- - - - - - - - - - - - - - \n";
    os << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
    return os;
}
// // // // Main reply_broadcast_message class end // // // //

// // // // Main reply_private_message class start // // // //
reply_private_message::reply_private_message() : reply(PRIVATE_MESSAGE) {}
reply_private_message::reply_private_message(int reply_id, int status, string server_message, id user_id, message_t message) : reply(reply_id, PRIVATE_MESSAGE, status, server_message)
{
    setUserId(user_id);
    setMessage(message);
}
reply_private_message::reply_private_message(const reply &other, id user_id, message_t message) : reply(other)
{
    if (other.getrepType() != PRIVATE_MESSAGE)
        throw runtime_error("[server] : error creating reply_private_message in reply constructor. Invalid rep_type");
    setUserId(user_id);
    setMessage(message);
}
reply_private_message::reply_private_message(const reply_private_message &other) : reply(other)
{
    if (other.getrepType() != PRIVATE_MESSAGE)
        throw runtime_error("[server] : error creating reply_private_message in reply_private_message constructor. Invalid rep_type");

    setUserId(other.getuserId());
    setMessage(other.getMessage());
}

id reply_private_message::getuserId() const { return user_id; }
void reply_private_message::setUserId(const id &userId) { user_id = userId; }

message_t reply_private_message::getMessage() const { return message_t(message); }
void reply_private_message::setMessage(const message_t &message_) { message = message_t(message_); }

ostream &operator<<(ostream &os, const reply_private_message &rep)
{
    os << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
    os << static_cast<const reply &>(rep);
    os << "User     id     : " << rep.getreplyId() << '\n';
    os << "- - - - - - - - - - - - - - \n";
    os << "Message         : \n";
    os << rep.getMessage() << '\n';
    os << "- - - - - - - - - - - - - - \n";
    os << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
    return os;
}
// // // // Main reply_private_message class end // // // //

// // // // Main reply_list_users class start // // // //
reply_list_users::reply_list_users() : reply(list_users) {}
reply_list_users::reply_list_users(int reply_id, int status, string server_message, vector<id> users) : reply(reply_id, list_users, status, server_message)
{
    setUsers(vector<id>(users));
}
reply_list_users::reply_list_users(const reply &other, vector<id> users) : reply(other)
{

    if (other.getrepType() != list_users)
        throw runtime_error("[server] : error creating reply_list_users in reply constructor. Invalid rep_type");
    setUsers(vector<id>(users));
}
reply_list_users::reply_list_users(const reply_list_users &other) : reply(other)
{
    if (other.getrepType() != list_users)
        throw runtime_error("[server] : error creating reply_list_users in reply_list_users constructor. Invalid rep_type");
    setUsers(vector<id>(users));
}

vector<id> reply_list_users::getUsers() const { return users; }
void reply_list_users::setUsers(const vector<id> &users_) { users = users_; }

ostream &operator<<(ostream &os, const reply_list_users &rep)
{
    os << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
    os << static_cast<const reply &>(rep);
    os << "- - - - - - - - - - - - - - \n";
    os << "User     ids    : \n";
    for (id &user : rep.getUsers())
    {
        os << "- - - - - - - - \n";
        os << user << '\n';
        os << "- - - - - - - - \n";
    }
    os << "- - - - - - - - - - - - - - \n";

    os << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -";
    return os;
}
// // // // Main reply_list_users class end // // // //

// // // // Main reply_disconnect class start // // // //

reply_disconnect::reply_disconnect() : reply(DISCONNECT)
{
}
reply_disconnect::reply_disconnect(int reply_id, int status, string server_message) : reply(reply_id, DISCONNECT, status, server_message)
{
}
reply_disconnect::reply_disconnect(const reply &other) : reply(other)
{
    if (other.getrepType() != DISCONNECT)
        throw runtime_error("[server] : error creating reply_connect. Invalid rep_type");
}
reply_disconnect::reply_disconnect(const reply_disconnect &other) : reply(other)
{
    if (other.getrepType() != DISCONNECT)
        throw runtime_error("[server] : error creating reply_connect. Invalid rep_type");
}
ostream &operator<<(ostream &os, const reply_disconnect &rep)
{
    os << static_cast<const reply &>(rep);
    return os;
}

// // // // Main reply_disconnect end // // // //
