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

void readData(istream &in, deque<string>::iterator &iter, deque<string> &ds){
    string str;
    while(cin >> str){
        iter = ds.insert(iter, str);
    }
}

void readData(istream &in, deque<string> &ds){
    string str;
    while(cin >> str){
        ds.push_back(str);
    }
}

int main(int argc, const char** argv) {
    string str;
    deque<string> ds;
    auto iter = ds.begin();
    readData(cin, iter, ds);
    printData(ds);
    ds.clear();
    cin.clear();
    readData(cin, ds);
    printData(ds);
    ds.clear();
    return 0;
}