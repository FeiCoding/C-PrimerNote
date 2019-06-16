#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<int> vc = {1, 2, 3, 4, 5};
    for(auto a : vc){
        cout << a << " ";
    }
    cout << endl;
    auto sz = vc.size();
    for(vector<int>::size_type ss = 0; ss != vc.size(); ++ss, --sz){
        vc[ss] = sz;
    }
    for(auto a : vc){
        cout << a << " ";
    }
    cout << endl;
    return 0;
}