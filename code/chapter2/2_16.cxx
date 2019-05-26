#include <iostream>
using namespace std;

int main(){
    int i = 0, &r1 = i;
    double d = 0, &r2 = d;
    cout << r1 << " " << r2 <<endl;
    r2 = 3.145;
    cout << r1 << " " << r2 <<endl;
    r2 = r1;
    cout << r1 << " " << r2 <<endl;
    i = r2;
    r1 = d;
    cout << r1 << " " << r2 <<endl;
    return 0;
}