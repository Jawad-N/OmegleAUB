#include "../headers/client.h"

const char *welcome_main =
    "Welcome to OmegleAUB, the first of ... available chatting applications. ";
const char *help =
    "Choose one of the options listed below:\n"
    "Options:\n"
    "    h    : Show this help\n"
    "    0    : Connect to server\n"
    "    1    : List available Chatrooms\n"
    "    2    : Create Chatroom\n"
    "    3    : Join Chatroom\n"
    "    4    : Leave Chatroom\n"
    "    5    : Delete Chatroom\n"
    "    6    : Broadcast Message to a chatroom\n"
    "    7    : List Users\n"
    "    8    : Private Message a user\n"
    "    9    : Disconnect\n"
    "    10   : List Details of certain chatroom\n"
    "    11   : Show message history of certain chatroom\n"
    "    hist : Show command history";
string username = "~~~~";
const char *terminal =
    "$omegleAUB@{{user}}>";
class CLI
{
public:
    CLI();
};

int main()
{
    // Client jawad;
    cout << welcome_main << '\n'
         << help << '\n'
         << terminal;

    // // // // // // // // // // //
}

/**
 * Welcome to OmegleAUB, the first of ... available chatting applications. Choose one of the options listed below:
Options:
    h    : Show this to help
    0    : Connect to server
    1    : List availabe Chatrooms
    2    : Create Chatrooms
    3    : Join Chatroom
    4    : Leave Chatroom
    5    : Delete Chatroom
    6    : BroadCast Message to a chatroom
    7    : List Users
    8    : Private Message a user
    9    : Disconnect
    10   : List Details of certain chatroom
    11   : Show message history of certain chatroom
    hist : Show command history
$omegleAUB@{{user}}>  0

 *
 */