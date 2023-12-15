#pragma once
#include "client.h"
#include "coder.h"
#include <cstdlib>

class OmegleShell;
class Parser
{
public:
    static string trim_spaces(string input);
    static string parse_user_input(string message);
    static bool parse_int(string message, int &result);
};

class TaskHandler
{
public:
    void handle_connect(OmegleShell &shell);
    void handle_list_chatrooms(OmegleShell &shell);
    void handle_create_chatroom(OmegleShell &shell);
    void handle_join_chatroom(OmegleShell &shell);
    void handle_leave_chatroom(OmegleShell &shell);
    void handle_delete_chatroom(OmegleShell &shell);
    void handle_broadcast_message(OmegleShell &shell);
    void handle_list_users(OmegleShell &shell);
    void handle_private_message(OmegleShell &shell);
    void handle_display_chatroom_info(OmegleShell &shell);
    void handle_disconnect(OmegleShell &shell);
    void handle_display_chatroom_message_history(OmegleShell &shell);
};

class OmegleShell
{
private:
    string user_command_history;
    // string user_name;
    TaskHandler task_handler;
    Client client;

public:
    void displayWelcome();
    void displayHelp();
    void displayPrompt();
    void displayHistory();
    void run();
    bool execute_command(string command);

    Client getClient() const;

    void setClient(const Client &client_);
    void setClientName(string client_);
    void setClientActivated(bool activate);
    void insertPendingRequestClient(int request_id, request req);

    // string getuserName() const;
    // void setUserName(const string &userName);
};