#include <iostream>
using namespace std;

int main(){
    double d = 1.123;
    void* dp = &d;
    double* dp2 = static_cast<double *>(dp);
    int* dp3 = static_cast<int *>(dp); // undefined value
    cout << *dp2 << endl;
    cout << *dp3 << endl;
    return 0;
}