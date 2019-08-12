#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct PersonInfo
{
    string name;
    vector<string> numbers;
};

int main(int argc, char const *argv[])
{
    ifstream in("info.txt");
    string line;
    vector<PersonInfo> people;

    while (getline(in, line))
    {
        string number;
        istringstream iss(line);
        PersonInfo person;
        iss >> person.name;
        while (iss >> number)
            person.numbers.push_back(number);
        people.push_back(person);
    }
    in.close();
    ostringstream oss;
    for (auto p : people)
    {
        oss << p.name << " ";
        for (auto num : p.numbers)
            oss << num << " ";
    }
    cout << oss.str();
    return 0;
}
