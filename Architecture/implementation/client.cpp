#include "../headers/client.h"
#include "../headers/coder.h"
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

int Client::getSocketfd() const { return socketfd; }
void Client::setSocketfd(int socketfd_) { socketfd = socketfd_; }

void Client::send_over_socket(string message)
{
    // string S = "OKAY";
    send(getSocketfd(), message.c_str(), message.size(), 0);
}
string Client::receive_from_socket()
{
    int valread = 0;
    char buffer[1024] = {0};
    while ((valread = read(getSocketfd(), buffer, sizeof(buffer))) <= 0)
    {
        1 == 1;
    }
    if (valread == 0)
        cout << "[client] : Error reading from socket\n";
    // string string_buffer = (string)buffer;
    string string_buffer(buffer, valread);
    // cout
    // << "STRING : " << string_buffer << '\n';
    // cout << "Decoding: " << coder::decode_request_connect(string_buffer) << '\n';
    return string(string_buffer);
}
bool Client::addchatrooms(int chatroom_id)
{

    chatrooms.insert(chatroom_id);
    return true;
}
/*
string string_buffer = coder::encode_request_disconnect( req ); //corresponding encoding
send( *clientSocket, string_buffer.c_str(), string_buffer.size(), 0);

*/

/*
    char * buffer;
    valread = read( *clientSocket, buffer, sizeof(buffer) );
    string string_buffer = (string) buffer;
    request_t type = coder::get_encode_reply_type(string_buffer);

*/