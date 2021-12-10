#ifndef BOOK_H
#define BOOK_H
#include <string>

using namespace std;

class Book
{
    private:
        string title;
        string authors;
        double isbn;
        int quantity;

    public:

        bool add_book();
        Book* findRec(double isbn);
        bool update(double isbn, Book d);
        bool update_book();
        bool search_book();

        Book();
        ~Book();



};

#endif // BOOK_H
