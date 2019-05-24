#include <iostream>

using namespace std;

int main(){
    unsigned u = 10, u2 = 42;
    cout <<u - u2 << endl;
    cout << u2 - u <<endl;

    int i = 10, i2 = 42;
    cout << i - i2 << endl;
    cout << i2 - i << endl;
    cout << i - u << endl;
    cout << u - i << endl;
    return 0;
}