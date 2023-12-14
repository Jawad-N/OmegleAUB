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

    vector<chatroom_t> chatrooms{
        chatroom_t(4432, "Hahem", 232, "Hashem", time(nullptr), "YES MINI RONALD"), chatroom_t(44213, "Hahem", 232, "Haashem", time(nullptr), "YES MINI Jawad"), chatroom_t(44322312, "Khalil", 232, "Ahmad", time(nullptr), "YES MINI Hashem")};
    reply_list_CR rep(1919, 322, "MESSAGE", chatrooms);
    // reply_list_CR;
    cout << rep << '\n';
    string encoding1 = coder::encode_reply_list_CR(rep);
    cout << "Encoding: " << encoding1 << '\n';
    reply_list_CR decoding = coder::decode_reply_list_CR(encoding1);

    cout << "Decoding: \n"
         << decoding << '\n';
    cout << request::request_mapper[coder::get_encode_reply_type(encoding1)] << '\n';
}

void test_reply_JLD_CR()
{
    reply_JLD_CR rep1, rep2, rep3, decoding1, decoding2, decoding3;
    string encoding1, encoding2, encoding3;

    // join
    rep1 = reply_JLD_CR(23, join_CR, 342, "Message", 223);
    encoding1 = coder::encode_reply_JLD_CR(rep1);
    decoding1 = coder::decode_reply_JLD_CR(encoding1);

    cout << "Encoding1 : " << encoding1 << '\n';
    cout << "Decoding1 : \n"
         << decoding1 << '\n';

    // leave
    rep2 = reply_JLD_CR(23, leave_CR, 342, "Message", 223);
    encoding2 = coder::encode_reply_JLD_CR(rep2);
    decoding2 = coder::decode_reply_JLD_CR(encoding2);
    cout << "Encoding2 : " << encoding2 << '\n';
    cout << "Decoding2 : \n"
         << decoding2 << '\n';
    // delete
    rep3 = reply_JLD_CR(23, delete_CR, 342, "Message", 223);
    encoding3 = coder::encode_reply_JLD_CR(rep3);
    decoding3 = coder::decode_reply_JLD_CR(encoding3);

    cout << "Encoding3 : " << encoding3 << '\n';
    cout << "Decoding3 : \n"
         << decoding3 << '\n';

    cout << request::request_mapper[coder::get_encode_reply_type(encoding3)] << '\n';
}

void test_reply_broadcast_message()
{
    reply_broadcast_message rep, decoding;
    string encoding;
    //
    rep = reply_broadcast_message(2023, 203, "Server message", 2332, message_t("Hashem", "Hi Jawad", time(nullptr)));
    cout << rep << '\n';
    encoding = coder::encode_reply_broadcast_message(rep);
    decoding = coder::decode_reply_broadcast_message(encoding);
    cout << "Encoding: " << encoding << '\n';
    cout << "Decoding: \n"
         << decoding << '\n';
}

void test_reply_private_message();

void test_reply_list_users();

int main()
{
    // test_reply();
    // test_reply_connect();
    // test_reply_list_CR();
    // test_reply_JLD_CR();
    test_reply_broadcast_message();
    return 0;
}