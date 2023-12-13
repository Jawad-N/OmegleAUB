#include <bits/stdc++.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include<chrono>
#include<ctime>
#include<mutex>
#include<semaphore.h>

using namespace std;


enum request_t {
    connect_CR = 0,
    list_CR = 1,
    create_CR = 2,
    join_CR = 3,
    leave_CR = 4,
    delete_CR = 5,
    BROADCAST_MESSAGE = 6,
    list_users = 7,
    PRIVATE_MESSAGE = 8,
    DISCONNECT = 9
};

int userCounter = 0;

map<chatRoom> CR;
vector<int> sockets; // sockets are filedescriptors, id is the index of the vector

queue<request> q;
mutex queueMutex;
counting_semaphore<int> work(0);

map< string, int > nameToSocket;
map< int, string > socketToName;


class request{
    public:

};


class requestConnect : public request{
    

};

struct msg
{

    int to;
    int from;
    string s;
    time_t sendingTime;

};


struct chatroom_t{
    
    string name;
    int capacity;
    int size;
    int owner;
    time_t birthtime;
    string description;
    vector<int> members;
    chatRoom(string _name, int _cap, int _size, int _owner, string _desc){
        name = _name; capacity = _cap; size = _size; owner = _owner; description = _desc; 
        birthtime = time(NULL); 
        members = vector<int> ( {owner} ); // initially there is only one member that is the owner
    }

};







void * workingThread( void * index ){ // no input taken here

    while(true){

        work.acquire(); // only to avoid bounded waiting

        queueMutex.lock();
        request req = q.front();
        q.pop();
        queueMutex.unlock();

        if( req.req_type == connect_CR ){
            req = ( request_connect ) req;
            connectRequest( req );
        }
        else if( req.req_type == list_CR ){
            req = ( request_list ) req;
            listRequest( req );
        }
        else if( req.req_type == create_CR ){

        }
        else if( req.req_type == join_CR ){
        
        }
        else if( req.req_type == leave_CR ){

        }
        else if( req.req_type == delete_CR ){

        }
        else if( req.req_type == BROADCAST_MESSAGE ){
        
        }
        else if( req.req_type == list_users){
        
        }
        else if( req.req_type == DISCONNECT ){

        }
        
    }


} 


void * listeningThread( void * incomingSocket ){

    while(true){
        
        char buffer[1024] = { 0 };
        ssize_t valread = recv(incomingSocket, buffer, sizeof(buffer), MSG_WAITALL);
        request req = *((request *) buffer);
        queueMutex.lock();
        q.push(req);
        queueMutex.unlock();
        work.release(); // to signal a working thread to start working

        if( req.reques_t == DISCONNECT ){
            break; // when disonnecting, reach pthread_exit to kill the thread
        }

    }

    close(incomingSocket);
    pthread_exit(NULL) // only kill thread when connections requests to die.

}



void connectRequest( request_connect req, int socketNbr ){
    reply_connect rep = reply_connect();

    try{
        nameToSocket[ req.user_name ] = socketNbr;
        socketToName[ socketNbr ] = req.user_name;
        rep.reply_id = req.request_id; 
        rep.rep_type = connect_CR;
        rep.status = 200;
        rep.server_message = "Connected Succesfully";
    }
    catch (const exception& e){
        rep.reply_id = req.request_id; 
        rep.rep_type = connect_CR;
        rep.status = 500;
        rep.server_message = "Could not connect succesfully";
    }
    
    send( socketNbr, &rep, sizeof(rep), 0 );

}

void listRequest( request_list req, int socket ){  
    string choices = "";
    reply_list_CR rep;
    rep.rep_type = connect_CR;
    rep.reply_id = req.id;
    vector<chatroom_t> rooms;
    try{
        int count = 1;
        for ( chatroom_t cr: CR ){
            rooms.push_back(cr);
        }
        rep.status = 200;
        rep.server_message = "Succesful"
    }
    catch (const exception& e){
        rep.status = 500;
        rep.server_message = "fail"
    }    

    send( socketNbr, &rep, sizeof(rep), 0 );
    
}


void broadcastRequest( request_broadcast_message ){

    

}

int main()
{

    pthread_t threads[1000];
    pthread_t wThreads[30];

    int offset = 1024;

    for(int i = 0 ; i < 30; i++){
        int err = pthread_create( &wThreads[i], NULL, workingThread, NULL ) ;
        if( err != 0 ) cout << " something is wrong working thread ";
    }


    while (true)
    {

        int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in serverAddress;
        socklen_t addrlen = sizeof(serverAddress);
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(offset++);
        if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
        {
            perror(" bind failed ");
            exit(EXIT_FAILURE);
        }
        // Giving the socket the capacity to listent to incoming communication
        if (listen(serverSocket, 3) < 0)
        {
            // handling potential error
            perror(" listen failed ");
            exit(EXIT_FAILURE);
        }
        int incoming;
        // Taking in requests, if one arrives before accept then it queues up and accept does not block
        // Otherwise accept blocks and waits until a connect request occurs
        if (incoming = accept(serverSocket, (struct sockaddr *)&serverAddress, &addrlen) < 0)
        {
            // handling potential error
            perror(" accept failed ")
                exit(EXIT_FAILURE);
        }
 
        int err = pthread_create( &thread[userCounter++], NULL, listeningThread, &incoming );
        if( err != 0 ) cout << " something is wrong " << '\n';
    
        // make a reply containing chat rooms available
        // available rooms sent
    }

    return 0;
}