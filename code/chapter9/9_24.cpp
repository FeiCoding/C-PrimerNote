#include <iostream>
#include <vector>
using namespace std;

void printV(const vector<int> &vi){
    for(auto i : vi)
        cout << i << " ";
    cout << endl;
}

int main(int argc, char const *argv[])
{
    vector<int> vi;
    auto &first = vi.front();
    auto &end = vi.back();
    cout << first << endl;
    cout << end << endl;
    first = 6;
    end = 8;
    printV(vi);
    cout << vi[3] << endl;
    cout << vi.at(3) << endl;
    auto first2 = *vi.begin();
    cout << first2 << endl;
    return 0;
}


