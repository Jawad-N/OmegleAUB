#include "../headers/client.h"

Client::Client()
{
    setName("");
    setActivated(false);
}
Client::Client(id username)
{
    setName(username);
    setActivated(true);
}
map<int, request> Client::getpendingRequests() const { return pending_requests; }
void Client::setPendingRequests(const map<int, request> &pendingRequests) { pending_requests = pendingRequests; }
// // // // Client end // // // //

// // // // Getters and setters start // // // //
id Client::getName() const { return name; }
void Client::setName(const id &name_) { name = name_; }

set<int> Client::getChatrooms() const { return chatrooms; }
void Client::setChatrooms(const set<int> &chatrooms_) { chatrooms = chatrooms_; }

set<id> Client::getUsers() const { return users; }
void Client::setUsers(const set<id> &users_) { users = users_; }

// map<int, request> Client::getpendingRequests() const { return pending_requests; }
// void Client::setPendingRequests(const map<int, request> &pendingRequests) { pending_requests = pendingRequests; }

pthread_t Client::getlThread() const { return l_thread; }
void Client::setLThread(const pthread_t &lThread) { l_thread = lThread; }

pthread_t Client::getwThread() const { return w_thread; }
void Client::setWThread(const pthread_t &wThread) { w_thread = wThread; }

bool Client::getActivated() const { return activated; }
void Client::setActivated(bool activated_) { activated = activated_; }

void Client::insertPendingRequest(int request_id, request req)
{
    pending_requests[request_id] = req;
}