#include <bits/stdc++.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <chrono>
#include <ctime>
#include <mutex>
#include <semaphore.h>
// #include <semaphore>
#include "headers/structures.h"
#include "headers/utilities.h"
#include "headers/request.h"
#include "headers/reply.h"
#include "headers/coder.h"
using namespace std;

int userCounter = 0;

set<chatroom_t> CR;
vector<int> sockets; // sockets are filedescriptors, id is the index of the vector

queue<request *> q;
mutex queueMutex;
sem_t work;

map<string, int> nameToSocket;
map<int, string> socketToName;

void *listeningThread(void *IC)
{
    int *incomingSocket = (int *)IC;
    while (true)
    {

        char buffer[1024] = {0};
        int valread = 0;
        while ((valread = read(*incomingSocket, buffer, sizeof(buffer))) == 0)
        {
            1 == 1;
        }
        cout << valread << '\n';
        cout << "received" << buffer << '\n';
        bool flag = false;
        if (socketToName.find(*incomingSocket) != socketToName.end()) flag = true;
        string string_buffer = (string)buffer;
        cout << "Here\n";
        cout << string_buffer << '\n';
        cout.flush();
        request_t type = coder::get_encode_request_type(string_buffer);
        cout << "TYPE RECEIVED: " << (int)type << '\n';
        cout.flush();
        queueMutex.lock();
        if (type == connect_CR)
        {
            request_connect req = coder::decode_request_connect(string_buffer);
            req.setSocket(*incomingSocket);
            if (flag)
                req.setFrom(socketToName[*incomingSocket]);
            q.push(&req);
        }
        else if (type == list_CR)
        {
            request_list req = coder::decode_request_list(string_buffer);
            req.setSocket(*incomingSocket);
            if (flag)
                req.setFrom(socketToName[*incomingSocket]);
            q.push(&req);
        }
        else if (type == create_CR)
        {
            request_create_CR req = coder::decode_request_create_CR(string_buffer);
            req.setFrom("menjarib");
            cout << "I'M INSTANCE: " << req.getFrom() << "\n";
            req.setSocket(*incomingSocket);
            if (flag)
                req.setFrom(socketToName[*incomingSocket]);
            q.push(&req);
        }
        else if (type == join_CR)
        {
            request_JLD_CR req = coder::decode_request_JLD_CR(string_buffer);
            req.setSocket(*incomingSocket);
            if (flag)
                req.setFrom(socketToName[*incomingSocket]);
            q.push(&req);
        }
        else if (type == leave_CR)
        {
            request_JLD_CR req = coder::decode_request_JLD_CR(string_buffer);
            req.setSocket(*incomingSocket);
            if (flag)
                req.setFrom(socketToName[*incomingSocket]);
            q.push(&req);
        }
        else if (type == delete_CR)
        {

            request_JLD_CR req = coder::decode_request_JLD_CR(string_buffer);
            cout << " DECODING CHECK: " << req.getchatroomID() << '\n';
            req.setSocket(*incomingSocket);
            if (flag)
                req.setFrom(socketToName[*incomingSocket]);
            q.push(&req);
        }
        else if (type == BROADCAST_MESSAGE)
        {
            request_broadcast_message req = coder::decode_request_broadcast_message(string_buffer);
            req.setSocket(*incomingSocket);
            if (flag)
                req.setFrom(socketToName[*incomingSocket]);
            q.push(&req);
        }
        else if (type == list_users)
        {
            request_list req = coder::decode_request_list(string_buffer);
            req.setSocket(*incomingSocket);
            if (flag)
                req.setFrom(socketToName[*incomingSocket]);
            q.push(&req);
        }
        else if (type == PRIVATE_MESSAGE)
        {
            request_private_message req = coder::decode_request_private_message(string_buffer);
            req.setSocket(*incomingSocket);
            if (flag)
                req.setFrom(socketToName[*incomingSocket]);
            q.push(&req);
        }
        else if (type == DISCONNECT)
        {
            queueMutex.unlock();
            close(*incomingSocket);
            exit(0);
            break; // when disonnecting, reach pthread_exit to kill the thread
        }
        else
        {
            cout << "here6\n";
        }
        queueMutex.unlock();

        sem_post(&work); // to signal a working thread to start working
    }

    close(*incomingSocket);
    pthread_exit(NULL); // only kill thread when connections requests to die.
}

// checked
// Called from Client
void connectRequest(request_connect req)
{
    reply_connect rep;

    try
    {
        if (nameToSocket.find(req.getuserName()) != nameToSocket.end())
        {
            rep.setReplyId(req.getrequestId());
            rep.setRepType(connect_CR);
            rep.setStatus(200);
            rep.setServerMessage("Username Already taken!");
        }
        else
        {
            nameToSocket[req.getuserName()] = req.getSocket();
            socketToName[req.getSocket()] = req.getuserName();
            rep.setReplyId(req.getrequestId());
            rep.setRepType(connect_CR);
            rep.setStatus(200);
            rep.setServerMessage("Connected Succesfully");
        }
    }
    catch (const exception &e)
    {
        rep.setReplyId(req.getrequestId());
        rep.setRepType(connect_CR);
        rep.setStatus(500);
        rep.setServerMessage("Could not connect succesfully");
    }
    cout << rep << '\n';
    string string_buffer = coder::encode_reply_connect(rep);
    send(req.getSocket(), string_buffer.c_str(), string_buffer.size(), 0);
}

// checked
void listRequest(request_list req)
{
    reply_list_CR rep;
    rep.setRepType(list_CR);
    rep.setReplyId(req.getrequestId());
    vector<chatroom_t> rooms;
    try
    {
        for (chatroom_t cr : CR)
        {
            rooms.push_back(cr);
        }
        rep.setChatrooms(rooms);
        rep.setStatus(200);
        rep.setServerMessage("Succesful");
    }
    catch (const exception &e)
    {
        rep.setStatus(500);
        rep.setServerMessage("fail");
    }
    string string_buffer = coder::encode_reply_list_CR(rep);
    send(req.getSocket(), string_buffer.c_str(), string_buffer.size(), 0);
}

int roomCount = 0;
// TODO
// checked
//
void createRequest(request_create_CR req)
{
    reply_create_CR rep;
    rep.setRepType(create_CR);
    rep.setReplyId(req.getrequestId());
    chatroom_t cur = req.getChatroom();
    cur.setOwner(socketToName[req.getSocket()]);
    cur.setChatroomID(roomCount++);
    try
    {
        set<id> tempSet = cur.getMembers();
        cout << "tempset1: ";
        for (id person : tempSet)
        {
            cout << person << ' ';
        }
        cout << endl;

        tempSet.insert(req.getFrom());

        cout << "tempset2: ";
        for (id person : tempSet)
        {
            cout << person << ' ';
        }
        cout << endl;

        cur.setMembers(tempSet);
        cout << "cur: ";
        for (id person : cur.getMembers())
        {
            cout << person << ' ';
        }
        cout << endl;
        rep.setChatroom(cur);
        CR.insert(cur);
        rep.setServerMessage("created Room succesfully");
        rep.setStatus(200);
    }
    catch (const exception &e)
    {
        rep.setServerMessage(" Failed in creating room ");
        rep.setStatus(500);
    }

    string string_buffer = coder::encode_reply_create_CR(rep);
    send(req.getSocket(), string_buffer.c_str(), string_buffer.size(), 0);
    for (chatroom_t cr : CR)
        cout << cr << '\n';
    cout << "CR SIZE IS: " << CR.size() << '\n';
}

// checked
void joinRequest(request_JLD_CR req)
{
    cout << "GETFROM: " << req.getFrom();
    reply_JLD_CR rep;
    rep.setRepType(join_CR);
    rep.setReplyId(req.getrequestId());
    try
    {
        bool flag = false;

        for (auto it = CR.begin(); it != CR.end(); ++it)
        {
            chatroom_t cr = *it;
            if (cr.getchatroomID() == req.getchatroomID())
            {   
                bool find = false;
                for(id name: cr.getMembers()){
                    if(name == req.getFrom()) find = true;
                }
                cout << '\n';
                if( find ){
                    rep.setServerMessage("You Are Already In That Room");
                }
                else
                {
                    rep.setServerMessage("Joined Desired Room");
                    set<id> tempSet = cr.getMembers();
                    tempSet.insert(req.getFrom());
                    cr.setMembers(tempSet);
                    CR.erase(it);
                    CR.insert(cr);
                }
                flag = true;
                break;
            }

        }

        if (!flag)
        {
            rep.setServerMessage("No Such Room ");
            rep.setChatroomId(-1);
        }
        rep.setStatus(200);
    }
    catch (const exception &e)
    {
        rep.setServerMessage("Failed in room joining");
        rep.setStatus(500);
    }
    string string_buffer = coder::encode_reply_JLD_CR(rep);
    send(req.getSocket(), string_buffer.c_str(), string_buffer.size(), 0);
}

//
void leaveRequest(request_JLD_CR req)
{
    cout << "FROM LEAVE: " << req.getFrom() << '\n';
    reply_JLD_CR rep;
    rep.setRepType(leave_CR);
    rep.setReplyId(req.getrequestId());
    rep.setChatroomId(req.getchatroomID());
    try
    {
        bool flag = false;
        for (auto it = CR.begin(); it != CR.end(); ++it){
            chatroom_t cr = *it;
            if (cr.getchatroomID() == req.getchatroomID())
            {   
                bool find = false;
                cout << "\nRoom Members before leave: ";
                for(id member: cr.getMembers()){
                    if ( member == req.getFrom() ) find = true;
                    cout << member << ' ';
                }
                cout << '\n';
                cout << "Person that wants to leave: " << req.getFrom() <<'\n';
                if( find ){
                    set<id> tempSet = cr.getMembers();
                    tempSet.erase( req.getFrom() );
                    cr.setMembers(tempSet);
                    string temp = "Left Room " + cr.getName();
                    rep.setServerMessage( temp );
                    rep.setStatus(200);
                    it = CR.erase(it);
                    CR.insert(cr);
                }
                else{
                    rep.setServerMessage("Not In That Room To Begin With");
                    rep.setStatus(200);
                }
                
                flag = true;
                break;
            }
            
        }
        if (!flag){
            rep.setServerMessage("ChatRoom Does Not Exist");
            rep.setStatus(200);
        }
    }
    catch (const exception &e)
    {
        rep.setServerMessage("Failed to leave room");
        rep.setStatus(500);
    }
    string string_buffer = coder::encode_reply_JLD_CR(rep);
    send(req.getSocket(), string_buffer.c_str(), string_buffer.size(), 0);
}

// checked
void deleteRequest(request_JLD_CR req)
{
    reply_JLD_CR rep;
    rep.setRepType(delete_CR);
    rep.setReplyId(req.getrequestId());

    try
    {
        bool flag = false;
        for (auto it = CR.begin(); it != CR.end(); ++it)
        {
            chatroom_t cr = *it;
            if (cr.getchatroomID() == req.getchatroomID())
            {
                if (cr.getOwner() != req.getFrom())
                {
                    rep.setServerMessage(" You Do Not Have Owner Priviliges ");
                    rep.setStatus(200);
                }
                else if (cr.getMembers().size() > 1)
                {
                    for (id s : cr.getMembers())
                    {
                        if (s != cr.getOwner())
                        {
                            request_JLD_CR* reqt = new request_JLD_CR();
                            reqt->setChatroomID(req.getchatroomID());
                            reqt->setRequestId(req.getrequestId());
                            reqt->setFrom(s);
                            reqt->setReqType(leave_CR);
                            queueMutex.lock();
                            q.push( reqt ); // requesting people to leave the chatroom before deletion
                            queueMutex.unlock();
                            sem_post(&work);
                        }
                    }
                    queueMutex.lock();
                    q.push(&req);
                    queueMutex.unlock();
                    rep.setServerMessage("Delete Chatroom Request Delayed Until Room Is Empty");
                    rep.setStatus(200);
                }
                else
                {
                    CR.erase(cr);
                    rep.setServerMessage("Room Deleted Succesfully");
                    rep.setStatus(200);
                }
                rep.setChatroomId(req.getchatroomID());
                flag = true;
                break;
            }
            
        }
        if (!flag)
        {
            rep.setServerMessage("Did not find room to Delete");
            rep.setStatus(200);
        }
    }
    catch (const exception &e)
    {
        rep.setServerMessage("Delete Room request Failed");
        rep.setStatus(500);
    }
    string string_buffer = coder::encode_reply_JLD_CR(rep);
    send(req.getSocket(), string_buffer.c_str(), string_buffer.size(), 0);
}



// checked
void privateMessageRequest(request_private_message req)
{
    reply_private_message rep;
    rep.setRepType(PRIVATE_MESSAGE);
    rep.setReplyId(req.getrequestId());
    try
    {
        rep.setMessage(req.getMessage());
        rep.setUserId(req.getuserId());
        rep.setStatus(200);
        rep.setServerMessage("Message delivered succesfully");
    }
    catch (const exception &e)
    {
        rep.setStatus(500);
        rep.setServerMessage("Failed to transmit a private msg");
    }
    message_t tmp = rep.getMessage();
    tmp.setSender( req.getFrom() );
    rep.setMessage(tmp);
    reply_private_message repSender(rep);
    tmp = repSender.getMessage();
    tmp.setContent("$tilowkey");
    repSender.setMessage(tmp);
    string string_buffer = coder::encode_reply_private_message(rep);
    string string_buffer2 = coder::encode_reply_private_message(repSender);
    send( nameToSocket[ req.getuserId() ], string_buffer.c_str(), string_buffer.size(), 0 );
    send( req.getSocket(), string_buffer2.c_str(), string_buffer2.size(), 0 );
}

// checked
void broadcastRequest(request_broadcast_message req)
{
    reply_broadcast_message rep;
    rep.setChatroomId(req.getchatroomID());
    rep.setMessage(req.getMessage());
    try
    {
        for (chatroom_t cr : CR)
        {
            if (cr.getchatroomID() == req.getchatroomID())
            {   
                bool find = false;
                for(id member: cr.getMembers()){
                    if( req.getFrom() == member ) find = true;
                }
                if(find){
                    for (id person : cr.getMembers())
                    {
                        cout << "c\n";
                        if( req.getFrom() == person ){
                            cout << "HAHA" << '\n'; continue;
                        }
                        request_private_message * reqt = new request_private_message();
                        reqt->setRequestId(req.getrequestId());
                        reqt->setReqType(PRIVATE_MESSAGE);
                        reqt->setFrom(req.getFrom());
                        reqt->setUserId(person);
                        reqt->setMessage(req.getMessage());
                        queueMutex.lock();
                        q.push( reqt );
                        queueMutex.unlock();
                        sem_post(&work);
                    }
                    rep.setServerMessage("Send Succesfully ");
                    rep.setStatus(200);
                    break;
                }
                else{
                    rep.setServerMessage("You Are Not In The Specified Room");
                    rep.setStatus(200);
                }
            }
        }
    }
    catch (const exception &e)
    {
        rep.setServerMessage("Delete Room request Failed");
        rep.setStatus(500);
    }
    string string_buffer = coder::encode_reply_broadcast_message(rep);
    send(req.getSocket(), string_buffer.c_str(), string_buffer.size(), 0);
}



void listUsersRequest(request_list req)
{
    reply_list_users rep;
    rep.setReplyId(req.getrequestId());
    rep.setRepType(list_users);
    try
    {
        vector<id> users;
        set<id> S;
        for (chatroom_t cr : CR)
        {
            for (id person : cr.getMembers())
            {
                S.insert(person); // set to avoid repititions, since a user may be in multiple chatrooms
            }
        }
        for (id person : S)
        {
            users.push_back(person);
        }
        sort(users.begin(), users.end()); // return the list alphabetically
        rep.setUsers(users);
        cout << "USERS: ";
        for( id user: users ) cout << user << ' '; cout << '\n';
        rep.setServerMessage("List Sent Succesfully");
        rep.setStatus(200);
    }
    catch (const exception &e)
    {
        rep.setStatus(500);
        rep.setServerMessage("Failed to list members of chatroom");
    }
    string string_buffer = coder::encode_reply_list_users(rep);
    send(req.getSocket(), string_buffer.c_str(), string_buffer.size(), 0);
}

// checked
void disconnectRequest(request_disconnect req)
{
    for (chatroom_t cr : CR)
    {
        for (id person : cr.getMembers())
        {
            if (person == req.getFrom())
            {
                set<id> tempSet = cr.getMembers();
                tempSet.erase(person);
                cr.setMembers(tempSet);
            }
        }
    }
}

void *workingThread(void *index)
{ // no input taken here
    while (true)
    {
        sem_wait(&work); // only to avoid bounded waiting
        queueMutex.lock();
        while(q.empty()){};
        request *req = q.front();
        q.pop();
        queueMutex.unlock();

        if (req->getreqType() == connect_CR)
        {
            request_connect *reqn = (request_connect *)req;
            connectRequest(*reqn);
        }
        else if (req->getreqType() == list_CR)
        {
            request_list *reqn = (request_list *)req;
            listRequest(*reqn);
        }
        else if (req->getreqType() == create_CR)
        {
            request_create_CR *reqn = (request_create_CR *)req;
            createRequest(*reqn);
        }
        else if (req->getreqType() == join_CR)
        {
            request_JLD_CR *reqn = (request_JLD_CR *)req;
            joinRequest(*reqn);
        }
        else if (req->getreqType() == leave_CR)
        {
            request_JLD_CR *reqn = (request_JLD_CR *)req;
            leaveRequest(*reqn);
        }
        else if (req->getreqType() == delete_CR)
        {
            request_JLD_CR *reqn = (request_JLD_CR *)req;
            deleteRequest(*reqn);
        }
        else if (req->getreqType() == BROADCAST_MESSAGE)
        {
            request_broadcast_message *reqn = (request_broadcast_message *)req;
            broadcastRequest(*reqn);
        }
        else if ( req->getreqType() == PRIVATE_MESSAGE ){
            request_private_message *reqn = (request_private_message *) req;
            privateMessageRequest(*reqn);
        }
        else if (req->getreqType() == list_users)
        {
            request_list *reqn = (request_list *)req;
            listUsersRequest(*reqn);
        }
        else if (req->getreqType() == DISCONNECT)
        {
            request_disconnect *req = (request_disconnect *)req;
            disconnectRequest(*req);
        }
    }
}

int main()
{
    chatroom_t chat = chatroom_t();
    chat.setCapacity(100);
    chat.setChatroomID(-1);
    chat.setCreated(time(nullptr));
    chat.setDescription("OS is fun and Easy");
    chat.setMembers({"Jawad", "Hashem"});
    chat.setName("Bechtel110");
    chat.setOwner("HASHEM&JAWAD");

    CR.insert(chat);
    pthread_t threads[100];
    pthread_t wThreads[30];
    sem_init(&work, 0, 0);

    for (int i = 0; i < 30; i++)
    {
        int err = pthread_create(&wThreads[i], NULL, workingThread, NULL);
        if (err != 0)
            cout << " something is wrong working thread ";
    }

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress;
    socklen_t addrlen = sizeof(serverAddress);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        perror(" bind failed ");
        exit(EXIT_FAILURE);
    }
    // Giving the socket the capacity to listent to incoming communication

    if (listen(serverSocket, 20) < 0)
    {
        // handling potential error
        perror(" listen failed ");
        exit(EXIT_FAILURE);
    }

    while (true)
    {

        int incoming[1024];
        // Taking in requests, if one arrives before accept then it queues up and accept does not block
        // Otherwise accept blocks and waits until a connect request occurs
        if ((incoming[userCounter] = accept(serverSocket, (struct sockaddr *)&serverAddress, &addrlen)) < 0)
        {
            // handling potential error
            perror(" accept failed ");
            exit(EXIT_FAILURE);
        }
        
        int err = pthread_create(&threads[userCounter], NULL, listeningThread, &incoming[userCounter]);
        userCounter++;
        if (err != 0)
            cout << " something is wrong " << '\n';

        // make a reply containing chat rooms available
        // available rooms sent
    }
    sem_destroy(&work);
    return 0;
}