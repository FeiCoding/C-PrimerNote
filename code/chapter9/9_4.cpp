#include <iostream>
#include <vector>
using namespace std;

bool find(vector<int>::const_iterator begin, vector<int>::const_iterator end, const int &target){
    while(begin != end){
        if(*begin == target){
            return true;
        }
        begin++;
    }
    return false;
}


int main(int argc, char const *argv[])
{
    vector<int> vi = {1, 2, 3, 4, 5, 6};
    bool res = find(vi.cbegin(), vi.cend(), 3);
    if(res)
        cout << "Found!"<< endl;
    else
        cout << "Not Found!" << endl;
    return 0;
}
