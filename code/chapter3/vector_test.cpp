#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    vector<string> v1(3, "AA");
    vector<string> v2{3, "BB"};
    cout << "First ouput way with for-range: " << endl;
    for (auto str : v1)
    {
        cout << str << " ";
    }
    cout << endl;
    for (auto str : v2)
    {
        cout << str << " ";
    }
    cout << endl;
    cout << "Second ouput way with iterator: " << endl;
    for (auto vi = v1.begin(); vi != v1.end();)
    {
        cout << *vi++ << " ";
    }
    cout << endl;
    return 0;
}