#include <iostream>
#include <string>
#include <vector>
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

string testReturn(){
    string ss;
    if(!ss.empty())
        return ss;
    else
    {
        return "Hello World";
    }
    
    return ss;
}

vector<int> testReturn2(){
    return {1, 2, 3, 4, 5};
}


const string &shorterString(const string &s1, const string &s2){
    return s1.size() < s2.size() ? s1 : s2;
}

string &shorterString(string &s1, string &s2){
    auto &r = shorterString(const_cast<const string &>(s1), const_cast<const string &>(s2));
    return const_cast<string &>(r);
}

int main(int argc, char const *argv[])
{
    // string ss;
    // cin >> ss;
    // for(auto c: ss){
    //     cout << c << " " << endl;
    // }
    // string::size_type occur = 0;
    // int l = count(ss, occur, 'l');
    // cout << "The first location is " << l << endl;
    // cout << "The number of showing up is " << occur << endl;
    cout << testReturn() << endl;
    vector<int> vi = testReturn2();
    for(auto i: vi)
        cout << i << endl;
    
    string s1 = "Hello World";
    string s2 = "Fei Xie";
    const string res = shorterString(s1, s2);
    cout << res << endl;
    
    return 0;
}
