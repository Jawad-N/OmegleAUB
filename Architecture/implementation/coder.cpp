#include "../headers/coder.h"

char coder::sep = '`';
char coder::sep_req_repl = 'x';

string coder::encode_chatroom_t(chatroom_t chatroom, bool req_or_repl)
{
    // to_add from time_t to time
    // request encoding : capacity sep created sep name sep description
    // reply encoding   : capacity sep  size sep created sep name sep description
    string extra = "";
    if (req_or_repl)
        extra = coder::sep + to_string((int)chatroom.getMembers().size());

    return to_string(chatroom.getCapacity()) + extra + coder::sep + to_string(chatroom.getCreated()) + coder::sep + chatroom.getName() + coder::sep + chatroom.getDescription();
}

chatroom_t coder::decode_chatroom_t(string chatroom_str, bool req_or_repl)
{

    // request encoding : capacity sep created sep name sep description
    // reply encoding   : capacity sep  size sep created sep name sep description
    // stoi(string) -> integer try accept
    vector<string> content = split(chatroom_str, coder::sep);
    if (content.size() > 5 || content.size() < 4)
        throw runtime_error("[server] : invalid encoding for chatroom_t");
    if (content.size() == 5 && !req_or_repl)
        throw runtime_error("[server] : invalid encoding for chatroom_t. Expected reply decoding instead of request ");
    if (content.size() == 4 && req_or_repl)
        throw runtime_error("[server] : invalid encoding for chatroom_t. Expected request decoding instead of reply ");
    chatroom_t chatroom;

    int offset = 0;
    chatroom.setCapacity(stoi(content[0]));

    if (req_or_repl)
    {
        offset = 1;
    }
    chatroom.setCreated((time_t)stoi(content[1 + offset]));
    chatroom.setName(content[2 + offset]);
    chatroom.setDescription(content[3 + offset]);

    return chatroom;
}

string coder::encode_chatroom_t(chatroom_t chatroom)
{
    // encoding :  capacity sep size sep owner sep created sep [ member_1,member_2,…, member_n ] sep name sep description
    // forbidden , in naming
    string members_encoding = "[";
    set<id> members = chatroom.getMembers();
    set<id>::iterator itr = members.begin();
    for (; itr != members.end(); itr++)
    {
        members_encoding += (*itr);
        if (itr + 1 != members.end())
            members += ',';
    }
    members_encoding += "]";
    return to_string(chatroom.getCapacity()) + coder::sep + to_string((int)chatroom.getMembers().size()) + coder::sep +
           chatroom.getOwner() + coder::sep + to_string(chatroom.getCreated()) + coder::sep + members_encoding + coder::sep +
           chatroom.getName() + coder::sep + chatroom.getDescription();
}

chatroom_t coder::decode_chatroom_t(string chatroom_str)
{
    // encoding :  capacity sep size sep owner sep created sep [ member_1,member_2,…, member_n ] sep name sep description
    // forbidden , in naming
    vector<string> content = split(chatroom_str, coder::sep);
    if (content.size() != 7)
        throw runtime_error("[server] :  invalid encoding for main chatroom_t.");
    // Continue from here.
}