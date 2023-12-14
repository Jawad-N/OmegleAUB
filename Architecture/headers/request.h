#pragma once

#include "includes.h"
#include "structures.h"

/**
 * @brief Base class for request
 *
 */
class request
{
private:
    int request_id;
    request_t req_type;
    string from;

public:
    static int counter;
    static vector<string> request_mapper;

    /**
     * @brief Construct a new request object
     *  Call is when you don't want to mess up the request_id
     *
     *
     */
    request();
    request(request_t req_type);
    request(const request &other);

    /**
     * @brief Getters and setters
     *
     *
     */

    int getrequestId() const;
    void setRequestId(int requestId);

    request_t getreqType() const;
    void setReqType(const request_t &reqType);

    string getFrom() const;
    void setFrom(const string &from_);

    friend ostream &operator<<(ostream &os, const request &req);
};

class request_connect : public request
{
private:
    string user_name;

public:
    // By default request_t : request_connect

    request_connect(string user_name);
    request_connect(const request &other);
    request_connect(const request_connect &other);
    request_connect();

    string getuserName() const;
    void setUserName(const string &userName);
    friend ostream &operator<<(ostream &os, const request_connect &req);
};
class request_list : public request
{
    // valid request_t : list_users | list_CR
public:
    request_list();
    request_list(const request &other);
    request_list(const request_list &other);
    request_list(request_t req_type);
    friend ostream &operator<<(ostream &os, const request_list &req);
};

class request_create_CR : public request
{
    // valid request_t : create_CR
private:
    chatroom_t chatroom;

public:
    request_create_CR();
    request_create_CR(const request &other);
    request_create_CR(const request_create_CR &other);
    request_create_CR(chatroom_t chatroom);

    chatroom_t getChatroom() const;
    void setChatroom(const chatroom_t &chatroom_);
    friend ostream &operator<<(ostream &os, const request_create_CR &req);
};

class request_JLD_CR : public request
{
    // valid request_t : join_CR , delete_CR , leave_CR
private:
    int chatroom_ID;

public:
    request_JLD_CR();
    request_JLD_CR(request_t req_type, int chatroom_ID);
    request_JLD_CR(const request &other, int chatroom_ID);
    request_JLD_CR(const request_JLD_CR &other);

    int getchatroomID() const;
    void setChatroomID(int chatroomID);
    friend ostream &operator<<(ostream &os, const request_JLD_CR &req);
};

class request_broadcast_message : public request
{
    // valid request_t : BROADCASE_MESSAGE
private:
    int chatroom_ID;
    message_t message;

public:
    request_broadcast_message();
    request_broadcast_message(int chatroom_ID, message_t message);
    request_broadcast_message(const request &other, int chatroom_ID, message_t message);
    request_broadcast_message(const request_broadcast_message &other);

    // request_broadcast_message(int chatroom_ID, message_t message);

    int getchatroomID() const { return chatroom_ID; }
    void setChatroomID(int chatroomID) { chatroom_ID = chatroomID; }

    message_t getMessage() const { return message; }
    void setMessage(const message_t &message_) { message = message_; }
    friend ostream &operator<<(ostream &os, const request_broadcast_message &req);
};

class request_private_message : public request
{
    // valid request_t : PRIVATE_MESSAGE
private:
    id user_id;
    message_t message;

public:
    request_private_message();
    request_private_message(id user_id, message_t message);
    request_private_message(const request &other, id user_id, message_t message);
    request_private_message(const request_private_message &other);

    // request_private_message(id user_id, message_t message);

    id getuserId() const { return user_id; }
    void setUserId(id userId) { user_id = userId; }

    message_t getMessage() const { return message; }
    void setMessage(const message_t &message_) { message = message_; }
    friend ostream &operator<<(ostream &os, const request_private_message &req);
};

class request_disconnect : public request
{
    // valid request_t : DISCONNECT
public:
    request_disconnect();
    request_disconnect(const request &other);
    request_disconnect(const request_disconnect &other);

    // request_disconnect();
    friend ostream &operator<<(ostream &os, const request_disconnect &req);
};

// request_connect , request_list,request_create_CR,request_JLD_CR,request_broadcast_message,request_private_message,request_disconnect
