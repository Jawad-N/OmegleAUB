#include "utilities.h"

/**
 * Possible encoding schemes:
 * Message: - Using seperators : Fails if the seperator is part of the message
 *                               We can restrict the messages to certain characters
 *                               No We can check for the last k seperators. Won't fail
 *                               Go in reverse order.
 *          - Message.message|str(from)|str(sendingTime)
 * Request: - Using seperators:
 *          - message$type$id
 * Reply  : - Using seperators:
 *          - message$type$id$status_code
 *
 */

// ########################### Request Start ##############################################

vector<string> request::request_type{
    "BROADCAST_MESS",
    "CREATE_CR"};

int request::counter = 0;

map<string, requestTYPE> request::str_to_request_type{
    {"BROADCAST_MESS", BROADCAST_MESS},
    {"CREATE_CR", CREATE_CR}};

requestTYPE request ::getRequestType(string key)
{
    return str_to_request_type[key];
}
request::request(requestTYPE type, Message message)
{
    counter++;
    this->ID = counter;
    this->type = type;
    this->message = message;
}

request::request(int ID, requestTYPE type, Message message)
{
    this->ID = ID;
    this->type = type;
    this->message = Message(message);
}

int request::getID()
{
    return ID;
}
requestTYPE request::getType()
{
    return type;
}
Message request::getMessage()
{
    return message;
}
string request::getTypeStr()
{
    return request_type[type];
}

std::ostream &operator<<(std::ostream &os, const request &req)
{
    /**
     * @brief
     *
     * ID      :
     * Type    :
     *
     *
     *
     */
    os << "\n////////////////////////////// Request start //////////////////////////////\n "
       << '\n';
    os << "ID      :" << req.ID << "\n";
    os << "Type    :" << request::request_type[req.type] << '\n';
    os << req.message;
    os << "\n////////////////////////////// Request end //////////////////////////////\n";

    return os;
}

// ########################### Request end ##############################################

// ########################### Reply Start ##############################################

vector<string> reply::request_type{
    "BROADCAST_MESS",
    "CREATE_CR"};

reply::reply(int ID, requestTYPE type, int status_code, Message message)
{
    this->ID = ID;
    this->type = type;
    this->status_code = status_code;
    this->message = Message(message);
}

int reply::getID() { return ID; }
int reply::getStatusCode()
{
    return status_code;
}
requestTYPE reply::getType()
{
    return type;
}
string reply::getTypeStr()
{
    return request_type[type];
}
Message reply::getMessage()
{
    return Message(message);
}

std::ostream &operator<<(std::ostream &os, const reply &rep)
{
    os << "\n////////////////////////////// Reply start //////////////////////////////\n "
       << '\n';
    os << "ID          :" << rep.ID << "\n";
    os << "Type        :" << reply::request_type[rep.type] << '\n';
    os << "Status Code :" << rep.status_code << '\n';
    os << rep.message;
    os << "\n////////////////////////////// Reply end //////////////////////////////\n";

    return os;
}
// ########################### Reply end ##############################################

// ########################### Message Start ##############################################

Message::Message(string content, int from, time_t sendingTime)
{
    this->content = content;
    this->from = from;
    this->sendingTime = sendingTime;
}

Message::Message()
{
    content = "";
    from = -1;
    sendingTime = time(nullptr);
}
string Message::getContent() { return content; }
time_t Message::getsendingTime() { return sendingTime; }
int Message::getFrom() { return from; }

std::ostream &operator<<(std::ostream &os, const Message &Mess)
{
    /**
     * @brief
     * From   :
     * Time   :
     * Content:
     *
     */
    os << "\nMessage start\n"
       << '\n';
    os << "From   : " << to_string(Mess.from) << '\n';
    os << "Sent   : " << TimeConverter::timeToString(Mess.sendingTime) << '\n';
    os << "Content: " << Mess.content << '\n';
    os << "\nMessage end\n"
       << '\n';
    return os;
}
// ########################### Message End    ##############################################

// ########################### Coder Start ##############################################

vector<string> Coder::split(string content, char delimeter, int k)
{
    vector<string> results;
    int i = content.size() - 1;
    int j = i;
    int count = 1;
    while (i >= 0)
    {
        j = i;
        while (j >= 0 && content[j] != delimeter)
            j--;
        if (j < 0)
            break;
        string substring = content.substr(j + 1, i - j);
        results.emplace_back(substring);
        if (count == k)
        {
            results.emplace_back(content.substr(0, j));
            break;
        }
        i = j - 1;
        count++;
    }
    reverse(results.begin(), results.end());
    return results;
}

string Coder::encode_message(Message mess)
{

    return mess.getContent() + "|" + to_string(mess.getFrom()) + "|" + TimeConverter::timeToString(mess.getsendingTime());
}
Message Coder::decode_message(string mess_str)
{
    int from = -1;
    string content = "";
    time_t TIME = time(nullptr);
    if (mess_str.size() == 0)
    {
        cout << "ERROR: Empty string\n";
        exit(0);
    }
    vector<string> LIST = Coder::split(mess_str, '|', 2);
    if (LIST.size() != 3)
        cout << "ERROR in decoding message\n";
    else
    {
        content = LIST[0];
        from = std::stoi(LIST[1]);
        TIME = TimeConverter::stringToTime(LIST[2]);
    }
    return Message(content, from, TIME);
}

string Coder::encode_request(request req)
{
    return Coder::encode_message(req.getMessage()) + "$" + req.getTypeStr() + "$" + to_string(req.getID());
}
request Coder::decode_request(string req_str)
{
    if (req_str.size() < 3)
    {
        cout << "ERROR: error in decoding request" << '\n';
        exit(1);
    }
    int ID = -1;
    requestTYPE type = CREATE_CR;
    Message message("", -1, time(nullptr));
    vector<string> LIST = Coder::split(req_str, '$', 2);
    // cout << LIST.size() << '\n';
    if (LIST.size() != 3)
        cout << "ERROR: error in decoding request\n";
    else
    {
        message = Coder::decode_message(LIST[0]);
        type = request::getRequestType(LIST[1]);
        ID = std::stoi(LIST[2]);
    }
    return request(ID, type, message);
}

string Coder::encode_reply(reply rep)
{
    // message$type$ID$status_code
    return Coder::encode_message(rep.getMessage()) + "$" + rep.getTypeStr() + "$" + to_string(rep.getID()) + "$" + to_string(rep.getStatusCode());
}
reply Coder::decode_reply(string rep_str)
{
    // message$type$ID$status_code
    int ID = -1;
    requestTYPE type = CREATE_CR;
    int status_code = -1;
    Message message("", -1, time(nullptr));
    vector<string> LIST = Coder::split(rep_str, '$', 3);
    if (LIST.size() != 4)
        cout << "ERROR: error in decoding reply\n";
    else
    {
        message = Coder::decode_message(LIST[0]);
        type = request::getRequestType(LIST[1]);
        ID = std::stoi(LIST[2]);
        status_code = std::stoi(LIST[3]);
    }

    return reply(ID, type, status_code, message);
}

// ########################### Coder End ##############################################

// ########################### TimeConverter Start ##############################################
string TimeConverter::timeToString(time_t currentTime)
{
    struct tm *timeinfo;
    char buffer[80];

    timeinfo = localtime(&currentTime);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

    return std::string(buffer);
}

time_t TimeConverter::stringToTime(string dateString)
{
    struct tm timeinfo = {};
    if (strptime(dateString.c_str(), "%Y-%m-%d %H:%M:%S", &timeinfo) == nullptr)
    {
        // Invalid string format
        throw std::invalid_argument("Invalid date string format");
    }

    time_t convertedTime = mktime(&timeinfo);
    if (convertedTime == -1)
    {
        // mktime failed (possibly due to out-of-range values)
        throw std::out_of_range("Invalid time value");
    }

    return convertedTime;
}
// ########################### TimeConverter End ##############################################