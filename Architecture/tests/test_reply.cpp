#include "../headers/reply.h"
#include "../headers/coder.h"

void test_reply()
{
    // creating replies from all constructors
    reply main_reply_empty;
    reply main_reply_default(list_CR);
    reply main_reply_args(23, BROADCAST_MESSAGE, 200, "");
    reply main_reply_copy(main_reply_args);

    cout << main_reply_empty << '\n';
    cout << main_reply_default << '\n';
    cout << main_reply_args << '\n';
    cout << main_reply_copy << '\n';
    string encoding = coder::encode_reply(main_reply_args);

    cout << "Encoding: " << encoding << '\n';
    reply decoding = coder::decode_reply(encoding);
    cout << "Decoding: " << decoding << '\n';

    // Encoding section
}

void test_reply_connect()
{
    reply_connect main_reply_empty;
    reply_connect main_reply_args(23, 200, "Hello. Here's the ssadsdsadsaerver");
    reply_connect main_reply_copy(main_reply_args);
    reply_connect main_reply_copy_shit(main_reply_copy);
    // reply_list_CR jawad(423, 2342, "asedasd", vector<chatroom_t>(2, chatroom_t(23, "TEsting", 232, "hashem", time(nullptr), "Welcome")));

    // Testing constructors
    cout << main_reply_empty << '\n';
    cout << main_reply_args << '\n';
    cout << main_reply_copy << '\n';
    cout << main_reply_copy_shit << '\n';
    //
    // cout << jawad << '\n';
    // reply_connect main_reply_copy_shit_fail(jawad);
    string encoding = coder::encode_reply_connect(main_reply_args);
    cout << "Encoding : " << encoding << '\n';
    reply_connect decoding = coder::decode_reply_connect(encoding);
    cout << "Decoding : \n";
    cout << decoding << '\n';
}

void test_reply_list_CR()
{
    reply_connect rep(123, 604, "MESSAFE");
}

void test_reply_JLD_CR();

void test_reply_broadcast_message();

void test_reply_private_message();

void test_reply_list_users();

int main()
{
    // test_reply();
    test_reply_connect();
    return 0;
}