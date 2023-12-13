#include <iostream>
using namespace std;

int main() {

    double a,b;
    char op = {};
    char use = {};

    cout << "Hello! I'm Calculator!\n" << '\n';
    
    while(1) {
        cout << "Please choose Y or N (Y/N) : ";
        cin >> use;
        cout << '\n';

        if (use == 'Y' || use == 'y') {

            cout << "Input X : ";
            cin >> a;

            cout << "Input Operator (+,-,*,/) : ";
            cin >> op;

            cout << "Input Y : ";
            cin >> b;

            if (op == '+') {
                cout << "X + Y is : " << a+b << '\n';
            }
            else if (op == '-') {
                cout << "X - Y is : " << a-b << '\n';
            }
            else if (op == '*') {
                cout << "X * Y is : " << a*b << '\n';
            }
            else if (op == '/') {
                cout << "X / Y is : " << a/b << '\n';
            }
            cout << '\n';
        }
        else break;
    }
    cout << "Good Bye!\n" << '\n';

    return 0;
}