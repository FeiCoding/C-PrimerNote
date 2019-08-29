#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, const char** argv) {
    vector<int> vi = {1, 2, 3, 4, 5};
    int sum = accumulate(vi.cbegin(), vi.cend(), 0);
    cout << sum << endl;
    vector<double> vd = {1.1, 1.2, 1.3, 1.4, 1.5};
    int sum2 = accumulate(vd.cbegin(), vd.cend(), 0);
    cout << sum2 << endl;
    vector<const char*> vcc = {"hello", "world"};
    vector<const char*> vcc2 = {"hello", "world"};
    cout << equal(vcc.cbegin(), vcc.cend(), vcc2.cbegin()) << endl;
    return 0;
}