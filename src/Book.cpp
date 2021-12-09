#include "Book.h"
#include <iostream>
#include <fstream>
using namespace std;

Book::Book()
{
    //ctor
}

bool Book::add_book(){
    cout << endl;
    cin.ignore();
    cout << "Enter title: ";
    getline(cin, title);

    cout << "Enter authors: ";
    cin >> authors;

    cout << "Enter isbn: ";
    cin >> isbn;

    /*Book *found= findRec(isbn)
    if( found !=NULL){
        char choice;
        cout << found->quantity << " copies of a book with this ISBN already exist do you want to increase quantity?(y/n): . \n";
        cin >> choice;
        if(choice=='y' || choice=='Y'){
            int amount;
            cout << "Enter the amount you want to add: ";
            cin >> amount;
            found->quantity= found->quantity+amount;
            return true;
        }



        return false;
    }
    */
    cout << "Enter quantity of book: ";
    cin >> quantity;


    ofstream o_accounts("books.txt", ios::app);
    o_accounts << title+"\t"+authors+"\t"+to_string(isbn)+"\t"+to_string(quantity)+"\n";
    o_accounts.close();

    cout << "Your book has been added successfully." << endl;
    return true;
}

Book::~Book()
{
    //dtor
}
