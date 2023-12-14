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


void * listening( void * input ){

}
void * sending( void * input ){

}







int main(){
>>>>>>> a91de25123cc0595d7ccacd48adc216933027785

    pthread listeningThread;
    pthread sendingThread;

<<<<<<< HEAD
=======

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress;
    socklen_t addrlen = sizeof(serverAddress);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(4000);
    
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
    if ( (incoming = accept(serverSocket, (struct sockaddr *)&serverAddress, &addrlen)) < 0 )
    {
        // handling potential error
        perror(" accept failed ")
            exit(EXIT_FAILURE);
    }

    int err = pthread_create( &thread[userCounter++], NULL, listeningThread, &incoming );
    if( err != 0 ) cout << " something is wrong " << '\n';

    // make a reply containing chat rooms available
    // available rooms sent




>>>>>>> a91de25123cc0595d7ccacd48adc216933027785
    return 0;
}