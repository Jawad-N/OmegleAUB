#include<iostream>
using namespace std;

void copy_to_pointer( string s, char * output ){

    int n = s.size();
    for ( int i = 0 ; i < n; i++ ) output[i] = s[i];
    
}

int main(){

    string s2 = "2";
    char msg2[ s2.size()+1 ];
    msg2[s2.size()] = '\0';
    copy_to_pointer ( s2, msg2 );

    cout << msg2 << '\n';
    return 0;
}