#include <iostream>
#include <Member.h>
#include <Librarian.h>
#include <Book.h>

using namespace std;

Librarian l;
Book b;
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

    if(!success)
        return 0;
    cout << endl;
    cout << "1: Add new Books\n"
         << "2: Add new Members\n"
         << "3: Remove a book\n"
         << "4: Remove a member\n"
         << "5: Issue a book\n"
         << "6: Deposit a book\n"
         << "7: View members accounts\n"
         << "8: View Stock\n"
         << "9: List of books issued\n"
         << "10: Search for a book\n"
         << "11: Update a book record\n"
         << "12: Exit"
         << endl;
    cout << "Enter your choice : ";
    cin >> choice;

    switch(choice){
        case 1:
                b.add_book();
        break;

        case 11:
                b.update_book();
        break;


        case 10:
                b.search_book();
        break;


        break;
    }





    return 0;
}
