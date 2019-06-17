#include <iostream>
using namespace std;

int main(){
    int i = 10;
    double d = 12.2324;
    i *= static_cast<int>(d);
    cout << i << endl;
    return 0;
}