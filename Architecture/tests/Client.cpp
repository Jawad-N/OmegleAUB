#include <iostream>
#include <string>
#include <sstream>
using namespace std;

string username = "";

void displayPrompt(const std::string &message = "")
{
    // Display command prompt
    std::cout << "omegleAUB@" << username << " > ";

    // Display additional message
    if (!message.empty())
        std::cout << message << " ";
}

std::string getUserInput()
{
    // Display command prompt
    displayPrompt();

    // Read user input
    std::string userInput;
    std::getline(std::cin, userInput);

    return userInput;
}

std::string getUserInput(string s)
{
    // Display command prompt
    displayPrompt(s);

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
        return false;

    return true;
}

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

class TaskHandler
{
public:
    void handleTask(int task)
    {
        switch (task)
        {
        case 0:
            std::cout << "Connecting to server..." << std::endl;
            handle_connect();
            break;
        // Add more cases for other tasks as needed
        default:
            std::cout << "Invalid task." << std::endl;
            break;
        }
    }

    void handle_connect()
    {
        // Take the username from the user
        username = getUserInput("[server] Enter username: ");
        // Display a message after connecting
        displayPrompt("Connected as " + username);
    }
};

int main()
{
    // Command history
    std::string commandHistory;

    // Task handler
    TaskHandler taskHandler;

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
            // Handle the parsed integer using the task handler
            taskHandler.handleTask(parsedInt);
        }

        // Parse user input
        else if (userInput == "h")
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
