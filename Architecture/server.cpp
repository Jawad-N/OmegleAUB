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
#include"Architecture/headers/structures.h"
#include"Architecture/headers/utilities.h"
#include"Architecture/headers/request.h"
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
int roomCount = 0;

set<chatroom_t> CR;
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

        if( req.getrequestId() == connect_CR ){
            req = ( request_connect ) req;
            connectRequest( req );
        }
        else if( req.getrequestId() == list_CR ){
            req = ( request_list ) req;
            listRequest( req );
        }
        else if( req.getrequestId() == create_CR ){
            req = ( request_create_CR ) req;
            createRequest( req  ); 
        }
        else if( req.getrequestId() == join_CR ){
            req = ( request_JLD_CR ) req;
            joinRequest( req )
        }
        else if( req.getrequestId() == leave_CR ){
            req = ( request_JLD_CR ) req;
            leaveRequest( req );
        }
        else if( req.getrequestId() == delete_CR ){
            req = ( request_JLD_CR ) req;
            deleteRequest( req );
        }
        else if( req.getrequestId() == BROADCAST_MESSAGE ){
            req = ( reply_broadcast_message ) req;
            broadcastRequest( req );
        }
        else if( req.getrequestId() == list_users){
            
        }
        else if( req.getrequestId() == DISCONNECT ){

        }
        
    }


} 


void * listeningThread( void * incomingSocket ){

    while(true){
        
        char buffer[1024] = { 0 };
        ssize_t valread = recv(incomingSocket, buffer, sizeof(buffer), MSG_WAITALL);
        string string_buffer = (string) buffer;
        request req = decode(string_buffer);
        if( socketToname.find( *incomingSocket) ) req.setFrom = socketToName[*incomingSocket];  
        req.setSocket(*incomingSocket);
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



void connectRequest( request_connect req ){
    reply_connect rep = reply_connect();

    try{
        nameToSocket[ req.user_name ] = req.getSocket();
        socketToName[ req.getSocket() ] = req.set; 
        rep.setReplyID( req.getrequestId );
        rep.setReplyType( connect_CR ); 
        rep.setStatus( 200 );
        rep.setServerMessage( "Connected Succesfully" );
    }
    catch (const exception& e){
        rep.setReplyID( req.getrequestId ); 
        rep.setReplyType( connect_CR ) ;
        rep.setStatus( 500 ) ;
        rep.setServerMessage( "Could not connect succesfully" );
    }
    //
    string string_buffer = encode(rep); 
    char buffer[ string_buffer.size() + 1]; buffer[ string_buffer.size() ] = '\0';
    copy_to_pointer( string_buffer, buffer );
    send( req.getSocket(), buffer, sizeof(buffer), 0 );

}

void listRequest( request_list req ){  
    string choices = "";
    reply_list_CR rep;
    rep.setReplyType( list_CR ) ;
    rep.setReplyID( req.getrequestId );
    vector<chatroom_t> rooms;
    try{
        for ( chatroom_t cr: CR ){
            rooms.push_back(cr);
        }
        rep.setStatus( 200 );
        rep.setServerMessage( "Succesful" );
    }
    catch (const exception& e){
        rep.setStatus( 500 ) ;
        rep.setServerMessage( "fail" );
    }    
    string string_buffer = encode( rep );
    char * buffer[string_buffer.size() + 1]; buffer[string_buffer.size()] = '\0';
    send( req.getScoket(), buffer, sizeof(buffer), 0 );
    
}

void createRequest( request_create_CR req ) {
    reply_create_CR rep;
    rep.setReplyType( create_CR );
    rep.setReplyID( req.getrequestId );
    chatroom_t cur = req.getChatroom();
    try{
        // betredelo chatroomt type 
        cur.setID(roomCount++);
        CR.insert( cur )
        
        rep.setServerMessage("created Room succesfully");
        rep.setStatus( 200 );

    }
    catch (const exception &e){
        rep.setServerMessage(" Failed in creating room ");
        rep.setStatus( 500 );
    }
    string string_buffer = encode( rep );
    char * buffer[string_buffer.size() + 1]; buffer[string_buffer.size()] = '\0';
    send( req.getSocket(), buffer, sizeof(buffer), 0 );
}

void joinRequest( request_JLD_CR req ){
    reply_JLD_CR rep;
    rep.setReplyType( join_CR );
    rep.setReplyID( req.getrequestId() );
    try{
        bool flag = false;
        if( CR.find(req.getChatroomID()) != CR.end() ){
            CR[ req.getChatroomID ].members.push_back( req.getFrom() );
            flag = true; 
            rep.setServerMessage(" Joined Room Succesfully! ")
            rep.setChatroomID( cr.ID );
            break;
        }
        if( !flag ) {
            rep.serverMessage( "No Such Room ");
            rep.setChatroomID(-1);
        }
        rep.setStatus(200);
    }
    catch(const exception &e){
        rep.setServerMessage("Failed in room joining");
        rep.setStatus(500);
    }
    string string_buffer = encode( rep );
    char * buffer[string_buffer.size() + 1]; buffer[string_buffer.size()] = '\0';
    send( req.getSocket(), buffer, sizeof(buffer), 0 );
}

void leaveRequest( request_JLD_CR req ){
    reply_JLD_CR rep;
    rep.setReplyType( join_CR );
    rep.setReplyID( req.getrequestId() );
    try{
        chatroom_t cr = *CR.find( req.getChatroom() );
        if( cr.getMembers().find( req.getSocket() ) != cr.getMembers().end() ){
            cr.getMembers().erase( req.getSocket() );
            rep.setServerMessage( "left the room" )
        }
        else{
            rep.setServerMessage("Not in that chatroom");
            rep.setStatus(200);
        }
    }
    catch( const exception &e ){
        rep.setServerMessage( "Failed to leave room" );
        rep.setStatus(500);
    }
    string string_buffer = encode( rep );
    char * buffer[string_buffer.size() + 1]; buffer[string_buffer.size()] = '\0';
    send( req.getSocket(), buffer, sizeof(buffer), 0 );
}

void deleteRequest( request_JLD_CR req ){
    reply_JLD_CR rep;
    rep.setReplyType( delete_CR );
    rep.setReplyID( req.getrequestId() );
    try{
        if( CR.find( req.getChatroom()) != CR.end() ){
            chatroomt_t cr = *CR.find( req.getChatroomID );
            if( cr.getMembers().size() != 1 ){
                for( id s: cr.getMembers() ){
                    if( s != cr.getOwner() ){
                        request_JLD_CR reqt;
                        reqt.setChatroomID( req.getChatroomID() );
                        reqt.setRequestId( req.getrequestId() );
                        reqt.setFrom( s );
                        reqt.setReqType( leave_CR );
                        q.push( reqt ) // requesting people to leave the chatroom before deletion
                    }
                }
                rep.setServerMessage( "delete chatroom request delayed until room is empty" )
                rep.setStatus(200);
            }
            else{
                CR.erase( req.getChatroom() );
                rep.setServerMessage("Room Deleted Succesfully");
                rep.setStatus(200);
            }
            rep.setChatroomID( req.getChatroomID() );
        }
        else{
            rep.setServerMessage( "Did not find room in leave" );
            rep.setStatus(200);
        }
    }
    catch( const exception &e){
        rep.setServerMessage( "Delete Room request Failed");
        rep.setStatus(500);
    }
    string string_buffer = encode( rep );
    char * buffer[string_buffer.size() + 1]; buffer[string_buffer.size()] = '\0';
    send( req.getSocket(), buffer, sizeof(buffer), 0 );
}




void broadcastRequest( request_broadcast_message req ){
    reply_broadcast_message rep;
    rep.setChatroomID( req.getChatroomID() );
    rep.setMessage( req.getMessage() );
    try{
        for( id person: CR[ req.getChatroomID() ]){
            request_private_message reqt;
            reqt.setRequestId( req.getrequestId() );
            reqt.setReqType( PRIVATE_MESSAGE );
            reqt.setFrom( person );
            reqt.setUserId( nameToSocket[person] );
            reqt.setMessage( req.getMessage() );
            q.push( reqt );
        }
        rep.setServerMessage( "Send Succesfully " );
        rep.setStatus(200);
    }
    catch( const exception &e){
        rep.setServerMessage( "Delete Room request Failed");
        rep.setStatus(500);
    }
    string string_buffer = encode( rep );
    char * buffer[string_buffer.size() + 1]; buffer[string_buffer.size()] = '\0';
    send( req.getSocket(), buffer, sizeof(buffer), 0 );
}


void privateMessageRequest( request_private_message req ){
    reply_private_message rep;
    rep.setReplyType( PRIVATE_MESSAGE );
    rep.setReplyID( req.getrequestId() );
    
    try{
        rep.setMessage( req.getMessage() );
        rep.setUserId( req.getUserId() );
        rep.setStatus( 200 );
        rep.setServerMessage( "Message delivered succesfully" )
    }
    catch( const exception &e ){
        rep.setStatus(500);
        rep.setServerMessage("Failed to send a private msg")
    }

    string string_buffer = encode( rep );
    char * buffer[string_buffer.size() + 1]; buffer[string_buffer.size()] = '\0';
    send( req.getSocket(), buffer, sizeof(buffer), 0 );

}

// ask hashem
void listRequest( request_list req ){
    reply_list_users rep;
    rep.setReplyID( req.getRequestId() );
    rep.setReplyType( list_users );
    try{
        vector<id> users;
        set<id> S;
        for( chatroom_t cr: CR ){
            for( id person: cr.getMemebrs() ){
                S.insert( person );
            }
        }
        for( id person: S ){
            users.push_back( person );
        }
        sort( users.begin(), users.end() );
        rep.setUsers( users );
        rep.setServerMessage("List Sent Succesfully")
        rep.setStatus(200);

    }
    catch( const exception &e ){
        rep.setStatus(500);
        rep.setServerMessage("Failed to list members of chatroom")
    }
    string string_buffer = encode( rep );
    char * buffer[string_buffer.size() + 1]; buffer[string_buffer.size()] = '\0';
    send( req.getSocket(), buffer, sizeof(buffer), 0 );
}

void disconnectRequest( request_disconnect req ){
    for( chatroom_t cr: CR ){
        for( id person : cr.getMembers() ){
            if( person == req.getFrom() ){
                cr.getMembers().erase( person );
            }
        }
    }
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
        if ( (incoming = accept(serverSocket, (struct sockaddr *)&serverAddress, &addrlen)) < 0)
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