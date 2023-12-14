#include "../headers/client.h"

// // // // Client start // // // //

Client::Client()
{
    setActivated(false);
}

void Client::C_connect(id name)
{
    if (getActivated())
    {
        cout << "[client] : you are already connected. Your id is : " << getName() << '\n';
        return;
    }
    // Connect_request
    request_connect req(name);
    // encode request
    string encoded = coder::encode_request_connect(req);
    // add request_to_queue;
    pending_requests[req.getrequestId()] = req;
    // send request over channel
    // socket.send(encoded)
}
void Client::C_disconnect()
{
    if (!getActivated())
    {
        cout << "[client] : you are already disconnected";
        return;
    }
    // Disconnect request
    request_disconnect req();
    // encode request
    // string encode = coder::encode_req
}

void Client::C_list_chatrooms()
{
    if (!getActivated())
    {
        cout << "[client] : you are not connected. Please connect first by calling C_connect";
        return;
    }
    // requests.
}
void Client::C_query_chatroom(int chatroom_id)
{
    if (!getActivated())
    {
        cout << "[client] : you are not connected. Please connect first by calling C_connect";
        return;
    }
    // requests.
}
void Client::C_leave_chatroom()
{
    if (!getActivated())
    {
        cout << "[client] : you are not connected. Please connect first by calling C_connect";
        return;
    }
}
void Client::C_delete_chatroom()
{
    if (!getActivated())
    {
        cout << "[client] : you are not connected. Please connect first by calling C_connect";
        return;
    }
}
void Client::C_broadcast_message(int chatroom_id, string message)
{
    if (!getActivated())
    {
        cout << "[client] : you are not connected. Please connect first by calling C_connect";
        return;
    }
}

void Client::C_list_users()
{
    if (!getActivated())
    {
        cout << "[client] : you are not connected. Please connect first by calling C_connect";
        return;
    }
}
void Client::C_private_message(id user, string message)
{
    if (!getActivated())
    {
        cout << "[client] : you are not connected. Please connect first by calling C_connect";
        return;
    }
}

void Client::C_query_again(int query_id)
{
    if (!getActivated())
    {
        cout << "[client] : you are not connected. Please connect first by calling C_connect";
        return;
    }
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

map<int, request> Client::pendingRequests() const { return pending_requests; }
void Client::setPendingRequests(const map<int, request> &pendingRequests) { pending_requests = pendingRequests; }

pthread_t Client::getlThread() const { return l_thread; }
void Client::setLThread(const pthread_t &lThread) { l_thread = lThread; }

pthread_t Client::getwThread() const { return w_thread; }
void Client::setWThread(const pthread_t &wThread) { w_thread = wThread; }

bool Client::getActivated() const { return activated; }
void Client::setActivated(bool activated_) { activated = activated_; }

// // // // Getters and setters end // // // //