#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    bool a = true;
    cout << -a << endl;
    bool b = -a;
    cout << b << endl;
    int x = 1;
    int y = 2;
    a ? x++, y++ : y--, y++;
    cout << y << endl;
    return 0;
}
