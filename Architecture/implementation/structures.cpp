#include "../headers/structures.h"

chatroom_t::chatroom_t()
{
    chatroom_ID = -1;
    name = "";
    capacity = 40;
    owner = "";
    chrono::system_clock::time_point currentTimePoint = std::chrono::system_clock::now();
    created = chrono::system_clock::to_time_t(currentTimePoint);
    description = "";
}

chatroom_t::chatroom_t(int chatroom_ID, string name, int capacity, id owner, time_t created, string description)
{
    this->chatroom_ID = chatroom_ID;
    this->name = name;
    this->capacity = capacity;
    this->owner = owner;
    this->created = created;
    this->description = description;
    this->members.insert(owner);
}

chatroom_t::chatroom_t(const chatroom_t &other)
{
    this->chatroom_ID = other.chatroom_ID;
    this->name = other.name;
    this->capacity = other.capacity;
    this->owner = other.owner;
    this->created = other.created;
    this->description = other.description;
    this->members = other.members;
}

bool chatroom_t::add_member(id member)
{
    // should raise two errors. One for full capacity and other for user already found
    // or return status code.
    if ((int)members.size() >= capacity || members.find(member) != members.end())
        return false;
    members.insert(member);
    return true;
}

string chatroom_t::getName() const { return name; }
void chatroom_t::setName(const string &name_) { this->name = name_; }

int chatroom_t::getchatroomID() const { return chatroom_ID; }
void chatroom_t::setChatroomID(int chatroomID) { this->chatroom_ID = chatroomID; }

int chatroom_t::getCapacity() const { return capacity; }
void chatroom_t::setCapacity(int capacity_)
{
    // don't allow for calls when the map size is greater than the new capacity todo
    this->capacity = capacity_;
}

id chatroom_t::getOwner() const { return owner; }
void chatroom_t::setOwner(const id &owner_) { this->owner = owner_; }

time_t chatroom_t::getCreated() const { return created; }
void chatroom_t::setCreated(const time_t &created_) { this->created = created_; }

string chatroom_t::getDescription() const { return description; }
void chatroom_t::setDescription(const string &description_) { this->description = description_; }

set<id> chatroom_t::getMembers() const { return set<id>(members); }
void chatroom_t::setMembers(const set<id> &members_) { this->members = set<id>(members_); }

ostream &operator<<(std::ostream &os, const chatroom_t &chatroom)
{
    os << "Chatroom ID: " << chatroom.getchatroomID() << "\n";
    os << "Name: " << chatroom.getName() << "\n";
    os << "Capacity: " << chatroom.getCapacity() << "\n";
    os << "Owner ID: " << chatroom.getOwner() << "\n";
    os << "Created: " << TimeConverter::timeToString(chatroom.getCreated()) << '\n';
    os << "Description: " << chatroom.getDescription() << "\n";
    os << "Members: ";
    for (const auto &member : chatroom.getMembers())
    {
        os << member << " ";
    }
    os << "\n";

    return os;
}
bool chatroom_t::operator<(const chatroom_t &other) const
{
    // Define your comparison logic here
    // For example, compare based on chatroom ID or other relevant attributes
    return getchatroomID() < other.getchatroomID();
}

message_t::message_t()
{
    this->sender = "";
    this->content = "";
    this->created = time(nullptr);
}
message_t::message_t(id sender, string content, time_t created)
{
    this->sender = sender;
    this->content = content;
    this->created = created;
}
message_t::message_t(const message_t &other)
{
    this->sender = other.sender;
    this->content = other.content;
    this->created = other.created;
}

id message_t::getSender() const { return sender; }
void message_t::setSender(const id &sender_) { sender = sender_; }

string message_t::getContent() const { return content; }
void message_t::setContent(const string &content_) { content = content_; }

time_t message_t::getCreated() const { return created; }
void message_t::setCreated(const time_t &created_) { created = created_; }

ostream &operator<<(ostream &os, const message_t &message)
{
    os << ":::::::::::: Message Begin ::::::::::::\n";
    os << "Sender  : " << message.getSender() << '\n';
    os << "Sent at : " << TimeConverter::timeToString(message.getCreated()) << '\n';
    os << "Content : " << message.getContent() << '\n';
    os << ":::::::::::: Message End   ::::::::::::\n";
    return os;
}