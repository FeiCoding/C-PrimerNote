#include <iostream>
using namespace std;

int main(){
    int ar[10];
    int *p = ar;
    cout << sizeof(ar) / sizeof(*ar) << endl;
    cout << sizeof(p) / sizeof(*p) << endl;
    return 0;
}