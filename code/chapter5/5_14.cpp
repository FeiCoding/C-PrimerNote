#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    cout << "Input words you want to compare: " << endl;
    string old_str;
    string new_str ;
    vector<string> vs;
    vector<int> vi;
    while(cin >> new_str){
        if(new_str == old_str){
            ++vi[vi.size() - 1];
        }
        else{
            vi.push_back(1);
            vs.push_back(new_str);
            old_str = new_str;
        }
    }
    int max = 0;
    for(auto i : vi){
        if(max < i){
            max = i;
        }
    }
    for(decltype(vi.size()) i = 0; i != vi.size(); ++i){
        if(vi[i] == max){
            cout << "string is " << vs[i] << endl;
            cout <<  "count number is " << max << endl;
        }
    }
    
    return 0;
}