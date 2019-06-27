#include <iostream>
#include <string>
using namespace std;

void FindUpper(const string str){
    for(auto s: str){
        if(isupper(s)){
            cout << "Find upper letter" << endl;
            break;
        }
    }
}

void LowerStr(string &str){
    for(auto &s: str){
        s = tolower(s);
    }
    cout << str << endl;
}

int main(int argc, const char** argv) {
    cout << argc << endl;
    for(int i = 1; i <= argc; ++i){
        cout << argv[i] << endl;
    }
    string str;
    cin >> str;
    FindUpper(str);
    LowerStr(str);
    return 0;
}