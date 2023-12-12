
#include <bits/stdc++.h>
#include <ctime>
using namespace std;

/**
 * @brief Class that represents the message to be broadcasted.
 *        Messages content for the following types
 *        BROADCAST_MESS : text_message | CR_ID
 *        CREATE_CR      : CR_ID : ChatRoom ID
 *        JOIN_CR        : CR_ID
 *        REQUEST_CR     : Empty
 *        LEAVE_CR       : CR_ID
 */
class Message
{
private:
    int from;           // ID of sender of message.Change its type later ?
    string content;     // Actual message sent.
    time_t sendingTime; // Timestamp of sending.

public:
    int getFrom();
    string getContent();
    time_t getsendingTime();
    Message(string content, int from, time_t sendingTime);
    Message();
    friend std::ostream &operator<<(std::ostream &os, const Message &Mess);
};

/**
 * @brief Enums concerned with the requestsType
 *
 */
enum requestTYPE
{
    BROADCAST_MESS,
    CREATE_CR,
    JOIN_CR,
    REQUEST_CR,
    LEAVE_CR
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
    static vector<string> request_type;
    static map<string, requestTYPE> str_to_request_type;
    int ID;           // ID of the request
    requestTYPE type; // type of request
    Message message;  // message encoded
public:
    request(requestTYPE type, Message message);
    request(int ID, requestTYPE type, Message message);
    request()
    {
    }
    /**
     * @brief Returns ID
     *
     * @return int
     */
    int getID();
    /**
     * @brief Get the Type object
     *
     * @return requestTYPE
     */
    requestTYPE getType();
    /**
     * @brief Returns the type in string representation
     *
     * @return string
     */
    string getTypeStr();
    /**
     * @brief Returns a copy of the message
     *
     * @return Message
     */
    Message getMessage();
    /**
     * @brief Returns the request type of key. string -> requestType
     *
     * @param key
     * @return requestTYPE
     */
    static requestTYPE getRequestType(string key);
    friend std::ostream &operator<<(std::ostream &os, const request &req);
};

/**
 * @brief Class represents the reply object to be sent from
 * the server to the client.
 *
 */
class reply
{
private:
    static vector<string> request_type;
    int ID;
    requestTYPE type;
    int status_code;
    Message message;

public:
    reply(int ID, requestTYPE type, int status_code, Message message);
    reply() {}

    int getID();
    int getStatusCode();
    requestTYPE getType();
    string getTypeStr();
    Message getMessage();

    friend std::ostream &operator<<(std::ostream &os, const reply &rep);
};

/**
 * @brief Class responsible for serialization of the messages.
 *
 */
class Coder
{
private:
public:
    /**
     * @brief Splits content string into vector<string> according to the last k delimeters
     *
     * @param content
     * @param delimeter
     * @param _size_
     * @return vector<string>
     */
    static vector<string> split(string content, char delimeter, int k);
    /**
     * @brief Encodes the request in a string
     * Encoding Scheme: message$type$id
     * @param req
     * @return string
     */
    static string encode_request(request req);
    /**
     * @brief Decodes the message to a request
     * Encoding Scheme: message$type$id
     * @param req_str
     * @return request
     */
    static request decode_request(string req_str);
    /**
     * @brief Encodes the reply object to string
     * Encoding Scheme: message$type$id$status_code
     * @param rep
     * @return string
     */
    static string encode_reply(reply rep);
    /**
     * @brief Decodes the string to reply object
     * Encoding Scheme: message$type$id$status_code
     * @param rep_str
     * @return string
     */
    static reply decode_reply(string rep_str);
    /**
     * @brief Encodes the Message object to string
     * Encoding scheme: Message.message|str(from)|str(sendingTime)\0
     * @param mess
     * @return string
     */
    static string encode_message(Message mess);
    /**
     * @brief Decodes the string to message object;
     * Encoding scheme: Message.message|str(from)|str(sendingTime)\0
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
     * @brief Intializes a connection between the client and the specific server.
     * Requires IP-Port-Protocol
     *
     * @return true if connection is established
     * @return false else
     */
    bool connect();
    /**
     * @brief Sends message encapsulated in a request object to the server.
     *
     * @return true if message is sent & received
     * @return false else
     */
    bool send_message(string message);

    bool create_chat_room();
};

/**
 * @brief Class that converts time_t to string and vice versa
 *
 */
class TimeConverter
{
public:
    // Convert time_t to string
    static std::string timeToString(time_t currentTime);

    // Convert string to time_t
    static time_t stringToTime(string dateString);
};
