#include <iostream>
#include <Member.h>
#include <Librarian.h>
using namespace std;

Librarian l;

int main()
{
    int choice;

    cout << "1: Register\n"
         << "2: Login\n"
         << "3: Forgot Password\n"
         << "Enter your choice: ";
    cin >> choice;

    bool success=false;

    switch(choice){
        case 1:
            success=l.register_user();
            break;
        case 2:
            success=l.login();
            break;
        case 3:
            success=l.forgot_pass();
            break;
    }

    if(success)
        cout << "Print other menu" << endl;



    return 0;
}
