#pragma once

#include "includes.h"
#include "structures.h"

/**
 * @brief Base class for reply
 *
 */
class reply
{
private:
    int reply_id;
    request_t rep_type;
    int status;
    string server_message;

public:
    reply();
    reply(request_t rep_type);
    reply(int reply_id, request_t rep_type, int status, string server_message);
    reply(const reply &other);

    /**
     * @brief Getters and setters
     *
     */

    int getreplyId() const;
    void setReplyId(int replyId);

    request_t getrepType() const;
    void setRepType(const request_t &repType);

    int getStatus() const;
    void setStatus(int status_);

    string getserverMessage() const;
    void setServerMessage(const string &serverMessage);

    friend ostream &operator<<(ostream &os, const reply &rep);
};

class reply_connect : public reply
{
public:
    reply_connect();
    reply_connect(int reply_id, int status, string server_message);
    reply_connect(const reply &other);
    reply_connect(const reply_connect &other);

    friend ostream &operator<<(ostream &os, const reply_connect &rep);
};

class reply_list_CR : public reply
{
private:
    vector<chatroom_t> chatrooms;

public:
    reply_list_CR();
    reply_list_CR(int reply_id, int status, string server_message, vector<chatroom_t> chatrooms);
    reply_list_CR(const reply &other, vector<chatroom_t> chatroom);
    reply_list_CR(const reply_list_CR &other);

    vector<chatroom_t> getChatrooms() const;
    void setChatrooms(const vector<chatroom_t> &chatrooms_);

    friend ostream &operator<<(ostream &os, const reply_list_CR &rep);
};

class reply_create_CR : public reply
{
private:
    chatroom_t chatroom;

public:
    reply_create_CR();
    reply_create_CR(int reply_id, int status, string server_message, chatroom_t chatroom);
    reply_create_CR(const reply &other, chatroom_t chatroom);
    reply_create_CR(const reply_create_CR &other);
    chatroom_t getChatroom() const;
    void setChatroom(const chatroom_t &chatroom);

    friend ostream &operator<<(ostream &os, const reply_create_CR &rep);
};

class reply_JLD_CR : public reply
{
    // join_CR leave_CR delete_CR
private:
    int chatroom_id;

public:
    reply_JLD_CR();
    reply_JLD_CR(request_t rep_type);
    reply_JLD_CR(int reply_id, request_t rep_type, int status, string server_message, int chatroom_id);
    reply_JLD_CR(const reply &other, int chatroom_id);
    reply_JLD_CR(const reply_JLD_CR &other);
    int getChatroomId() const;
    void setChatroomId(int chatroomId);

    friend ostream &operator<<(ostream &os, const reply_JLD_CR &rep);
};

class reply_broadcast_message : public reply
{
private:
    int chatroom_id;
    message_t message;

public:
    reply_broadcast_message();
    reply_broadcast_message(int reply_id, int status, string server_message, int chatroom_id, message_t message);
    reply_broadcast_message(const reply &other, int chatroom_id, message_t message);
    reply_broadcast_message(const reply_broadcast_message &other);

    int getChatroomId() const;
    void setChatroomId(int chatroomId);

    message_t getMessage() const;
    void setMessage(const message_t &message_);

    friend ostream &operator<<(ostream &os, const reply_broadcast_message &rep);
};

class reply_private_message : public reply
{
private:
    id user_id;
    message_t message;

public:
    reply_private_message();
    reply_private_message(int reply_id, int status, string server_message, id user_id, message_t message);
    reply_private_message(const reply &other, id user_id, message_t message);
    reply_private_message(const reply_private_message &other);

    id getuserId() const;
    void setUserId(const id &userId);

    message_t getMessage() const;
    void setMessage(const message_t &message_);

    friend ostream &operator<<(ostream &os, const reply_private_message &rep);
};

class reply_list_users : public reply
{
private:
    vector<id> users;

public:
    reply_list_users();
    reply_list_users(int reply_id, int status, string server_message, vector<id> users);
    reply_list_users(const reply &other, vector<id> users);
    reply_list_users(const reply_list_users &other);

    vector<id> getUsers() const;
    void setUsers(const vector<id> &users_);

    friend ostream &operator<<(ostream &os, const reply_list_users &rep);
};

class reply_disconnect : public reply
{
public:
    reply_disconnect();
    reply_disconnect(int reply_id, int status, string server_message);
    reply_disconnect(const reply &other);
    reply_disconnect(const reply_disconnect &other);

    friend ostream &operator<<(ostream &os, const reply_disconnect &rep);
};
