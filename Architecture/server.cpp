#include<bits/stdc++.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include<chrono>
#include<ctime>

using namespace std;

map<int, vector<int>> CR;
vector<int> sockets; // sockets are filedescriptors

struct msg{

    int to;
    int from;
    string s;
    time_t sendingTime;

};

// server sending to client
// first time will send the options then wait for a send 
void * pickAndListenThread( void * incomingSocket ){ // index will be the address of the incoming request; 
    incomingSocket = (int *) incomingSocket;
    string choices = "";
    for(pair<int,vector<int>> p: CR){
        choices += str(p.first) + " ";
    }
    send( *incomingSocket, choices, choices.size(), 0);
    char* buffer[1024] = { 0 };
    ssize_t bytes_received = recv( *(incomingSocket), buffer, sizeof(buffer), MSG_WAITALL);

    // now we wait for the response, we will agree on the format
    // based on the format add him to the correct group

    // Manipulate CR according to his joining request;

    // Wait until further requests are done



    while(true){

        char buffer[1024] = { 0 };
        ssize_t valread = recv(incomingSocket, buffer, sizeof(buffer), MSG_WAITALL);
        // read msg into buffer, next create threads to send for each of the servers
        request = decode(buffer);
        if(request.type)...

        // after decoding
        // msg will also be decoded
        for(int i: receivers){

            pthread_create(&thread[id][0], NULL, broadcastThread, message);
        }



        if(connectionRequestToDie == 1) break;
    }

    close(incomingSocket);
    pthread_exit(NULL) // only kill thread when connections requests to die.

}



void * broadcastThread( void * index ){

    // index will have a msg struct that includes recipient and sender, and we will send this msg to everyone
    // receiving thread will redirect us here with a destination that is each of the recipients
    
    index = *(msg *) index;
    // encode msg using hashem's
    char * buffer[1024] = { 0 };
    buffer = encoding(index) // TODO
    send(index->to, buffer, strlen(buffer), 0); // to will be based on socket

    pthread_exit(NULL);    

}





int main(){



    CR[0] = {}; // mainRoom
    pthread_t threads[1000][2];
    int offset = 1024;

    while(true){

        int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in serverAddress;
        socklen_t addrlen = sizeof(serverAddress);
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY; 
        serverAddress.sin_port = htons(offset++); 

        //giving a port to the socket and a protocol, i.e. creating the socket
        if ( bind( serverSocket, ( struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0){ 
            //handling potential errors
            perror(" bind failed ");
            exit(EXIT_FAILURE);
        }
        //Giving the socket the capacity to listent to incoming communication
        if( listen(serverSocket,3) < 0 ){
            //handling potential error
            perror(" listen failed ");
            exit(EXIT_FAILURE); 
        }
        int incoming;
        //Taking in requests, if one arrives before accept then it queues up and accept does not block
        //Otherwise accept blocks and waits until a connect request occurs
        if( incoming = accept(serverSocket, (struct sockaddr*)& serverAddress, &addrlen) < 0 ){
            //handling potential error
            perror(" accept failed ")
            exit(EXIT_FAILURE);
        }

        char* buffer[1024] = { 0 };
        // accepted incoming request, connecting it to a thread

        int valread = recv( incoming, buffer, 1024-1, 0); //reading into buffer
        //decoding and get id;

        // creating two threads for two operations
        // first replies to the user with a list of ChatRooms
        // the other listens to broadcast requests from user to some ChatRoom that he plays part in
        pthread_create( &thread[id][1], NULL, pickAndListenThread, &incoming );

    
        // make a reply containing chat rooms available
        // available rooms sent

    }

    return 0;
}