#include "../headers/C_handler.h"

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