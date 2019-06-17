#include <iostream>
using namespace std;

int main(){
    double d = 1.123;
    void* dp = &d;
    double* dp2 = static_cast<double *>(dp);
    int* dp3 = static_cast<int *>(dp); //undefined value
    const double *dp4 = &d;
    double *dp5 = const_cast<double *>(dp4);
    cout << *dp2 << endl;
    cout << *dp3 << endl;
    cout << *dp4 << endl;
    *dp5 = 6;
    cout << *dp4 << endl;
    return 0;
}