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
        string getUsername();
        bool update(string email, Librarian d);
        static Librarian* findRec(string email);

        ~Librarian();
        bool register_user();
        bool forgot_pass();





};

#endif // LIBRARIAN_H
