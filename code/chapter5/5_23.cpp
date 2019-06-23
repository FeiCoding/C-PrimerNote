#include <iostream>
#include <stdexcept>
using namespace std;

int main(int argc, const char** argv) {
    cout << "Please input two numbers:" << endl;
    int a, b;
    while(cin >> a >> b){
        try
        {
            if(b == 0) throw runtime_error("dividend cannot be 0");
            cout << "The result of dividing is " << static_cast<double>(a) / b << endl;
        }
        catch(const runtime_error &e)
        {
            cerr << e.what() << '\n';
            cout << "Do you want to continue? \n0: continue \n1: finish" << endl;
            int choice;
            cin >> choice;
            if(choice){
                break;
            }else{
                cout << "Please input two numbers:" << endl;
            }
        }
    }
    
    return 0;
}