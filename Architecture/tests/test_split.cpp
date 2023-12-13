#include "../headers/utilities.h"

void test_split()
{
    string text = "I cant't j, hear sdsa, fa,sadf,asdsdda,,,,,,";
    char deli = ',';
    vector<string> results = split(text, deli);
    for (string &x : results)
        cout << x << "\n";
}

int main()
{
    test_split();
    return 0;
}