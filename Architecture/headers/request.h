#pragma once

#include "includes.h"

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

    request();
    request(request_t req_type);

    /**
     * @brief Getters and setters
     *
     *
     */

    int requestId() const { return request_id; }
    void setRequestId(int requestId) { request_id = requestId; }

    request_t reqType() const { return req_type; }
    void setReqType(const request_t &reqType) { req_type = reqType; }

    string getFrom() const { return from; }
    void setFrom(const string &from_) { from = from_; }
};

class request_connect : public request
{
private:
    string user_name;

public:
    // By default request_t : request_connect

    request_connect(string user_name);

    string userName() const { return user_name; }
    void setUserName(const string &userName) { user_name = userName; }
};

class request_list : public request
{
    // valid request_t : list_users | list_CR
    request_ public : request_list(request_t req_type);
};

class request_create_CR : public request
{
    // valid request_t : create_CR

private:
    chatroom_t chatroom;

public:
    request_create_CR(chatroom_t chatroom);

    chatroom_t getChatroom() const { return chatroom; }
    void setChatroom(const chatroom_t &chatroom_) { chatroom = chatroom_; }
};

class request_JLD_CR : public request
{
    // valid request_t : join_CR , delete_CR , leave_CR
private:
    int chatroom_ID;

public:
    request_JLD_CR(request_t req_type, int chatroom_ID);

    int chatroomID() const { return chatroom_ID; }
    void setChatroomID(int chatroomID) { chatroom_ID = chatroomID; }
};

class request_broadcast_message : public request
{
    // valid request_t : BROADCASE_MESSAGE
private:
    int chatroom_ID;
    message_t message;

public:
    request_broadcast_message(int chatroom_ID, message_t message);

    int chatroomID() const { return chatroom_ID; }
    void setChatroomID(int chatroomID) { chatroom_ID = chatroomID; }

    message_t getMessage() const { return message; }
    void setMessage(const message_t &message_) { message = message_; }
};

class request_private_message : public request
{
    // valid request_t : PRIVATE_MESSAGE
private:
    int user_id;
    message_t message;

public:
    request_private_message(int user_id, message_t message);

    int userId() const { return user_id; }
    void setUserId(int userId) { user_id = userId; }

    message_t getMessage() const { return message; }
    void setMessage(const message_t &message_) { message = message_; }
};

class request_disconnect : public request
{
    // valid request_t : DISCONNECT
public:
    request_disconnect();
};