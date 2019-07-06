#include <iostream>
#include<string>
using namespace std;

struct Person
{
    friend istream & read(istream &i, Person &p);
    friend ostream & print(ostream &o, const Person &p);
    
    private: 
        string name;
        string address = "China";
        
    public:
        string getName() const{
            return name;
        }
        string getAddress() const{
            return address;
        }
        Person() = default;
        Person(string n, string ad):name(n),address(ad){ }    
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
    p.name = "Fei Xie1";
    p.address = "London, United Kingdom";
    cout << p.getName() << endl;
    cout << p.getAddress() << endl;

    cout << "Please input your name:" << endl;
    read(cin, p);
    print(cout, p);
    cout << endl;

    Person p2("Fei Xie3", "London");
    print(cout, p2);
    cout << endl;
    return 0;
}
