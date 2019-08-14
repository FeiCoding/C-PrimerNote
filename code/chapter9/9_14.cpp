#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
    list<const char *> lc = {"Hello", "World"};
    vector<string> vs;
    vs.assign(lc.cbegin(), lc.cend());
    for(auto ss:vs){
        cout << ss << endl;
    }
    return 0;
}
