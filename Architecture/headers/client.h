#pragma once

#include "includes.h"
#include "request.h"
#include "reply.h"
#include "coder.h"

class Client
{
private:
    id name;                            // name of the user
    set<int> chatrooms;                 // chatroom_ids
    set<id> users;                      // set of friends (reachable users)
    map<int, request> pending_requests; // all the requests that are waiting
    // socket connection
    pthread_t l_thread;                           // thread for listening
    pthread_t w_thread;                           // thread for writing
    map<int, vector<message_t>> chatroom_history; // chat history of the chatrooms.
    bool activated;                               // set act activated to true

public:
    Client();

    // Constructors
    void C_connect(id name);
    void C_handle_connect();

    void C_disconnect();
    void C_handle_disconnect();

    void C_list_chatrooms();
    void C_handle_list_chatrooms();

    void C_query_chatroom(int chatroom_id);
    void C_handle_query_chatroom();

    void C_leave_chatroom();
    void C_handle_leave_chatroom();

    void C_delete_chatroom();
    void C_handle_delete_chatroom();

    void C_broadcast_message(int chatroom_id, string message);
    void C_handle_broadcast_message();

    void C_list_users();
    void C_handle_list_users();

    void C_private_message(id user, string message);
    void C_handle_private_message();

    void C_query_again(int query_id);
    void C_handle_query_again();

    // Setters and getting

    id getName() const;
    void setName(const id &name_);

    set<int> getChatrooms() const;
    void setChatrooms(const set<int> &chatrooms_);

    set<id> getUsers() const;
    void setUsers(const set<id> &users_);

    map<int, request> pendingRequests() const;
    void setPendingRequests(const map<int, request> &pendingRequests);

    bool getActivated() const;
    void setActivated(bool activated_);

    pthread_t getlThread() const;
    void setLThread(const pthread_t &lThread);

    pthread_t getwThread() const;
    void setWThread(const pthread_t &wThread);

    // Setters and getters
};

// connect ()
// connect_CR , list_chat_rooms , join_chatroom , leave_chatroom, delete_chatroom, l
// connect_CR = 0,
//     list_CR = 1,
//     create_CR = 2,
//     join_CR = 3,
//     leave_CR = 4,
//     delete_CR = 5,
//     BROADCAST_MESSAGE = 6,
//     list_users = 7,
//     PRIVATE_MESSAGE = 8,
//     DISCONNECT = 9,
//     connect_USR = 10