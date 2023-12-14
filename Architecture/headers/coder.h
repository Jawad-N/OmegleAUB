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
    static request_create_CR decode_request_create_CR(string req_str);

    /**
     * @brief Reply section
     *
     *
     *
     */

    static string encode_request_JLD_CR(request_JLD_CR req);
    static request_JLD_CR decode_request_JLD_CR(string req_str);

    static string encode_request_broadcast_message(request_broadcast_message req);
    static request_broadcast_message decode_request_broadcast_message(string req_str);

    static string encode_request_private_message(request_private_message req);
    static request_private_message decode_request_private_message(string req_str);

    static string encode_reply(reply rep);
    static reply decode_reply(string rep_str);

    static string encode_reply_connect(reply_connect rep);
    static reply_connect decode_reply_connect(string rep_str);

    static string encode_reply_disconnect(reply_disconnect rep);
    static reply_disconnect decode_reply_disconnect(string rep_str);

    static string encode_reply_list_CR(reply_list_CR rep);
    static reply_list_CR decode_reply_list_CR(string rep_str);

    static string encode_reply_create_CR(reply_create_CR rep);
    static reply_create_CR decode_reply_create_CR(string rep_str);

    static string encode_reply_JLD_CR(reply_JLD_CR rep);
    static reply_JLD_CR decode_reply_JLD_CR(string rep_str);

    static string encode_reply_broadcast_message(reply_broadcast_message rep);
    static reply_broadcast_message decode_reply_broadcast_message(string rep_str);

    static string encode_reply_private_message(reply_private_message rep);
    static reply_private_message decode_reply_private_message(string rep_str);

    static string encode_reply_list_users(reply_list_users rep);
    static reply_list_users decode_reply_list_users(string rep_str);

    /**
     * @brief Now for the main encoding and decoding functions
     *
     */

    // Split and check the rep_type attribute.
    static request_t get_encode_request_type(request req);
    static request_t get_encode_reply_type(reply rep);
    // static string main_encode_request(request req);
    // static request main_decode_request(string req_str);

    // static string main_encode_reply(reply rep);
    // static reply main_decode_reply(string rep_str);
};

// request_connect , request_list,request_create_CR,request_JLD_CR,request_broadcast_message,request_private_message,request_disconnect
