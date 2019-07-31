#include <iostream>
#include <string>
using namespace std;

string::size_type count(const string &s, string::size_type &occur, const char &c){
    auto ret = s.size();
    for(decltype(ret) i = 0; i < s.size(); ++i){
        if(s[i] == c){
            if(ret == s.size())
                ret = i;
            ++occur;
        }
    }
    return ret;
}

int main(int argc, char const *argv[])
{
    string ss;
    cin >> ss;
    for(auto c: ss){
        cout << c << " " << endl;
    }
    string::size_type occur = 0;
    int l = count(ss, occur, 'l');
    cout << "The first location is " << l << endl;
    cout << "The number of showing up is " << occur << endl;
    return 0;
}
