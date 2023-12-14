#include <bits/stdc++.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;

/*
class Server
{
public:
    int serverSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    int S_port = -1;
    Server(int port)
    {
        S_port = port;
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        int bind_status = bind(serverSocket,
                               (struct sockaddr *)&serverAddr,
                               sizeof(serverAddr));
        if (bind == -1)
        {
            cout << "Binding to port " << port << " failed :(\n";
            exit(0);
        }
        if (listen(serverSocket, 50) == 0)
            cout << "Server listening at port " << port << " ...\n";
        else
        {
            cout << "Server failed to listen at port " << port << ":( \n";
            exit(1);
        }
    }
};
*/


int userCounter = 0;
int main()
{

    pthread_t threads[1000];
    pthread_t wThreads[30];


//    for(int i = 0 ; i < 30; i++){
        //int err = pthread_create( &wThreads[i], NULL, workingThread, NULL ) ;
        //if( err != 0 ) cout << " something is wrong working thread ";
//  }

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
        char buffer[1024] = { 0 }; 
        ssize_t valread = recv(incoming, buffer, sizeof(buffer), MSG_WAITALL);
        cout << "Received: " << buffer << '\n';
        //int err = pthread_create( &thread[userCounter++], NULL, listeningThread, &incoming );
        //if( err != 0 ) cout << " something is wrong " << '\n';
    
        // make a reply containing chat rooms available
        // available rooms sent
    }

    return 0;
}