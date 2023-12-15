#include "../headers/C_handler.h"
#include "../headers/structures.h"
int main()
{
    Client jawad();
    string commandHistory = "";

    // Intialize client
    // Initialize command history variable
    // Initialize taskHandler
    // Main loop
    // //  input = read_user_input
    // // try to parse it to integer
    // // taskHandler(user_input);

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
