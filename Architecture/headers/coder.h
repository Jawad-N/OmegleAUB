#pragma once
#pragma once
#include "utilities.h"
#include "structures.h"
#include "request.h"
#include "reply.h"

class coder
{
public:
    // seperator for the structures.h
    static char sep;
    // seperator for subclasses of reply and request
    static char sep_req_repl;
    // seperator for main request and reply classes
    static char sep_req_repl_main;
    /**
     * @brief Encodes chatroom_t type according to the following scheme
     * request: id sep capacity sep created sep name sep description
     * reply  : id sep capacity sep  size sep created sep name sep description
     * @param chatroom
     * @param req_or_repl false for request encoding and true for reply
     * @return string
     */
    static string encode_chatroom_t(chatroom_t chatroom, bool req_or_repl);

    /**
     * @brief Decodes string that represents chatroom_t object
     *
     * @param chatroom_str
     * @param req_or_repl false for request encoding and true for reply
     * @return chatroom_t
     */
    static chatroom_t decode_chatroom_t(string chatroom_str, bool req_or_repl);

    /**
     * @brief Encodes the whole chatroom attributes
     *
     *
     * @param chatroom
     * @return chatroom_t
     */
    static string encode_chatroom_t(chatroom_t chatroom);

    /**
     * @brief Decodes the whole chatroom attributes
     *
     * @param chatroom_str
     * @return chatroom_t
     */
    static chatroom_t decode_chatroom_t(string chatroom_str);

    /**
     * @brief Encodes message_t structure
     * Encoding scheme: sender sep created sep content
     * @param message
     * @return string
     */
    static string encode_message_t(message_t message);

    /**
     * @brief Decodes message_t string to message_t structure
     *
     * @param message_t_str
     * @return message_t
     */
    static message_t decode_message_t(string message_t_str);

    /**
     * @brief Encodes request structure
     * req_type sep_req_repl_main request_id sep_req_repl_main from (encoding scheme)
     * @param req
     * @return string
     */
    static string encode_request(request req);

    /**
     * @brief
     *
     * @param req_str
     * @return request
     */
    static request decode_request(string req_str);

    /**
     * @brief
     * Encoding scheme encode_request(req) sep_req_repl user_name;
     * @param req
     * @return string
     */
    static string encode_request_connect(request_connect req);

    /**
     * @brief
     *
     * @param req_str
     * @return request_connect
     */
    static request_connect decode_request_connect(string req_str);

    /**
     * @brief encodes request_list
     * encoding scheme : encode_request()
     * @param req
     * @return string
     */
    static string encode_request_list(request_list req);

    /**
     * @brief decodes string to request_list
     *
     * @param req_str
     * @return request_list
     */
    static request_list decode_request_list(string req_str);

    /**
     * @brief encodes request_create_CR to string
     *
     * @param req
     * @return string
     */
    static string encode_request_create_CR(request_create_CR req);

    /**
     * @brief decodes string to request_create_CR
     *
     * @param req_str
     * @return request_create_CR
     */
    static request_create_CR decode_request_create_CR(request_create_CR req_str);
};

// request_connect , request_list,request_create_CR,request_JLD_CR,request_broadcast_message,request_private_message,request_disconnect
