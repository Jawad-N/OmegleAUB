# Architecture

## Backend : 
### Server side : 
We will implement a multithreaded server that handles broadcasting the messages.

#### Structures used: 


### Client side:

The client side takes care of sending requests and receiving replies.
Types of requests to send:
- Creating a chatroom
- Sending  a message to the server.

Types of replies to receive:
- Message received from the chatroom.
- Chatroom created fail/succeeded reply.



#### Structures used (utilities.h):
- request class:
    - int requestID; // id of the request
    - enum requestType;// {BROADCAST_MESS,CREATE_CR}
    - string message ; // Message to be broadcasted. It is ignored whne requestTYPE = CREATE_CR

- reply class :
    - int replyID; // id of the request to reply to
    - enum replyType;// {BROADCAST_MESS,CREATE_CR} same as request type
    - int status_code ; // 0 if successful, -1 otherwise
    - string message; // (reply message.) 



- message class : 
    - int from;           // ID of the sender
    - string s;           // Actual message sent 
    - time_t sendingTime; // Time sent

- encoder class  :
    - static string encode_request(request);  // Used for encoding requests
    - static request decode_request(string); // Used for decoding requests
    - static string encode_reply(request);  // Used for encoding replies
    - static request decode_reply(string); // Used for decoding replies

    - static string encode_message(message); // Used for encoding message
    - static message decode_message(string); // Used for decoding message
- reply_handler class:
    - handle_reply(); // handels the reply message

- client class:
    - socket connection;
    - int ID;
    - vector Message log_history;
    - vector int CR_Joined;
    
    - bool connect();   // For connecting to server.
    - bool send() ;     // For sending message
    - bool create_CR(); // For creating a CR

- chatRoom class:
    - int ID; // ID of the chatRoom class
    - vector int client_IDs;
    - string name;        // name of the chatroom
    - string description; // decription of the chatroom


# TO-DO

## Frontend : 
- TBA 

## Backend  : 
- ServerSide (Jawad)
- ClientSide (Hashem)
