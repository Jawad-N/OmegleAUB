
#include "includes.h"
#include "structures.h"
class C_handler
{
private:
    string username = "";

public:
    // string getUserInput()
    string getUserInput();

    // Display prompt
    void displayPrompt();
    // Show help
    void showHelp();

    // Connect to server
    void connectToServer(string username);

    // List available Chatrooms
    void listAvailableChatrooms();

    // Create Chatroom
    void createChatroom();

    // Join Chatroom
    void joinChatroom(int chatroom_id);

    // Leave Chatroom
    void leaveChatroom(int chatroom_id);

    // Delete Chatroom
    void deleteChatroom(int chatroom_id);

    // Broadcast Message to a chatroom
    void broadcastMessage(int chatroom_id, message_t message);

    // List Users
    void listUsers();

    // Private Message a user
    void privateMessageUser(id user_id, message_t message);

    // Disconnect
    void disconnect();

    // List Details of a certain chatroom
    void listChatroomDetails(int chatroom_id);

    // Show message history of a certain chatroom
    void showMessageHistory(int chatroom_id);

    // Show command history
    void showCommandHistory();
};

/*
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
*/