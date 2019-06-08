#include <vector>
#include <iostream>
using namespace std;

int main()
{
    vector<int> ve{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto vi = ve.begin();
    for (; vi != ve.end(); vi++)
    {
        *vi = *vi * 2;
    }
    for (auto i : ve)
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}