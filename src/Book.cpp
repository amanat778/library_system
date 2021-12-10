#include "Book.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

string* split_string( string str, char c);

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
            cout << "Record has been updated successfully." << endl;
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

bool Book::update_book(){

    cout << endl;
    cout << "Enter isbn: ";
    cin >> isbn;

    Book *found= findRec(isbn);

    if(found==NULL){
        cout << "No Record with this isbn number. " << endl;
        return false;
    }

    cout << endl;
    cin.ignore();
    cout << "Enter new title("+found->title+"): ";
    getline(cin, title);

    cout << "Enter new authors("+found->authors+"): ";
    getline(cin,authors);
    string s_isbn=to_string(found->isbn);
    s_isbn= s_isbn.substr(0,s_isbn.find('.'));
    cout << "Enter new isbn("+s_isbn+"): ";
    cin >> isbn;


    if(found->isbn!=isbn && findRec(isbn)!=NULL){
        cout << "A book record with this isbn number already exist. " << endl;
        return false;
    }

    cout << "Enter new quantity("+to_string(found->quantity)+"):";
    cin >> quantity;

    update(found->isbn, *this);
    cout << "Record has been updated successfully." << endl;
    return true;



}

bool Book::search_book(){
    string query;
    cout << "Enter your term: ";
    cin.ignore();
    getline(cin, query);
    query+=" ";

    string* words=split_string(query, ' ');
    int i=0;

    while( words[i].find(' ')== string::npos ){
        cout <<  words[i]  << words[i].size()<< endl;
        ++i;
    }

    cout << "Went through that. No errors. " << endl;






}


string* split_string( string str, char c){
    string temp=str;
    int words_count=0;
    while(temp.find(c)!=string::npos){
        words_count++;
        temp= temp.substr(temp.find(c)+1);
    }

    string *words= new string[words_count];
    int i=0;
    while(str.find(c)!=string::npos){
        words[i]= str.substr(0, str.find(c));
        str= str.substr(str.find(c)+1);
        ++i;
    }


    return words;
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
    return true;
}


Book* Book::findRec(double isbn){
    Book* rec= new Book();
    ifstream file;
    file.open("books.txt");


    string line;

    while(getline(file, line)){
        char delimiter='\t';


        rec->title= line.substr(0,  line.find(delimiter));
        line= line.substr(line.find(delimiter)+1);
        rec->authors= line.substr(0,  line.find(delimiter));
        line= line.substr(line.find(delimiter)+1);
        rec->isbn= stod(line.substr(0,line.find(delimiter)));
        line= line.substr(line.find(delimiter)+1);
        rec->quantity= stoi(line.substr(0,line.find(delimiter)));

        if(isbn==rec->isbn)
                return rec;
    }
    return NULL;

}

Book::~Book()
{
    //dtor
}
