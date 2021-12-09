#include "Book.h"
#include <iostream>
#include <fstream>
#include <iomanip>
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
    getline(cin,authors);

    cout << "Enter isbn: ";
    cin >> isbn;

    Book *found= findRec(isbn);
    if( found !=NULL){
        char choice;
        cout << found->quantity << " copies of a book with this ISBN already exist do you want to increase quantity?(y/n): ";
        cin >> choice;
        if(choice=='y' || choice=='Y'){
            int amount;
            cout << "Enter the amount you want to add: ";
            cin >> amount;
            found->quantity= found->quantity+amount;
            update(found->isbn, *found);
            return true;
        }



        return false;
    }

    cout << "Enter quantity of book: ";
    cin >> quantity;


    ofstream o_books("books.txt", ios::app);
    string s_isbn=to_string(isbn);
    s_isbn= s_isbn.substr(0, s_isbn.find('.'));
    o_books << title+"\t"+authors+"\t"+s_isbn+"\t"+to_string(quantity)+"\n";
    o_books.close();

    cout << "Your book has been added successfully." << endl;
    return true;
}


bool Book::update(double isbn, Book d){
    string newContent="";
    ifstream books;
    books.open("books.txt");


    string rec;

    while(getline(books, rec)){
        char delimiter='\t';

        double f_isbn;
        string temp= rec.substr(rec.find(delimiter)+1);
        temp= temp.substr(temp.find(delimiter)+1);

        f_isbn= stod(temp.substr(0,  temp.find(delimiter)));
        rec+="\n";
        if(isbn==f_isbn){
            string s_isbn=to_string(d.isbn);
            s_isbn= s_isbn.substr(0, s_isbn.find('.'));
            rec=d.title+"\t"+d.authors+"\t"+s_isbn+"\t"+to_string(d.quantity)+"\n";
        }


        newContent+=rec;


    }

    ofstream o_books("books.txt");

    o_books << newContent;

}


Book* Book::findRec(double isbn){
    Book* rec= new Book();
    ifstream accounts;
    accounts.open("books.txt");


    string account_info;

    while(getline(accounts, account_info)){
        char delimiter='\t';


        rec->title= account_info.substr(0,  account_info.find(delimiter));
        account_info= account_info.substr(account_info.find(delimiter)+1);
        rec->authors= account_info.substr(0,  account_info.find(delimiter));
        account_info= account_info.substr(account_info.find(delimiter)+1);
        rec->isbn= stod(account_info.substr(0,account_info.find(delimiter)));
        account_info= account_info.substr(account_info.find(delimiter)+1);
        rec->quantity= stoi(account_info.substr(0,account_info.find(delimiter)));

        if(isbn==rec->isbn)
                return rec;
    }
    return NULL;

}

Book::~Book()
{
    //dtor
}
