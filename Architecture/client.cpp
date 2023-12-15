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
        valread = read( *clientSocket, buffer, sizeof(buffer) );
        string string_buffer = (string) buffer;
        request_t type = coder::get_encode_reply_type(string_buffer);
        
        if( type == list_CR ){
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
    
    int * clientSocket = ( int* ) IS;
    while(true){
        int n; cout << "pick command 1-->10: "; cin >> n; 
        request_t type = (request_t)n;
        cout << type << '\n';
        try{
            if( type == list_CR ){
                
                request_list req = request_list(list_CR);
                string string_buffer = coder::encode_request_list( req );
                send( *clientSocket, string_buffer.c_str(), string_buffer.size(), 0);
                
            }
            else if( type == create_CR ){

                chatroom_t newRoom = chatroom_t();
                string roomName; cout << "Give Room Name: "; cin >> roomName;
                newRoom.setName(roomName);
                request_create_CR req = request_create_CR( newRoom );
                string string_buffer = coder::encode_request_create_CR( req );            
                send( *clientSocket, string_buffer.c_str(), string_buffer.size(), 0 );

            }
            else if( type == join_CR ){
                int roomID;
                cout << "Pick A Room To Join By ID Number: "; cin >> roomID;
                request_JLD_CR req = request_JLD_CR( join_CR, roomID );
                string string_buffer = coder::encode_request_JLD_CR( req );            
                send( *clientSocket, string_buffer.c_str(), string_buffer.size(), 0 );
                
            }
            else if( type == leave_CR ){
                int roomID;
                cout << "Pick A Room To Leave By ID: "; cin >> roomID;
                request_JLD_CR req = request_JLD_CR( leave_CR, roomID );
                string string_buffer = coder::encode_request_JLD_CR( req );            
                send( *clientSocket, string_buffer.c_str(), string_buffer.size(), 0 );
                
            }
            else if( type == delete_CR ){
                int roomID;
                cout << "Pick A Room To Delete By ID: "; cin >> roomID;
                request_JLD_CR req = request_JLD_CR( delete_CR, roomID );
                string string_buffer = coder::encode_request_JLD_CR( req );            
                send( *clientSocket, string_buffer.c_str(), string_buffer.size(), 0 );
            }
            else if( type == BROADCAST_MESSAGE ){
                string s; cout << "Enter MSG: "; cin >> s;
                request_broadcast_message req = request_broadcast_message( req );
                string string_buffer = coder::encode_request_broadcast_message( req ); 
                cout << coder::decode_reply_broadcast_message( string_buffer ) << '\n';
            }
            // else if( type == list_users ){
            //     cout << coder::decode_reply_list_users( string_buffer ) << '\n';
            // }
            // else if( type == PRIVATE_MESSAGE ){
            //     cout << coder::decode_reply_private_message( string_buffer ) << '\n';
            // }
            else if( type == DISCONNECT ){
                request_disconnect req = request_disconnect( DISCONNECT );
                string string_buffer = coder::encode_request_disconnect( req );
                send( *clientSocket, string_buffer.c_str(), string_buffer.size(), 0);
            }
        }
        catch( const exception &e ){
            cout << "Input error" << '\n';
        }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
 
}










int main(){

    pthread_t listeningThread;
    pthread_t sendingThread;

   
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


    char buffer[ 1024 ] = { 0 };
    bool connect = false;
    string nameHandle; cout << "Specify Username Please: "; cin >> nameHandle;
    request_connect req(nameHandle);
    string string_buffer = coder::encode_request_connect(req);
    send(clientSocket, string_buffer.c_str(), string_buffer.size(), 0);

    int valread = read( clientSocket, buffer, sizeof(buffer) );
    reply_connect rep =  coder::decode_reply_connect( buffer );
    if( rep.getserverMessage() == "Connected Succesfully" ) connect = true;
    while( !connect ){
        string nameHandle;
        cout << rep.getserverMessage() <<'\n';
        cout << "Please Provide A Different Username: "; cin >> nameHandle;
        request_connect reqRetry(nameHandle);
        string string_buffer = coder::encode_request_connect(reqRetry);
        memset(buffer, '\0', sizeof(buffer));
        send(clientSocket, string_buffer.c_str(), string_buffer.size(), 0);
        valread = read( clientSocket, buffer, sizeof(buffer) );
        rep = coder::decode_reply_connect( buffer );
        if( rep.getserverMessage() == "Connected Succesfully" ) connect = true;
    }
    cout << rep << '\n';
    pthread_create( &listeningThread, NULL, listening, &clientSocket);
    pthread_create( &sendingThread, NULL, sending, &clientSocket );
    void * status2;
    pthread_join(listeningThread, &status2);
    pthread_join(sendingThread, &status2);

    return 0;
}