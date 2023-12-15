#pragma once
#include "includes.h"
#include "structures.h"
#include "request.h"
#include "reply.h"

class Client
{
private:
    id name;                            // name of the user
    set<int> chatrooms;                 // chatroom_ids
    set<id> users;                      // set of friends (reachable users)
    map<int, request> pending_requests; // all the requests that are waiting
    // socket connection // Jawad can you add a socket structure
    /**
     * Jawad can you add socket structure or class that have the following operation
     * > connect(string ip_address,int port);
     * > send(string message) : sends the message after the connection
     * > close()              : close the the connection
     * > receive()            : returns a string which is the message received via the connection
     */
    pthread_t l_thread;                           // thread for listening
    pthread_t w_thread;                           // thread for writing
    map<int, vector<message_t>> chatroom_history; // chat history of the chatrooms.
    bool activated;
    int socketfd;

public:
    Client(id username);
    Client();
    id getName() const;
    void setName(const id &name_);

    set<int> getChatrooms() const;
    void setChatrooms(const set<int> &chatrooms_);

    set<id> getUsers() const;
    void setUsers(const set<id> &users_);

    map<int, request> getpendingRequests() const;
    void setPendingRequests(const map<int, request> &pendingRequests);

    bool getActivated() const;
    void setActivated(bool activated_);

    pthread_t getlThread() const;
    void setLThread(const pthread_t &lThread);

    pthread_t getwThread() const;
    void setWThread(const pthread_t &wThread);

    void insertPendingRequest(int request_id, request req);

    int getSocketfd() const;
    void setSocketfd(int socketfd_);

    void send_over_socket(string message);
    string receive_from_socket();
};