#include <iostream>
#include <string>
using namespace std;

int main(){
    unsigned long ull = 3, ul2 = 7;
    cout << (ull || ul2) << endl; 
    int value = 10;
    const int *const p3 = &value;
    // int *p1 = p3; 错误，p3含有底层const
    cout << "P3 is " << *p3 << endl;
    return 0;
}