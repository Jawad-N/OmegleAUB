#include <bits/stdc++.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <chrono>
#include <ctime>

using namespace std;

map<int, vector<int>> CR;
vector<int> sockets; // sockets are filedescriptors

// server sending to client
// first time will send the options then wait for a send
void *sendingThread(void *index)
{ // index will be the specific

    string choices = "";
    for (pair<int, vector<int>> p : CR)
    {
        reply += str(p.first) + " ";
    }
    send(*index, reply, strlen(reply), 0);
}

// server receiving from client either an order or a request
void *receivingThread(void *index)
{
}

struct msg
{

    int from;
    string s;
    time_t sendingTime;
};

int main()
{

    CR[0] = {}; // mainRoom
    pthread_t threads[1000][2];
    int offset = 1024;

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
        if (listen(serverSocket, 3) < 0)
        {
            perror(" listen failed ");
            exit(EXIT_FAILURE);
        }
        int incoming;
        if (incoming = accept(serverSocket, (struct sockaddr *)&serverAddress, &addrlen) < 0)
        {
            perror(" accept failed ")
                exit(EXIT_FAILURE);
        }
        int valread;
        char *buffer[1024] = {0};
        valread = read(incoming, buffer, 1024 - 1); // reading into buffer
        // decoding and get id;

        pthread_create(&thread[id][0], NULL, receivingThread, NULL);
        pthread_create(&thread[id][1], NULL, sendingThread, &incoming);

        // make a reply containing chat rooms available
        // available rooms sent
    }

    return 0;
}