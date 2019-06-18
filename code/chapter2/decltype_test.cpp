#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;
int main()
{
    int i = 10;
    int *p = &i;
    decltype(i = 20) y = i; // y is reference type
    y = 15;
    decltype(10) z = 20; // z is int type
    decltype(*p) s = z;  // p is reference type

    cout << typeid(z).name() << endl;
    cout << typeid(y).name() << endl;
    cout << typeid(s).name() << endl;
    return 0;
}