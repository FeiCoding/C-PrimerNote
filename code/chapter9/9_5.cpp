#include <vector>
#include <iostream>

using namespace std;

using VII = vector<int>::const_iterator;

VII find(VII begin, VII end, const int &target){
    while(begin != end){
        if(*begin == target)
            return begin;
        begin++;
    }
    return end;
}

int main(int argc, char const *argv[])
{
    vector<int> vi = {1, 2, 3, 4, 5};
    auto pi = find(vi.cbegin(), vi.cend(), 3);
    if(pi != vi.cend()){
        cout << "Found " << *pi << endl;
    }
    else{
        cout << "Not found" << endl;
    }
    return 0;
}
