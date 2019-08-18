#include <iostream>
#include <list>
#include <string>
using namespace std;



void printData(const list<string> &ls){
    for(auto ss:ls){
        cout << ss << " ";
    }
    cout << endl;
}

void readData(istream &in, list<string>::iterator &iter, list<string> &ls){
    string str;
    while(cin >> str){
        iter = ls.insert(iter, str);
    }
}

void readData(istream &in, list<string> &ls){
    string str;
    while(cin >> str){
        ls.push_back(str);
    }
}


int main(int argc, char const *argv[])
{
    string word;
    list<string> ls;
    auto it = ls.begin();
    readData(cin, it, ls);
    printData(ls);
    cin.clear();
    ls.clear();
    readData(cin, ls);
    printData(ls);
    return 0;
}
