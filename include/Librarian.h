#ifndef LIBRARIAN_H
#define LIBRARIAN_H
#include <string>


using namespace std;

class Librarian
{
    private:
        string username;
        string email;
        string password;
        string security_quest;
        string security_ans;
    public:
        Librarian();
        bool login();
        bool update(string email, Librarian d);
        static Librarian* findRec(string email);
        bool issue_book();
        bool deposit_book();

        bool register_user();
        bool forgot_pass();

        string getUsername();
        string getEmail(){
            return email;
        }

        ~Librarian();





};

#endif // LIBRARIAN_H
