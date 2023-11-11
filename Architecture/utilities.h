
#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Class that represents the message to be broadcasted.
 *
 */
class Message
{
private:
    int from;           // ID of sender of message.Change its type later ?
    string s;           // Actual message sent.
    time_t sendingTime; // Timestamp of sending.
};

/**
 * @brief Enums concerned with the requestsType
 *
 */
enum requestTYPE
{
    BROADCAST_MESS,
    CREATE_CR
};
/**
 * @brief Class that represents the request object to be sent
 * from the client to the server
 *
 */
class request
{

private:
    static int counter; //
    int ID;             // ID of the request
    requestTYPE type;   // type of request
    string message;     // message encoded
};

/**
 * @brief Class represents the reply object to be sent from
 * the server to the client.
 *
 */
class reply
{
private:
    int ID;
    requestTYPE type;
    int status_code;
    string message;
};

/**
 * @brief Class responsible for serialization of the messages.
 *
 */
class Coder
{
public:
    /**
     * @brief Encodes the request in a string
     *
     * @param req
     * @return string
     */
    static string encode_request(request req);
    /**
     * @brief Decodes the message to a request
     *
     * @param req_str
     * @return request
     */
    static request decode_request(string req_str);
    /**
     * @brief Encodes the reply object to string
     *
     * @param rep
     * @return string
     */
    static string encode_reply(reply rep);
    /**
     * @brief Decodes the string to reply object
     *
     * @param rep_str
     * @return string
     */
    static reply decode_reply(string rep_str);
    /**
     * @brief Encodes the Message object to string
     *
     * @param mess
     * @return string
     */
    static string encode_message(Message mess);
    /**
     * @brief Decodes the string to message object
     *
     * @param mess_str
     * @return Message
     */
    static Message decode_message(string mess_str);
};

/**
 * @brief Class that represents the Client object
 *
 */
class Client
{
private:
    int socket;                         // file_descriptor of the socket
    int ID;                             // ID of the client
    map<int, vector<Message>> chat_log; // chat history of each CR
    vector<int> chat_rooms_joined;      //
public:
    /**
     * @brief Construct a new Client object.It must create a socket
     *
     */
    Client();

    /**
     * @brief connects.
     * Requires IP-Port-Protocol
     *
     * @return true
     * @return false
     */
    bool connect();
    bool send_message();
    bool create_chat_room();
};