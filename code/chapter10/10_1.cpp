#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <list>
using namespace std;

int main(int argc, const char** argv) {
    vector<int> vi = {1, 2, 3, 4, 5, 5, 6, 6, 5, 5, 6};
    cout << count(vi.cbegin(), vi.cend(), 5) << endl;
    string str;
    list<string> ls;
    while(cin >> str){
        ls.push_back(str);
    }
    cin.clear();
    string target;
    cin >> target;
    cout << count(ls.cbegin(), ls.cend(), target) << endl;
    return 0;
}