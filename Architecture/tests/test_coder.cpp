#include "../headers/structures.h"
#include "../headers/coder.h"
void test_create_chatroom_t()
{
    chatroom_t firstRoom(32, "test", 334, "HASHEM", time(nullptr), "Welcome to the final show bro.");
    cout << firstRoom << '\n';
    cout << "Encoding of request : ";
    string encoding = coder::encode_chatroom_t(firstRoom, false);
    cout << encoding;
    cout.flush();
    chatroom_t decoding = coder::decode_chatroom_t(encoding, false);
    cout << "Decoding of request : \n"
         << decoding;
}

int main()
{
    test_create_chatroom_t();
    return 0;
}