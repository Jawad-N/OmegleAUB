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
    // seperator for replies and requests
    static char sep_req_repl;
    /**
     * @brief Encodes chatroom_t type according to the following scheme
     * request: capacity sep created sep name sep description
     * reply  : capacity sep  size sep created sep name sep description
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
};