#include "utilities.h"

void testRequest()
{
    request Jawad(CREATE_CR, Message("hi bro, I'm enjoying the project with you", 1, time(nullptr)));
    request Khaled(CREATE_CR, Message("Why are you always late Ayman", 1, time(nullptr)));
    // cout << Jawad << '\n';
    // cout << Khaled << '\n';
    string ENCODED_MESSAGE = Coder::encode_request(Khaled);
    // cout << ENCODED_MESSAGE << "\n";
    request DECODED = Coder::decode_request(ENCODED_MESSAGE);
    cout << DECODED << '\n';
}

void testReply()
{
    reply Hashem(1, CREATE_CR, 302, Message("hello bro, me too bro. Let's do a starup together then", 1, time(nullptr)));
    reply Ayman(2, CREATE_CR, 302, Message("Late in what exactly?", 1, time(nullptr)));
    // cout << Hashem << '\n';
    // cout << Ayman << '\n';
    string ENCODED_MESSAGE = Coder::encode_reply(Hashem);
    cout << ENCODED_MESSAGE << "\n";
    reply DECODED = Coder::decode_reply(ENCODED_MESSAGE);
    cout << DECODED << '\n';
}

void testSplit()
{
    string L = "Nour;Raffoul;Is;a;CSE;and;ACM;Hater";
    vector<string> T = Coder::split(L, ';', 1);
    for (string &x : T)
        cout << x << " ";
    cout << '\n';
}

int main()
{
    // string MESSAGE = "asdsdafsadssdasf4343432023-1114 16:54:54";
    // Message HASHEM("OKAY HI Bro LOVE YOU", 2321, time(nullptr));
    // cout << Coder::encode_message(HASHEM) << '\n';
    // cout << Coder::decode_message(Coder::encode_message(HASHEM)) << '\n';
    // cout << HASHEM << '\n';
    // testRequest();
    testReply();
    // testSplit();
    // Coder::decode_message(MESSAGE);

    return 0;
}