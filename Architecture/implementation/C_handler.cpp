#include "../headers/C_handler.h"
#include "../headers/request.h"
#include "../headers/coder.h"
void C_handler::showHelp()
{
    // Display the help message
    std::cout << "Options:\n"
              << "    h    : Show this help\n"
              << "    0    : Connect to server\n"
              << "    1    : List available Chatrooms\n"
              << "    2    : Create Chatroom\n"
              << "    3    : Join Chatroom\n"
              << "    4    : Leave Chatroom\n"
              << "    5    : Delete Chatroom\n"
              << "    6    : Broadcast Message to a chatroom\n"
              << "    7    : List Users\n"
              << "    8    : Private Message a user\n"
              << "    9    : Disconnect\n"
              << "    10   : List Details of a certain chatroom\n"
              << "    11   : Show message history of a certain chatroom\n"
              << "    hist : Show command history" << std::endl;
}

void C_handler::displayPrompt()
{
    // Display command prompt
    std::cout << "omegleAUB@" << username << " > ";
}

string C_handler::getUserInput()
{
    displayPrompt();
    // Read user input
    std::string userInput;
    std::getline(std::cin, userInput);

    return userInput;
}

void C_handler::connectToServer(string username)
{
    // create request_connect
    request_connect req(username);

    // encode request_connect
    string encoding = coder::encode_request_connect(req);

    // send request_connect encoding
    // // send(encoding)
    // // if(send(encoding) != -1)
    // add request_connect to the pending_requests_queue
    client.getpendingRequests();
    // output waiting for the server's reply message
}

void C_handler::listAvailableChatrooms()
{

    // create request_list

    // encode request_list

    // send request_list encoding

    // add request_list to the pending requests queue

    // output waiting for the server's reply message
}

void C_handler::createChatroom(chatroom_t chatroom)
{
    // create request_create_CR
    // encode request_create_CR
    // send request_create_CR encoding
    // add request_list to the pending requests queue
    // output waiting for the server's reply message
}

void C_handler::joinChatroom(int chatroom_id)
{

    // create request_JLD_CR (join_CR)
    // encode request_JLD_CR (join_CR)
    // send request_JLD_CR (join_CR) encoding
    // add request_JLD_CR (join_CR) to the pending requests queue
    // output waiting for the server's reply message
}

void C_handler::leaveChatroom(int chatroom_id)
{
    // create request_JLD_CR (join_CR)
    // encode request_JLD_CR (join_CR)
    // send request_JLD_CR (join_CR) encoding
    // add request_JLD_CR (join_CR) to the pending requests queue
    // output waiting for the server's reply message
}