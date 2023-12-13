#include "../headers/structures.h"
#include "../headers/coder.h"
void test_create_chatroom_t()
{
    chatroom_t firstRoom(32, "test", 334, "HASHEM", time(nullptr), "Welcome to the final show bro.");
    cout << firstRoom << '\n';
    cout << "Encoding of request : ";
    string encoding = coder::encode_chatroom_t(firstRoom, false);
    cout << encoding << '\n';
    cout.flush();
    chatroom_t decoding = coder::decode_chatroom_t(encoding, false);
    cout << "Decoding of request : \n"
         << decoding;
}

void test_add_members_chatroom()
{
    chatroom_t firstRoom(31232, "test", 334, "HASHEM", time(nullptr), "Welcome to the final show bro.");
    vector<string> members{"OIP", "asds", "sdasfs", "asdsaf", "asdsafasd", "OIP"};
    for (string member : members)
        firstRoom.add_member(member);
    for (auto x : firstRoom.getMembers())
        cout << x << '\n';

    string encoding = coder::encode_chatroom_t(firstRoom);
    cout << "encoding: " << encoding << '\n';
    chatroom_t decoding = coder::decode_chatroom_t(encoding);
    cout << "before encoding:\n";
    cout << firstRoom << '\n';
    cout << "decoding:\n";
    cout << decoding << '\n';

    encoding = coder::encode_chatroom_t(firstRoom, false);
    decoding = coder::decode_chatroom_t(encoding, false);
    cout << "Request encoding: " << encoding << '\n';
    cout << "Request decoding: " << decoding << '\n';
}

void test_message_t_create()
{
    message_t Message("Hashem", "Where you go I go, what you see I see\n I know that I will never be with without the security", time(nullptr));
    cout << ":::::::::::: Message ::::::::::::\n";
    cout << Message << '\n';
}

void test_message_t_encoding()
{
    message_t Message("Hashem", "Where you go I go, what you see I see\n I know that I will never be with without the security", time(nullptr));
    string encoding = coder::encode_message_t(Message);
    message_t decoding = coder::decode_message_t(encoding);
    cout << "Encoding: " << encoding << '\n';
    cout << "Decoding:\n"
         << decoding << '\n';
    cout << "Actual Message: \n";
    cout << Message << '\n';
}

int main()
{
    // test_create_chatroom_t();
    // test_add_members_chatroom();
    // test_message_t_create();
    test_message_t_encoding();
    return 0;
}