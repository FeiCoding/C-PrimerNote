#include <iostream>
using namespace std;

int main(){
    int i = 20;
    const int *p;
    p = &i;
    cout << *p << endl;
    return 0;
}