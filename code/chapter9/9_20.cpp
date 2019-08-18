#include <iostream>
#include <list>
#include <deque>
using namespace std;

int main(int argc, char const *argv[])
{
    list<int> li = {1, 2, 3, 4, 5, 6};
    deque<int> die;
    deque<int> dio;
    for(auto i : li){
        if(i % 2 == 0)
            die.push_back(i);
        else
            dio.push_back(i);        
    }
    for(auto i : die)
        cout << i << " ";
    cout << endl;
    for(auto i : dio)
        cout << i << " ";
    cout << endl;
    
    return 0;
}
