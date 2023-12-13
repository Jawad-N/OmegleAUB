#include<iostream>
using namespace std;


int main(){

    int count = 1;
    string temp = "hi";
    string choices;
    for ( int i = 0; i < 100; i++ ){
        choices += to_string(count);
        choices += temp;
        choices += '\n';
        count ++;
    }
    cout << choices;

}