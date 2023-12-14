#include <iostream>
#include <string>
#include <sstream>
#include <limits>

string username = "";

void showHelp()
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

std::string getUserInput()
{
    // Display command prompt

    std::cout << "omegleAUB@ {{username}} > ";

    // Read user input
    std::string userInput;
    std::getline(std::cin, userInput);

    return userInput;
}

bool tryParseInt(const std::string &str, int &result)
{
    std::istringstream ss(str);
    ss >> result;

    if (ss.fail() || !ss.eof())
    {
        // Parsing failed
        return false;
    }

    return true;
}

int main()
{
    // Command history
    std::string commandHistory;

    // Main command loop
    while (true)
    {
        // Read user input using the function
        std::string userInput = getUserInput();

        // Update command history
        commandHistory += userInput + '\n';

        // Try to parse as an integer
        int parsedInt;
        if (tryParseInt(userInput, parsedInt))
        {
            std::cout << "Parsed integer: " << parsedInt << std::endl;
        }

        // Parse user input
        if (userInput == "h")
        {
            showHelp();
        }
        else if (userInput == "hist")
        {
            // Show command history
            std::cout << "Command History:\n"
                      << commandHistory;
        }
        else if (userInput == "exit")
        {
            // Exit the program
            break;
        }
        else
        {
            // Unrecognized command
            std::cout << "Unrecognized command " << '"' << userInput << '"' << ". Type 'h' for help." << std::endl;
        }
    }

    return 0;
}
