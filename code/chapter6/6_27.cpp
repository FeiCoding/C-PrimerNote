#include <iostream>

using namespace std;

void addAll(const initializer_list<int> &il){
    int total = 0;
    for(auto n : il){
        total += n;
    }
    cout << total << endl;
}

int main(){
    addAll({1, 2, 5, 3, 4});
    addAll({4, 5, 6, 7});
    return 0;
}