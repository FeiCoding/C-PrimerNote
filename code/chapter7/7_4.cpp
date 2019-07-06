#include <iostream>
#include<string>
using namespace std;

struct Person
{
    string name;
    string address;
    string getName() const{
        return name;
    }
    string getAddress() const{
        return address;
    }

    istream & read(istream &i, Person &p);
    ostream & print(ostream &o, const Person &p);
};

istream &read(istream &i, Person &p){
    i >> p.name >> p.address;
    return i;
}

ostream &print(ostream &o, const Person &p){
    o << p.getName() << " " << p.getAddress();
    return o;
}

int main(int argc, char const *argv[])
{
    Person p;
    p.name = "Fei Xie";
    p.address = "London, United Kingdom";
    cout << p.getName() << endl;
    cout << p.getAddress() << endl;

    cout << "Please input your name:" << endl;
    read(cin, p);
    print(cout, p);
    cout << endl;
    return 0;
}
