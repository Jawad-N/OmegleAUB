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
#include "Architecture/headers/structures.h"
#include "Architecture/headers/utilities.h"
#include "Architecture/headers/request.h"
#include "Architecture/headers/reply.h"
using namespace std;

<<<<<<< HEAD
int main()
{
=======

set<int> chatrooms;
set<id> users;
map<int, request> pending_requests;
id name;


void * listening( void * IS ){
    int *clientSocket = (int*) IS;
    while( true ){

        char buffer[ 1024 ] = { 0 };
        ssize_t valread = recv(incomingSocket, buffer, sizeof(buffer), MSG_WAITALL);
        string string_buffer = (string) buffer;
        reply rep = decode(buffer);
        //handle reply

    }
}
void * sending( void * IS ){
    
    int * clientScoket = ( int* ) IS;
    
 
}







int main(){
>>>>>>> a91de25123cc0595d7ccacd48adc216933027785

    pthread listeningThread;
    pthread sendingThread;

<<<<<<< HEAD
=======

    int clientSocket ;
    if( clientSocket = (clientSocket = socket(AF_INET, SOCK_STREAM, 0) ) < 0 );
    struct sockaddr_in clientAddress;
    socklen_t addrlen = sizeof(clientAddress);

    clientAddress.sin_family = AF_INET;
    clientAddress.sin_addr.s_addr = INADDR_ANY;


    if ( inet_pton( AF_INET, "127.0.0.1", &clientAddress.sin_addr ) <= 0 ){
        cout << "Invalid" << '\n';
        return -1;
    }

    
    if( ( status = connect( clientSocket, (struct sockaddr*) &clientAddress ), sizeof(client) ) < 0  ){
        cout << "Invalid2" << '\n';
    }


    send(clientSocket, hello, strlen(hello), 0);
    cout << "Hello sent\n" << '\n';

    pthread_create( &listeningThread, NULL, listening, &clientSocket)




>>>>>>> a91de25123cc0595d7ccacd48adc216933027785
    return 0;
}