#include <iostream>
#include <list>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
    string word;
    list<string> ls;
    auto it = ls.begin();
    while(cin >> word){
        it = ls.insert(it, word);
    }
    for(auto s: ls){
        cout << s << " ";
    }
    cout << endl;
    return 0;
}
