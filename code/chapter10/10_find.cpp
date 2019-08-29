#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

using VI = vector<int>;

int main(int argc, const char** argv) {
    VI vi = {1, 2, 3, 4, 5};
    auto res = find(vi.cbegin(), vi.cend(), 2);
    cout << "The value is " << (res == vi.cend() ? "not found." : "found") << endl; 
    return 0;
}