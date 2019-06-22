#include <iostream>
#include<string>
using namespace std;

int main() {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for(int i : a){
        int val = i % 2;
        switch(val){
            case 0:
                int test_int;
                // int test_int2 = 2; //error
                // string test_str; // error 
                cout << i <<  " even number" << endl;
                break;
            case 1:
                test_int = 12;
                cout << i << " odd number" << endl;
                cout << "test int is " << test_int << endl;
                break;
            default:
                cout << "Hello" << endl;
                break;
        }
    }

    int b = 4;
    switch(b){
        case 3:
            cout << "b is 3" << endl;
            break;
        default: ; // default 必须以空语句结尾
    }
    return 0;
}