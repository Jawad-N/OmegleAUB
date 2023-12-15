#include "../headers/OmegleShell.h"
#include "../headers/request.h"
#include "../headers/reply.h"

#define RED_TEXT "\033[1;31m"
#define RESET_COLOR "\033[0m"
#define BLUE_TEXT(text) "\033[1;34m" << text << "\033[0m"
#define GREEN_TEXT(text) "\033[1;32m" << text << "\033[0m"
// // // // // // Parser class start // // // // // //
string Parser::trim_spaces(string input)
{
    if (input.size() == 0)
        return input;
    int i(0), j(input.size() - 1);
    while (i < input.size() && input[i] == ' ')
        i++;
    while (j >= 0 && input[j] == ' ')
        j--;
    if (j < i)
        return "";
    return input.substr(i, j - i + 1);
}
string Parser::parse_user_input(string message)
{
    string user_input;
    if (message.size() != 0)
        cout << message;
    getline(cin, user_input);
    return trim_spaces(user_input);
}

bool Parser::parse_int(string message, int &result)
{
    try
    {
        int res = stoi(message);
        result = res;
        return true;
    }
    catch (exception e)
    {
        return false;
    }
}
// // // // // // Parser class end // // // // // // //

// // // // // // OmegleShell start // // // // // // //
// string OmegleShell::getuserName() const { return user_name; }
// void OmegleShell::setUserName(const string &userName) { user_name = userName; }
OmegleShell::OmegleShell(int socketfd) { client.setSocketfd(socketfd); }
OmegleShell::OmegleShell() {}
void OmegleShell::displayWelcome() { cout << "\033[1;32mWelcome to My Bash Script!\033[0m\n"; }
void OmegleShell::displayHelp()
{
    cout << "\033[1;37mOptions:\n"
         << "    \033[1;36mh\033[0m    : Show this help\n"
         << "    \033[1;36m0\033[0m    : Connect to server\n"
         << "    \033[1;36m1\033[0m    : List available Chatrooms\n"
         << "    \033[1;36m2\033[0m    : Create Chatroom\n"
         << "    \033[1;36m3\033[0m    : Join Chatroom\n"
         << "    \033[1;36m4\033[0m    : Leave Chatroom\n"
         << "    \033[1;36m5\033[0m    : Delete Chatroom\n"
         << "    \033[1;36m6\033[0m    : Broadcast Message to a chatroom\n"
         << "    \033[1;36m7\033[0m    : List Users\n"
         << "    \033[1;36m8\033[0m    : Private Message a user\n"
         << "    \033[1;36m9\033[0m    : Disconnect\n"
         << "    \033[1;36m10\033[0m   : List Details of a certain chatroom\n"
         << "    \033[1;36m11\033[0m   : Show message history of a certain chatroom\n"
         << "    \033[1;36mhist\033[0m : Show command history\n"
         << "    \033[1;36mexit\033[0m : Exit command line\033[0m\n";
    ;
}
void OmegleShell::displayPrompt() { cout << "\033[1;32m" + (client.getName() == "" ? "guest" : client.getName()) + "@omegleAUB> " + "\033[0m"; }
void OmegleShell::displayHistory() { cout << user_command_history << '\n'; }
void OmegleShell::insertPendingRequestClient(int request_id, request req) { client.insertPendingRequest(request_id, req); }

bool OmegleShell::addchatrooms(int chatroom_id)
{
    client.addchatrooms(chatroom_id);
    return true;
}
bool OmegleShell::execute_command(string command)
{
    int command_int = -1;
    try
    {
        command_int = stoi(command);
        if (command_int >= 0 && command_int <= 11)
        {
            switch (command_int)
            {
            case 0:
                task_handler.handle_connect(*this);
                break;
            case 1:
                task_handler.handle_list_chatrooms(*this);
                break;
            case 2:
                task_handler.handle_create_chatroom(*this);
                break;
            case 3:
                task_handler.handle_join_chatroom(*this);
                break;
            case 4:
                task_handler.handle_leave_chatroom(*this);
                break;
            case 5:
                task_handler.handle_delete_chatroom(*this);
                break;
            case 6:
                task_handler.handle_broadcast_message(*this);
                break;
            case 7:
                task_handler.handle_list_users(*this);
                break;
            case 8:
                task_handler.handle_private_message(*this);
                break;
            case 9:
                task_handler.handle_disconnect(*this);
                break;
            case 10:
                task_handler.handle_display_chatroom_info(*this);
                break;
            case 11:
                task_handler.handle_display_chatroom_message_history(*this);
                break;
            default:
                /* default code */
                break;
            }

            return true;
        }
        else
        {
        }
    }
    catch (exception e)
    {
        cout << e.what() << '\n';
    }

    cout << "Unrecognized command " << '"' << command << '"' << ". Type 'h' for help.\n";
    return false;
}
void OmegleShell::run()
{
    displayWelcome();
    while (true)
    {
        displayPrompt();
        string user_input = Parser::parse_user_input("");

        user_command_history = user_command_history + user_input + "\n";

        if (user_input == "h")
            displayHelp();
        else if (user_input == "exit")
        {
            cout << "Thank you for your time at omegleAUB ... We hope to see you soon.\n";
            break;
        }
        else if (user_input == "hist")
            displayHistory();
        else
            execute_command(user_input);
    }
}

Client OmegleShell::getClient() const { return client; }
void OmegleShell::setClient(const Client &client_) { client = client_; }
void OmegleShell::setClientName(string client_)
{
    client.setName(client_);
}
void OmegleShell::setClientActivated(bool activate)
{
    client.setActivated(activate);
}
// // // // // // OmegleShell end // // // // // // //

// // // // // // Task Handler start // // // // // //
void TaskHandler::handle_connect(OmegleShell &shell)
{
    if (shell.getClient().getActivated())
    {
        cout << RED_TEXT << " [server] : user already connected" << RESET_COLOR << '\n';
        return;
    }
    cout << BLUE_TEXT("[server] : Attempting to connect to server\n");

    string user_name = Parser::parse_user_input("Enter your username: ");
    // Add allowed regular expersion filter.

    // create request_connect()
    request_connect req(user_name);
    cout << "Request:\n"
         << req;
    // encode request_connect()
    string encoding = coder::encode_request_connect(req);

    // send encoding to server
    shell.getClient().send_over_socket(encoding);
    // // client.send(encoding);

    // store the request inside the set.
    shell.insertPendingRequestClient(req.getrequestId(), req);

    string CONTENT = shell.getClient().receive_from_socket();
    reply_connect rep = coder::decode_reply_connect(CONTENT);
    // cout << coder::decode_reply_connect(CONTENT) << '\n';
    cout << "Reply : " << rep << '\n';
    string encoding_reply = "";

    if (rep.getStatus() / 200 <= 1) // if reply successful
    {
        shell.setClientName(user_name);
        shell.setClientActivated(true);
        cout << GREEN_TEXT("[server] : Welcome " + user_name + " to omegleAUB\n");
    }
    else
    {
        cout << RED_TEXT << "[server] : Connection failed. Please try again later.\n"
             << RESET_COLOR;
    }

    // shell.setUserName(user_name);
}
void TaskHandler::handle_list_chatrooms(OmegleShell &shell)
{
    if (!shell.getClient().getActivated())
    {
        cout << RED_TEXT << "[server] : Connect to server first before requesting\n"
             << RESET_COLOR;
        return;
    }

    request_list req(list_CR);
    string encoding = coder::encode_request_list(req);
    // send encoding over the network
    // shell.insertPendingRequestClient(req.getrequestId(), req);
    shell.getClient().send_over_socket(encoding);
    string content = shell.getClient().receive_from_socket();
    reply_list_CR rep = coder::decode_reply_list_CR(content);
    cout << rep << '\n';

    // receive reply
    // To-Add :
    if (rep.getStatus() / 200 == 1)
    {
        // display_chatrooms();
        cout << GREEN_TEXT("[server] : Listing available chatrooms ...\n ");

        cout << "Available chatrooms:\n";
        for (chatroom_t &chatroom : rep.getChatrooms())
            cout << chatroom << '\n';
    }
    else
    {
        cout << RED_TEXT << "[server] request for listing chatrooms failed. Please try again later\n"
             << RESET_COLOR;
    }

    cout << "handle list chatrooms\n";
}
void TaskHandler::handle_create_chatroom(OmegleShell &shell)
{
    if (!shell.getClient().getActivated())
    {
        cout << RED_TEXT << "[server] : Connect to server first before requesting\n"
             << RESET_COLOR;
        return;
    }
    id name = Parser::parse_user_input("Enter name of the chatroom:");

    string capacity_str = Parser::parse_user_input("Enter capacity of chatroom: ");
    int capacity = 0;
    if (!Parser::parse_int(capacity_str, capacity))
    {
        cout << RED_TEXT << "[server] : Error parsing " << '"' << capacity_str << '"' << " ; Expected type integer\n"
             << RESET_COLOR;
        return;
    }
    capacity = min(max(1, capacity), 40);
    string description = Parser::parse_user_input("Enter description of this chatroom: ");
    chatroom_t chatroom(-1, name, capacity, shell.getClient().getName(), time(nullptr), description);

    request_create_CR req(chatroom);
    string encoding = coder::encode_request_create_CR(req);
    shell.getClient().send_over_socket(encoding);
    string content = shell.getClient().receive_from_socket();
    reply_create_CR rep = coder::decode_reply_create_CR(content);
    if (rep.getStatus() / 200 == 1)
    {
        cout << GREEN_TEXT("[server] : Create chatroom " + name + "...\n ");
    }
    else
    {
        cout << RED_TEXT << "[server] : Create chatroom request failed. Please try again later\n"
             << RESET_COLOR;
    }
    cout << "Reply: \n"
         << rep << '\n';

    // send over the socket

    // cout << "handle create chatrooms\n";
}
void TaskHandler::handle_join_chatroom(OmegleShell &shell)
{
    if (!shell.getClient().getActivated())
    {
        cout << RED_TEXT << "[server] : Connect to server first before requesting\n"
             << RESET_COLOR;
        return;
    }
    cout << BLUE_TEXT("[server] : Attempting to join chatroom\n");
    string chatroom_id_str = Parser::parse_user_input("Enter chatroom id:");
    int chatroom_id = 0;
    if (!Parser::parse_int(chatroom_id_str, chatroom_id))
    {
        cout << RED_TEXT << "[server] : Error parsing " << '"' << chatroom_id_str << '"' << " ; Expected type integer\n"
             << RESET_COLOR;
        return;
    }
    cout << BLUE_TEXT("Joining room " + chatroom_id_str + " ...\n");
    request_JLD_CR req(join_CR, chatroom_id);
    string encoding = coder::encode_request_JLD_CR(req);

    shell.getClient().send_over_socket(encoding);
    string content = shell.getClient().receive_from_socket();
    reply_JLD_CR rep = coder::decode_reply_JLD_CR(content);
    if (rep.getStatus() / 200 == 1)
    {
        shell.addchatrooms(chatroom_id);
        cout << GREEN_TEXT("[server] : Joined chatroom " + chatroom_id_str + " successfuly !\n");
    }
    else
    {
        cout << RED_TEXT << "[server] : Joining charoom" + chatroom_id_str + " failed. Please try again later.\n"
             << RESET_COLOR;
    }
    // cout << req << '\n';
    //
    // //
    // // // Send over tcp sockets.
    // //
    //
    // cout << "handle join chatrooms\n";
}
void TaskHandler::handle_leave_chatroom(OmegleShell &shell)
{
    if (!shell.getClient().getActivated())
    {
        cout << RED_TEXT << "[server] : Connect to server first before requesting\n"
             << RESET_COLOR;
        return;
    }
    cout << BLUE_TEXT("[server] : Attempting to leave chatroom\n");
    string chatroom_id_str = Parser::parse_user_input("Enter chatroom id:");
    int chatroom_id = 0;
    if (!Parser::parse_int(chatroom_id_str, chatroom_id))
    {
        cout << RED_TEXT << "[server] : Error parsing " << '"' << chatroom_id_str << '"' << " ; Expected type integer\n"
             << RESET_COLOR;
        return;
    }
    cout << BLUE_TEXT("Leaving room " + chatroom_id_str + " ...\n");
    request_JLD_CR req(leave_CR, chatroom_id);
    string encoding = coder::encode_request_JLD_CR(req);
    shell.getClient().send_over_socket(encoding);
    string content = shell.getClient().receive_from_socket();
    reply_JLD_CR rep = coder::decode_reply_JLD_CR(content);
    if (rep.getStatus() / 200 == 1)
    {
        shell.addchatrooms(chatroom_id);
        cout << GREEN_TEXT("[server] : Left chatroom " + chatroom_id_str + " successfuly !\n");
    }
    else
    {
        cout << RED_TEXT << "[server] : Leaving charoom" + chatroom_id_str + " failed. Please try again later.\n"
             << RESET_COLOR;
    }
    cout << "Rep:\n"
         << rep;
}
void TaskHandler::handle_delete_chatroom(OmegleShell &shell)
{
    cout << RED_TEXT << "[server] : Option is not supported. Try again next semester :)\n"
         << RESET_COLOR;
    return;
    if (!shell.getClient().getActivated())
    {
        cout << RED_TEXT << "[server] : Connect to server first before requesting\n"
             << RESET_COLOR;
        return;
    }
    cout << BLUE_TEXT("[server] : Attempting to delete chatroom\n");
    string chatroom_id_str = Parser::parse_user_input("Enter chatroom id:");
    int chatroom_id = 0;
    if (!Parser::parse_int(chatroom_id_str, chatroom_id))
    {
        cout << RED_TEXT << "[server] : Error parsing " << '"' << chatroom_id_str << '"' << " ; Expected type integer\n"
             << RESET_COLOR;
        return;
    }
    cout << "Leaving room " << chatroom_id << " ...\n";
    request_JLD_CR req(delete_CR, chatroom_id);
    string encoding = coder::encode_request_JLD_CR(req);
    cout << req << '\n';
    cout << "handle delete chatrooms\n";
}
void TaskHandler::handle_broadcast_message(OmegleShell &shell)
{
    if (!shell.getClient().getActivated())
    {
        cout << RED_TEXT << "[server] : Connect to server first before requesting\n"
             << RESET_COLOR;
        return;
    }
    cout << BLUE_TEXT("[server] : Attempting to broadcast message to chatroom\n");
    string chatroom_id_str = Parser::parse_user_input("Enter chatroom id:");
    int chatroom_id = 0;
    if (!Parser::parse_int(chatroom_id_str, chatroom_id))
    {
        cout << RED_TEXT << "[server] : Error parsing " << '"' << chatroom_id_str << '"' << " ; Expected type integer\n"
             << RESET_COLOR;
        return;
    }
    // verify that the user is in a member of this room
    // // // To DO
    string message_str = Parser::parse_user_input("Enter message: ");
    message_t message(shell.getClient().getName(), message_str, time(nullptr));
    request_broadcast_message req(chatroom_id, message);
    string encoding = coder::encode_request_broadcast_message(req);
    shell.getClient().send_over_socket(encoding);
    string content = shell.getClient().receive_from_socket();
    reply_broadcast_message rep = coder::decode_reply_broadcast_message(content);

    if (rep.getStatus() / 200 == 1)
    {
        cout << GREEN_TEXT("[server] : Broadcasting message to " + chatroom_id_str + " was successful !\n");
        cout << rep << '\n';
    }
    else
    {
        cout << RED_TEXT << "[server] : Broadcasting message to " + chatroom_id_str + " failed. Try again later\n"
             << RESET_COLOR;
    }

    //
    // //
    // // // Send them over sockets
    // //
    //
}
void TaskHandler::handle_list_users(OmegleShell &shell)
{
    if (!shell.getClient().getActivated())
    {
        cout << RED_TEXT << "[server] : Connect to server first before requesting\n"
             << RESET_COLOR;
        return;
    }
    cout << "handle list users\n";
}
void TaskHandler::handle_private_message(OmegleShell &shell)
{
    if (!shell.getClient().getActivated())
    {
        cout << RED_TEXT << "[server] : Connect to server first before requesting\n"
             << RESET_COLOR;
        return;
    }
    cout << BLUE_TEXT("[server] : Attempting to private message to user\n");
    string user_id = Parser::parse_user_input("Enter user id:");
    // verify that the user is in a member of this room
    // // // To DO
    string message_str = Parser::parse_user_input("Enter message: ");
    message_t message(shell.getClient().getName(), message_str, time(nullptr));
    request_private_message req(user_id, message);
    string encoding = coder::encode_request_private_message(req);
    shell.getClient().send_over_socket(encoding);
    string content = shell.getClient().receive_from_socket();
    reply_private_message rep = coder::decode_reply_private_message(content);

    if (rep.getStatus() / 200 == 1)
    {
        cout << GREEN_TEXT("[server] : Private message to " + user_id + " was successful !\n");
        cout << rep << '\n';
    }
    else
    {
        cout << RED_TEXT << "[server] : Private message to " + user_id + " failed. Try again later\n"
             << RESET_COLOR;
    }

    //
    // cout << "handle private message\n";
}
void TaskHandler::handle_display_chatroom_info(OmegleShell &shell)
{
    if (!shell.getClient().getActivated())
    {
        cout << RED_TEXT << "[server] : Connect to server first before requesting\n"
             << RESET_COLOR;
        return;
    }
    cout << "handle display chatrooms info\n";
}
void TaskHandler::handle_disconnect(OmegleShell &shell)
{

    if (!shell.getClient().getActivated())
    {
        cout << RED_TEXT << "[server] : Already disconnected\n"
             << RESET_COLOR;
        return;
    }
    cout << BLUE_TEXT("[server] : Attempting to disconnect\n");
    // create request_disconnect.
    request_disconnect req;
    // encoding request_disconnect.
    string encoding = coder::encode_request_disconnect(req);

    shell.getClient().send_over_socket(encoding);
    cout << GREEN_TEXT("[server] : User" + shell.getClient().getName() + " disconnected\n");

    // string decoding = shell.getClient().receive_from_socket();
    // reply_disconnect rep = coder::decode_reply_disconnect(decoding);
    // cout << rep << '\n';
    // send the request_disconnect.

    // wait for reply.
    // if successful, flush all the data structures of the user
    // if (rep.getStatus() / 200 == 1)
    // {
    // shell.setClientName("");
    // shell.setClientActivated(false);
    // }
    // else
    // {
    // }
    cout << "handle disconnect\n";
}
void TaskHandler::handle_display_chatroom_message_history(OmegleShell &shell) { cout << "handle display chatroom message history\n"; }
// // // // // // Task Handler end // // // // // // //