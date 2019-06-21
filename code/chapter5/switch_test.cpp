#include <iostream>
using namespace std;

int main() {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for(int i : a){
        int val = i % 2;
        switch(val){
            case 0:
                cout << i <<  " even number" << endl;
                break;
            case 1:
                cout << i << " odd number" << endl;
                break;
            default:
                cout << "Hello" << endl;
                break;
        }
    }
    return 0;
}