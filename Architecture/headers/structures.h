#pragma once
#include "includes.h"
#include "utilities.h"
typedef string id;
/**
 * @brief class that represent the chatroom instance
 *
 */
class chatroom_t
{
private:
    //
    int chatroom_ID;
    string name;
    int capacity;
    id owner;
    time_t created;
    string description;
    set<id> members;

public:
    chatroom_t();
    chatroom_t(int chatroom_ID, string name, int capacity, id owner, time_t created, string description);
    chatroom_t(const chatroom_t &other);
    /**
     * @brief Attempts to add member to this chatroom
     *
     * @param member
     * @return True
     * @return False
     */
    bool add_member(id member);

    /**
     * @brief Getters and setters for all the attributes
     *
     */

    string getName() const;
    void setName(const string &name_);

    int getchatroomID() const;
    void setChatroomID(int chatroomID);

    int getCapacity() const;
    void setCapacity(int capacity_);

    id getOwner() const;
    void setOwner(const id &owner_);

    time_t getCreated() const;
    void setCreated(const time_t &created_);

    string getDescription() const;
    void setDescription(const string &description_);

    set<id> getMembers() const;
    void setMembers(const set<id> &members_);
    friend ostream &operator<<(ostream &os, const chatroom_t &chatroom);
};

class message_t
{
private:
    id sender;
    string content;
    time_t created;

public:
    message_t();
    message_t(id sender, string content, time_t created);
    message_t(const message_t &other);
    

    friend ostream &operator<<(ostream &os, const message_t &message);
    /**
     * @brief Getters and setters of objects
     *
     *
     */

    id getSender() const;
    void setSender(const id &sender_);

    string getContent() const;
    void setContent(const string &content_);

    time_t getCreated() const;
    void setCreated(const time_t &created_);
};
