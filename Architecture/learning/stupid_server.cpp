#include <bits/stdc++.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

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