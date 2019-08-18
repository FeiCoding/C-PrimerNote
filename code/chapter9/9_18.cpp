#include <iostream>
#include <deque>
#include <string>

using namespace std;

void printData(const deque<string> &ds){
    for(auto ss:ds){
        cout << ss << " ";
    }
    cout << endl;
}

void clearStream(istream &in){
    in.clear();
}

int main(int argc, const char** argv) {
    string str;
    deque<string> ds;
    auto iter = ds.begin();
    while(cin >> str){
        iter = ds.insert(iter, str);
    }
    printData(ds);
    ds.clear();
    clearStream(cin);
    while(cin >> str){
        ds.push_back(str);
    }
    printData(ds);
    ds.clear();
    return 0;
}