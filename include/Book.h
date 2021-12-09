#ifndef BOOK_H
#define BOOK_H
#include <string>

using namespace std;

class Book
{
    private:
        double isbn;
        string title;
        string authors;
        int quantity;

    public:

        bool add_book();
        Book();
        ~Book();



};

#endif // BOOK_H
