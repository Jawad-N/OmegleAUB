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
#include<arpa/inet.h>
#include "headers/structures.h"
#include "headers/utilities.h"
#include "headers/request.h"
#include "headers/reply.h"
#include "headers/coder.h"
using namespace std;


set<int> chatrooms;
set<id> users;
map<int, request> pending_requests;
id name;


void * listening( void * IS ){
    cout << "listening\n"; cout.flush();
    int *clientSocket = (int*) IS;
    while( true ){
        char buffer[ 1024 ] = { 0 };
        ssize_t valread = 0 ;
        cout << "pre: " << valread << '\n';
        cout.flush();
        valread = read( *clientSocket, buffer, sizeof(buffer) );
        cout << "post: " << valread << '\n';
        cout.flush();
        string string_buffer = (string) buffer;
        request_t type = typecoder::get_encode_reply_type(string_buffer);
        if( type == connect_CR ){
            cout << coder::decode_reply_connect( string_buffer ) << '\n';
        }
        else if( type == list_CR ){
            cout << coder::decode_reply_list_CR( string_buffer ) << '\n';
        }
        else if( type == create_CR ){
            cout << coder::decode_reply_create_CR( string_buffer ) << '\n';
        }
        else if( type == join_CR ){
            cout << coder::decode_reply_JLD_CR( string_buffer ) << '\n';
        }
        else if( type == leave_CR ){
            cout << coder::decode_reply_JLD_CR( string_buffer ) << '\n';
        }
        else if( type == delete_CR ){
            cout << coder::decode_reply_JLD_CR( string_buffer ) << '\n';
        }
        else if( type == BROADCAST_MESSAGE ){
            cout << coder::decode_reply_broadcast_message( string_buffer ) << '\n';
        }
        else if( type == list_users ){
            cout << coder::decode_reply_list_users( string_buffer ) << '\n';
        }
        else if( type == PRIVATE_MESSAGE ){
            cout << coder::decode_reply_private_message( string_buffer ) << '\n';
        }
        cout.flush();
    }
}








void * sending( void * IS ){
    
    int * clientScoket = ( int* ) IS;
    
    assume we have the type and the request elements

    try{

        
    }

    
 
}










int main(){

    pthread_t listeningThread;
    pthread_t sendingThread;

    string nameHandle;
    cout << "Specify Username Please: "; cin >> nameHandle;

    int clientSocket ;
    if( ( clientSocket = (clientSocket = socket(AF_INET, SOCK_STREAM, 0) ) ) < 0 );
    struct sockaddr_in serverAddress;
    socklen_t addrlen = sizeof(serverAddress);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);

    if ( inet_pton( AF_INET, "127.0.0.1", &serverAddress.sin_addr ) <= 0 ){
        cout << "Invalid" << '\n';
        return -1;
    }

    int status;
    if( ( status = connect( clientSocket, (struct sockaddr*) &serverAddress , sizeof(serverAddress) ) ) < 0  ){
        cout << status << '\n';
        perror("Connection error");
        return -1;
    }

    request_connect req(nameHandle);
    string string_buffer = coder::encode_request_connect(req);
    send(clientSocket, string_buffer.c_str(), string_buffer.size(), 0);
    pthread_create( &listeningThread, NULL, listening, &clientSocket);
    // pthread_create( &sendingThread, NULL, sending, &clientSocket );
    void * status2;
    pthread_join(listeningThread, &status2);
    pthread_join(sendingThread, &status2);


    return 0;
}