#include <iostream>
#include <deque>
#include <list>
using namespace std;

int main(int argc, char const *argv[])
{
    deque<int> di = {1, 2, 3, 4, 5, 6};
    list<deque<int>> ldi;
    ldi.push_back(di);
    deque<int> di2 = di;
    deque<int> di3(di2);
    ldi.push_back(di2);
    ldi.push_back(di3);
    auto it_b = ldi.cbegin();
    auto it_e = ldi.cend();
    while(it_b != it_e){
        for(auto i : *it_b){
            cout << i << " ";
        }
        cout << endl;
        it_b++;
    }
    return 0;
}
