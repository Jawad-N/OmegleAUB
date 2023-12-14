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
#include"headers/structures.h"
#include"headers/utilities.h"
#include"headers/request.h"
#include"headers/reply.h"
#include"headers/coder.h"
using namespace std;




int userCounter = 0;

set<chatroom_t> CR;
vector<int> sockets; // sockets are filedescriptors, id is the index of the vector

queue<request*> q;
mutex queueMutex;
counting_semaphore<int> work(0);

map< string, int > nameToSocket;
map< int, string > socketToName;




void * listeningThread( void * IC ){
    int *incomingSocket = (int*) IC;
    while(true){
        
        char buffer[1024] = { 0 }; 
        ssize_t valread = recv(*incomingSocket, buffer, sizeof(buffer), MSG_WAITALL);
        cout << "received" << buffer << '\n';
        bool flag = false;
        if( socketToName.find( *incomingSocket ) != socketToName.end() ) flag = true;  
        string string_buffer = (string) buffer;
        request_t type = coder::get_encode_request_type( string_buffer );
        queueMutex.lock();
       if (type == connect_CR) {
            request_connect req = coder::decode_request_connect( string_buffer );
            if(flag) req.getFrom() = socketToName[*incomingSocket];
            q.push( &req );
        } else if (type == list_CR) {
            request_list req = coder::decode_request_list( string_buffer );
            if(flag) req.getFrom() = socketToName[*incomingSocket];
            q.push( &req );
        } else if (type == create_CR) {
            request_create_CR req = coder::decode_request_create_CR( string_buffer );
            if(flag) req.getFrom() = socketToName[*incomingSocket];
            q.push( &req );
        } else if (type == join_CR) {
            request_JLD_CR req = coder::decode_request_JLD_CR( string_buffer );
            if(flag) req.getFrom() = socketToName[*incomingSocket];
            q.push( &req );
        } else if (type == leave_CR) {
            request_JLD_CR req = coder::decode_request_JLD_CR( string_buffer );
            if(flag) req.getFrom() = socketToName[*incomingSocket];
            q.push( &req );
        } else if (type == delete_CR) {
            request_JLD_CR req = coder::decode_request_JLD_CR( string_buffer );
            if(flag) req.getFrom() = socketToName[*incomingSocket];
            q.push( &req );
        } else if (type == BROADCAST_MESSAGE) {
            request_broadcast_message req = coder::decode_request_broadcast_message( string_buffer );
            if(flag) req.getFrom() = socketToName[*incomingSocket];
            q.push( &req );
        } else if (type == list_users) {
            request_list req = coder::decode_request_list( string_buffer );
            if(flag) req.getFrom() = socketToName[*incomingSocket];
            q.push( &req );
        } else if (type == PRIVATE_MESSAGE) {
            request_private_message req = coder::decode_request_private_message( string_buffer );
            if(flag) req.getFrom() = socketToName[*incomingSocket];
            q.push( &req );
        } else if (type == DISCONNECT) {
            request_disconnect req = coder::decode_request_disconnect( string_buffer );
            if(flag) req.getFrom() = socketToName[*incomingSocket];
            q.push( &req );
        }
        queueMutex.unlock();
        
        work.release(); // to signal a working thread to start working

        if( req.reques_t == DISCONNECT ){
            break; // when disonnecting, reach pthread_exit to kill the thread
        }

    }

    close(*incomingSocket);
    pthread_exit(NULL); // only kill thread when connections requests to die.

}


//checked
void connectRequest( request_connect req ){
    reply_connect rep;

    try{
        if( nameToSocket.find( req.getuserName() ) == nameToSocket.end() ){
            rep.setReplyId( req.getrequestId() );
            rep.setRepType( connect_CR ); 
            rep.setStatus( 200 );
            rep.setServerMessage( "Username Already taken!" );
        }
        else{
            nameToSocket[ req.getuserName() ] = req.getSocket();
            socketToName[ req.getSocket() ] = req.getuserName(); 
            rep.setReplyId( req.getrequestId() );
            rep.setRepType( connect_CR ); 
            rep.setStatus( 200 );
            rep.setServerMessage( "Connected Succesfully" );
        }
    }
    catch (const exception& e){
        rep.setReplyId( req.getrequestId() ); 
        rep.setRepType( connect_CR ) ;
        rep.setStatus( 500 ) ;
        rep.setServerMessage( "Could not connect succesfully" );
    }
    
    string string_buffer = coder::encode_reply_connect( rep );
    send( req.getSocket(), string_buffer.c_str(), string_buffer.size(), 0 );

}

//checked
void listRequest( request_list req ){  
    reply_list_CR rep;
    rep.setRepType( list_CR ) ;
    rep.setReplyId( req.getrequestId() );
    vector<chatroom_t> rooms;
    try{
        for ( chatroom_t cr: CR ){
            rooms.push_back(cr);
        }
        rep.setChatrooms( rooms );
        rep.setStatus( 200 );
        rep.setServerMessage( "Succesful" );
    }
    catch (const exception& e){
        rep.setStatus( 500 ) ;
        rep.setServerMessage( "fail" );
    }    
    string string_buffer = coder::encode_reply_list_CR( rep );
    send( req.getSocket(), string_buffer.c_str(), string_buffer.size(), 0 );
    
}

int roomCount = 0;
// TODO
//checked
void createRequest( request_create_CR req ) {
    reply_create_CR rep;
    rep.setRepType( create_CR );
    rep.setReplyId( req.getrequestId() );
    chatroom_t cur = req.getChatroom();
    try{
        rep.setChatroom( cur );
        CR.insert( cur );
        rep.setServerMessage("created Room succesfully");
        rep.setStatus( 200 );
    }
    catch (const exception &e){
        rep.setServerMessage(" Failed in creating room ");
        rep.setStatus( 500 );
    }

    string string_buffer = coder::encode_reply_create_CR( rep );
    send( req.getSocket(), string_buffer.c_str(), string_buffer.size(), 0 );
    
}

//checked 
void joinRequest( request_JLD_CR req ){
    reply_JLD_CR rep;
    rep.setRepType( join_CR );
    rep.setReplyId( req.getrequestId() );
    try{
        bool flag = false;

        for (chatroom_t cr : CR){
            if( cr.getchatroomID() == req.getchatroomID() ){
                cr.getMembers().insert( req.getFrom() );
                flag = true;
                break;
            }
        }

        if( ! flag ){
            rep.setServerMessage( "No Such Room ");
            rep.setChatroomId(-1);
        }
        rep.setStatus(200);
    }
    catch(const exception &e){
        rep.setServerMessage("Failed in room joining");
        rep.setStatus(500);
    }
    string string_buffer = coder::encode_reply_JLD_CR( rep );
    send( req.getSocket(), string_buffer.c_str(), string_buffer.size(), 0 );
}


//
void leaveRequest( request_JLD_CR req ){
    reply_JLD_CR rep;
    rep.setRepType( leave_CR );
    rep.setReplyId( req.getrequestId() );
    try{
        bool flag = false;
        for( chatroom_t cr : CR ){
            if( cr.getchatroomID() == req.getrequestId() ){
                cr.getMembers().erase( req.getFrom() );
                rep.setServerMessage( "left room ");
                rep.setStatus( 200 );
                flag = true;
            }
        }
        if( ! flag ){
            rep.setServerMessage("Not in that chatroom");
            rep.setStatus(200);
        }
    }
    catch( const exception &e ){
        rep.setServerMessage( "Failed to leave room" );
        rep.setStatus(500);
    }
    string string_buffer = coder::encode_reply_JLD_CR( rep );
    send( req.getSocket(), string_buffer.c_str(), string_buffer.size(), 0 );
}

//checked
void deleteRequest( request_JLD_CR req ){
    reply_JLD_CR rep;
    rep.setRepType( delete_CR );
    rep.setReplyId( req.getrequestId() );
    try{
        bool flag = false;
        for( chatroom_t cr : CR ){
            if( cr.getchatroomID() == req.getchatroomID() ){
                if( cr.getMembers().size() != 1 ){
                    for( id s: cr.getMembers() ){
                        if( s != cr.getOwner() ){
                            request_JLD_CR reqt;
                            reqt.setChatroomID( req.getchatroomID() );
                            reqt.setRequestId( req.getrequestId() );
                            reqt.setFrom( s );
                            reqt.setReqType( leave_CR );
                            queueMutex.lock();
                            q.push( &reqt ); // requesting people to leave the chatroom before deletion
                            queueMutex.unlock();
                        }
                    }    
                    queueMutex.lock();
                    q.push( &req );
                    queueMutex.unlock();
                    rep.setServerMessage( "delete chatroom request delayed until room is empty" );
                    rep.setStatus(200);
                }
                else{

                    CR.erase( cr );
                    rep.setServerMessage("Room Deleted Succesfully");
                    rep.setStatus(200);
                }
                rep.setChatroomId( req.getchatroomID() );
                break;
            }
        }
        if( !flag ){   
            rep.setServerMessage( "Did not find room to Delete" );
            rep.setStatus(200);
        }
    }
    catch( const exception &e){
        rep.setServerMessage( "Delete Room request Failed");
        rep.setStatus(500);
    }
    string string_buffer = coder::encode_reply_JLD_CR( rep );
    send( req.getSocket(), string_buffer.c_str(), string_buffer.size(), 0 );
}

//checked
void broadcastRequest( request_broadcast_message req ){
    reply_broadcast_message rep;
    rep.setChatroomId( req.getchatroomID() );
    rep.setMessage( req.getMessage() );
    try{
        for( chatroom_t cr: CR){
            if( cr.getchatroomID() == req.getchatroomID() ){
                for( id person: cr.getMembers() ){
                    request_private_message reqt;
                    reqt.setRequestId( req.getrequestId() );
                    reqt.setReqType( PRIVATE_MESSAGE );
                    reqt.setFrom( person );
                    reqt.setUserId( person );
                    reqt.setMessage( req.getMessage() );
                    queueMutex.lock();
                    q.push( &reqt );
                    queueMutex.unlock();
                }
                rep.setServerMessage( "Send Succesfully " );
                rep.setStatus(200);
                break;
            }
        }
    }
    catch( const exception &e){
        rep.setServerMessage( "Delete Room request Failed");
        rep.setStatus(500);
    }
    string string_buffer = coder::encode_reply_broadcast_message( rep );
    send( req.getSocket(), string_buffer.c_str(), string_buffer.size(), 0 );
}

//checked
void privateMessageRequest( request_private_message req ){
    reply_private_message rep;
    rep.setRepType( PRIVATE_MESSAGE );
    rep.setReplyId( req.getrequestId() );
    try{
        rep.setMessage( req.getMessage() );
        rep.setUserId( req.getuserId() );
        rep.setStatus( 200 );
        rep.setServerMessage( "Message delivered succesfully" );
    }
    catch( const exception &e ){
        rep.setStatus(500);
        rep.setServerMessage("Failed to transmit a private msg");
    }
    string string_buffer = coder::encode_reply_private_message( rep );
    send( req.getSocket(), string_buffer.c_str(), string_buffer.size(), 0 );
}

void listUsersRequest( request_list req ){
    reply_list_users rep;
    rep.setReplyId( req.getrequestId() );
    rep.setRepType( list_users );
    try{
        vector<id> users;
        set<id> S;
        for( chatroom_t cr: CR ){
            for( id person: cr.getMembers() ){
                S.insert( person );
            }
        }
        for( id person: S ){
            users.push_back( person );
        }
        sort( users.begin(), users.end() ); // return the list alphabetically 
        rep.setUsers( users );
        rep.setServerMessage( "List Sent Succesfully" );
        rep.setStatus( 200 );

    }
    catch( const exception &e ){
        rep.setStatus( 500 );
        rep.setServerMessage( "Failed to list members of chatroom" );
    }
    string string_buffer = coder::encode_reply_list_users( rep );
    send( req.getSocket(), string_buffer.c_str(), string_buffer.size(), 0 );
}

//checked
void disconnectRequest( request_disconnect req ){
    for( chatroom_t cr: CR ){
        for( id person : cr.getMembers() ){
            if( person == req.getFrom() ){
                cr.getMembers().erase( person );
            }
        }
    }
}




void * workingThread( void * index ){ // no input taken here

    while(true){

        work.acquire(); // only to avoid bounded waiting

        queueMutex.lock();
        request * req = q.front();
        q.pop();
        queueMutex.unlock();

        if( req->getrequestId() == connect_CR ){
            request_connect* reqn = ( request_connect * ) req;
            connectRequest( *reqn );
        }
        else if( req->getrequestId() == list_CR ){
            request_list* reqn = ( request_list * ) req;
            listRequest( *reqn );
        }
        else if( req->getrequestId() == create_CR ){
            request_create_CR* reqn = ( request_create_CR* ) req;
            createRequest( *reqn  ); 
        }
        else if( req->getrequestId() == join_CR ){
            request_JLD_CR* reqn = ( request_JLD_CR* ) req;
            joinRequest( *reqn );
        }
        else if( req->getrequestId() == leave_CR ){
            request_JLD_CR* reqn = ( request_JLD_CR* ) req;
            leaveRequest( *reqn );
        }
        else if( req->getrequestId() == delete_CR ){
            request_JLD_CR* reqn = ( request_JLD_CR* ) req;
            deleteRequest( *reqn );
        }
        else if( req->getrequestId() == BROADCAST_MESSAGE ){
            request_broadcast_message* reqn = ( request_broadcast_message* ) req;
            broadcastRequest( *req );
        }
        else if( req->getrequestId() == list_users){
            request_list* reqn = ( request_list* ) req;
            listUsersRequest( *reqn );
        }
        else if( req->getrequestId() == DISCONNECT ){
            request_disconnect* req = ( request_disconnect* ) req;
            disconnectRequest( *req );
        }
    }

} 


int main()
{

    pthread_t threads[1000];
    pthread_t wThreads[30];


    for(int i = 0 ; i < 30; i++){
        int err = pthread_create( &wThreads[i], NULL, workingThread, NULL ) ;
        if( err != 0 ) cout << " something is wrong working thread ";
    }

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress;
    socklen_t addrlen = sizeof(serverAddress);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);
    if ( bind( serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress) ) < 0)
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

        int incoming;
        // Taking in requests, if one arrives before accept then it queues up and accept does not block
        // Otherwise accept blocks and waits until a connect request occurs
        if ( (incoming = accept(serverSocket, (struct sockaddr *)&serverAddress, &addrlen)) < 0 )
        {
            // handling potential error
            perror(" accept failed ");
            exit(EXIT_FAILURE);
        }
 
        int err = pthread_create( &threads[userCounter++], NULL, listeningThread, &incoming );
        if( err != 0 ) cout << " something is wrong " << '\n';
    
        // make a reply containing chat rooms available
        // available rooms sent
    }

    return 0;
}