#include <iostream>
#include <string>
using namespace std;

auto doubleArray(int (*arr)[5]) -> int (*)[5]
{
    for (auto &i : *arr)
    {
        i *= 2;
    }
    return arr;
}

int main(int argc, char const *argv[])
{
    int arr[5] = {1, 2, 3, 4, 5};
    int(*arr2)[5] = doubleArray(&arr);
    for (auto i : *arr2)
    {
        cout << i << endl;
    }
    return 0;
}
