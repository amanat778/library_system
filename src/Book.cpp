#include "Book.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

string* split_string( string str, char c, int& length);
string to_lower(string str);
void sort_by_relevancy(Book* arr, int* relevancy, int len);


Book::Book()
{

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
    char choice;
    cout << "Do you want to add another record(y/n): ";
    cin >> choice;

    if( choice == 'y' or choice == 'Y')
        return add_book();
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

    // converting ISBN from 1234567890.0000 to 1234567890
    string s_isbn=to_string(found->isbn);
    s_isbn= s_isbn.substr(0,s_isbn.find('.'));
    cout << "Enter new isbn("+s_isbn+"): ";
    cin >> isbn;

    // changed the ISBN and its already exist
    if(found->isbn!=isbn && findRec(isbn)!=NULL){
        cout << "A book record with this isbn number already exist. " << endl;
        return false;
    }

    cout << "Enter new quantity("+to_string(found->quantity)+"):";
    cin >> quantity;

    if(title=="")
        title= found->isbn;

    if(authors=="")
        authors= found->authors;




    update(found->isbn, *this);
    cout << "Record has been updated successfully." << endl;



    return true;
}

bool Book::search_book(){
    string query;
    cout << "Enter your term: ";
    cin.ignore();
    getline(cin, query);
    query= to_lower(query);

    int query_len=0;
    string* words=split_string(query, ' ', query_len);

    ifstream books;
    books.open("books.txt");

    string rec;
    int arr_length=0;

    while(getline(books, rec)){
        bool first=true;
        rec= to_lower(rec);
        for(int i=0; i< query_len; i++)

            if(rec.find(words[i])!=string::npos && first){
                arr_length++;
                first=false;
            }

    }



    Book *records= new Book[arr_length];
    int *relevancy= new int[arr_length];
    int index=0;

    books.clear();
    books.seekg(0);
    while(getline(books, rec)){
        bool found=false;
        relevancy[index]=0;
        rec=to_lower(rec);

        //iterating over all the key words and calculating relevancy for each record
        for(int i=0; i< query_len; i++){


            if(rec.find(words[i])!=string::npos)
                relevancy[index]++;
            if(rec.find(words[i])!=string::npos && !found){
                int l=0;
                found=true;
                string *fields=split_string(rec, '\t',l );
                double isbn= stod(fields[2]);
                records[index]= *findRec(isbn);
                delete [] fields;
            }
        }

        if(found)
            index++;


    }
    sort_by_relevancy(records, relevancy, arr_length);
    cout << endl;

    if(arr_length!=0)
        cout << setw(35) << left << "Title"
             << setw(45) << left << "Authors"
             << setw(20) << left << "ISBN"
             << setw(8)  << left << "Quantity" << endl;

    cout << string(110,'-') << endl;
    for(int i=0; i<arr_length; ++i){
        int limit=33;
        if(records[i].title.size()>limit){
            records[i].title= records[i].title.substr(0,limit);
            records[i].title[limit-1]='.';
            records[i].title[limit-2]='.';
            records[i].title[limit-3]='.';
        }
        limit=43;

        if(records[i].authors.size()>43){
            records[i].authors= records[i].authors.substr(0,43);
            records[i].authors[limit-1]='.';
            records[i].authors[limit-2]='.';
            records[i].authors[limit-3]='.';
        }
        cout << setw(35)<< left << records[i].title
             << setw(45)<< left << records[i].authors
             << setw(20)<< left << fixed << setprecision(0)<< records[i].isbn
             << setw(8) << left << records[i].quantity << endl;
    }

    if(arr_length==0)
        cout << "Sorry no records found with this keyword. "<< endl;

    return arr_length;

}


void sort_by_relevancy(Book* arr, int* relevancy, int len){
    for( int i=0; i< len; ++i )
        for(int j=i; j< len; ++j)
                if(relevancy[j]>relevancy[i]){
                    int temp=relevancy[j];
                    relevancy[j]= relevancy[i];
                    relevancy[i]= temp;

                    Book tmp_book= arr[j];
                    arr[j]=arr[i];
                    arr[i]= tmp_book;
                }


}

string to_lower(string str){
    for(unsigned int i=0; i< str.size(); ++i)
        str[i]= tolower(str[i]);
    return str;
}

string* split_string( string str, char c, int& length){
    string temp=str;
    temp+=c;

    while(temp.find(c)!=string::npos){
        length++;
        temp= temp.substr(temp.find(c)+1);
    }

    string *words= new string[length];

    for( int i=0;i< length; ++i){
        words[i]= str.substr(0, str.find(c));
        str= str.substr(str.find(c)+1);
    }


    return words;
}


bool Book::update(double isbn, Book d){
    string newContent="";
    ifstream books;
    books.open("books.txt");


    string rec;

    while(getline(books, rec)){
        int l;

        string *fields= split_string(rec, '\t', l);
        double f_isbn= stod(fields[2]);
        delete [] fields;

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
    cout << endl;
    Book* rec= new Book();
    ifstream file;
    file.open("books.txt");


    string line;

    while(getline(file, line)){

        int l=0;

        string *fields= split_string(line, '\t', l);

        rec->title    = fields[0];
        rec->authors  = fields[1];
        rec->isbn     = stod(fields[2]);
        rec->quantity = stoi(fields[3]);

        delete [] fields;
        if(isbn==rec->isbn)
                return rec;
    }
    return NULL;

}

bool Book::remove_book(){
   cout << "Enter the ISBN number of book you want to remove: ";
   cin >>isbn;
   ifstream file("books.txt");
   string newContent;
   string line;

   while(getline(file, line)){

        int l=0;
        string *fields= split_string(line, '\t', l);
        if(isbn!=stod(fields[2]))
                newContent+=line+"\n";
        delete [] fields;
    }


    ofstream o_books("books.txt");
    o_books << newContent;

    cout << "Book record has been deleted successfully." << endl;
    return true;
}

bool Book::issue_book(){
    ofstream file("issue_history.txt");

    cout << "Enter the ISBN of book you want to issue: ";
    cin >> isbn;

    if(findRec(isbn)==NULL){
        cout << "Sorry sir, no book with this ISBN number exist in system." << endl;
        return false;
    }

    string issuer, borrower, issue_date, return_date;

    cout << "Enter issuer Email: ";
    cin >> issuer;

    cout << "Enter borrower Email: ";
    cin >> borrower;


    cout << "Enter issue date(mm/dd/yyyy):";
    cin >> issue_date;

    cout << "Enter return date(mm/dd/yyyy): ";
    cin >> return_date;






}



Book::~Book()
{
    //dtor
}
