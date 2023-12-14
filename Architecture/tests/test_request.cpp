#include "../headers/request.h"
#include "../headers/coder.h"
#include "../headers/reply.h"
void test_request_create()
{
     request REQ1(connect_CR);
     request REQ2(BROADCAST_MESSAGE);
     request REQ3;

     cout << "REQUEST1: \n"
          << REQ1;
     cout << "\nREQUEST2:\n"
          << REQ2;
     cout << "\nREQUEST3:\n"
          << REQ3 << '\n';
}

void test_request_encoding()
{
     request REQ1(connect_CR);
     string encoding = coder::encode_request(REQ1);
     request R2 = coder::decode_request(encoding);

     cout << "Encoding: " << encoding << '\n';
     cout << "Decoding : \n"
          << R2 << '\n';
     cout << "OLD Request: \n"
          << REQ1 << '\n';
}

void test_connect_request()
{
     request_connect REQ("Hashem");
     cout << REQ << '\n';
}

void test_connect_request_encoding_decoding()
{
     request_connect REQ("Hashem");
     cout << REQ << '\n';
     cout.flush();
     string encoding = coder::encode_request_connect(REQ);
     cout << "Encoding: " << encoding << '\n';
     cout.flush();
     request_connect decoding = coder::decode_request_connect(encoding);

     cout << "Decoding : \n"
          << decoding << '\n';
}

void test_request_create_CR()
{
     chatroom_t firstRoom(32, "test", 334, "HASHEM", time(nullptr), "Welcome to the final show bro.");
     request_create_CR req(firstRoom);
     cout << req << '\n';
}

void test_request_create_CR_encoding_decoding()
{
     chatroom_t firstRoom(32, "test", 334, "HASHEM", time(nullptr), "Welcome to the final show bro.");
     request_create_CR req(firstRoom);

     string encoding = coder::encode_request_create_CR(req);
     cout << "Encoding: " << encoding << '\n';
     request_create_CR decoding = coder::decode_request_create_CR(encoding);
     cout << "Decoding : \n"
          << decoding << '\n';
}

void test_request_list_encoding_decoding()
{
     request_list req1(list_CR);
     request_list req2(list_users);
     cout << req1 << '\n';
     cout << req2 << '\n';

     string encoding1 = coder::encode_request_list(req1);
     request_list decoding1 = coder::decode_request_list(encoding1);

     string encoding2 = coder::encode_request_list(req2);
     request_list decoding2 = coder::decode_request_list(encoding2);

     cout << "Encoding1 : " << encoding1 << '\n';
     cout << "Decoding1 : \n"
          << decoding1 << '\n';

     cout << "Encoding2 : " << encoding2 << '\n';
     cout << "Decoding2 : \n"
          << decoding2 << '\n';
}
int main()
{
     // test_request_create();
     // test_request_encoding();
     // test_connect_request();
     // test_connect_request_encoding_decoding();
     // test_request_create_CR();
     // test_request_create_CR_encoding_decoding();
     test_request_list_encoding_decoding();

     return 0;
}