#include<iterator>
#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
using namespace std;

int main(int argc, const char** argv) {
    vector<int> ivc;
    list<int> ilst = {1, 2, 3, 3, 3, 6, 7};
    replace_copy(ilst.cbegin(), ilst.cend(), back_insert_iterator<vector<int>>(ivc), 3, 45);
    for(auto i : ilst){
        cout << i << " ";
    }
    cout << endl;
    for(auto i : ivc){
        cout << i << " ";
    }
    cout << endl;
    return 0;
}