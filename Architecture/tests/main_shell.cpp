#include "../headers/OmegleShell.h"

int main()
{

    int clientSocket;
    if ((clientSocket = (clientSocket = socket(AF_INET, SOCK_STREAM, 0))) < 0)
        ;
    struct sockaddr_in serverAddress;
    socklen_t addrlen = sizeof(serverAddress);

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);

    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0)
    {
        cout << "Invalid" << '\n';
        return -1;
    }

    int status;
    if ((status = connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress))) < 0)
    {
        cout << status << '\n';
        perror("Connection error");
        return -1;
    }

    OmegleShell myshell(clientSocket);
    myshell.run();
}

/*
    string string_buffer = coder::encode_request_disconnect( req ); //corresponding encoding
    send( *clientSocket, string_buffer.c_str(), string_buffer.size(), 0);

*/

/*
    char * buffer;
    valread = read( *clientSocket, buffer, sizeof(buffer) );
    string string_buffer = (string) buffer;
    request_t type = coder::get_encode_reply_type(string_buffer);

*/