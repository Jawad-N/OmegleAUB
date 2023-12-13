#include "../headers/request.h"
#include "../headers/coder.h"
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
int main()
{
     // test_request_create();
     // test_request_encoding();
     // test_connect_request();
     test_connect_request_encoding_decoding();

     return 0;
}