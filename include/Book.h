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
        static Book* findRec(double isbn);
        static bool update(double isbn, Book d);
        bool update_book();
        bool remove_book();
        bool search_book();
        bool issue_book();
        void view_stock();
        void display_row();
        string getTitle(){
            return title;
        }
        void decrement_qty(){
            --quantity;
        }

        void increment_qty(){
            ++quantity;
        }


        Book();
        ~Book();



};



#endif // BOOK_H
