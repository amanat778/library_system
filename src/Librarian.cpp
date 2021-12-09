#include "Librarian.h"
#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

string input_pass();

Librarian::Librarian()
{

}

string Librarian::getUsername(){
    return username;
}


string security_quests[3]={
    "What was your first shool name?",
    "What is your pet name?",
    "What is the name of your favourite teacher?"
};

bool Librarian::register_user(){
    cout << endl;
    string p1, p2;
    cin.ignore();
    cout << "Enter user name: ";
    getline(cin, username);

    cout << "Enter email: ";
    cin >> email;

    if(findRec(email)!=NULL){
        int choice;
        cout << "An account with this email already exist. \n"
             << "1: Login\n"
             << "2: Forgot Password\n"
             << "Enter your choice: ";
        cin >> choice;
        choice==1 ? login() : forgot_pass() ;

        return false;
    }

    cout << endl;
    for(int i=0; i<3; ++i)
        cout <<i+1 << " " <<security_quests[i] << endl;

    int choice;
    cout << "Choose your security question :  ";
    cin >> choice;
    security_quest= security_quests[choice-1];

    cin.ignore();
    cout << "Enter answer of the question: ";

    getline(cin, security_ans);





    do{
        cout << "ONLY CHARACTER AND NUMBERS ARE ALLOWED IN PASSWORD." << endl;
        cout << "Enter password :";
        p1= input_pass();

        cout << "Enter password again:";
        p2=input_pass();
        if(p1!=p2)
            cout << "Password mismatch. Enter again." << endl;
    }while(p1!=p2);
    password=p1;






    ofstream o_accounts("accounts.txt", ios::app);
    o_accounts << username+"\t"+email+"\t"+password+"\t"+security_quest+"\t"+security_ans+"\n";
    o_accounts.close();

    cout << "Your account has been created. You are now logged in as \"" << username << "\""<< endl;
    return true;
}

string input_pass(){
    string p;

    char temp;
    do{

        temp= getch();
        if( ( temp>='a' && temp <='z') || (temp>='A' && temp <='Z') || (temp>='0' && temp <='9')){
            p+=temp;
            putch('*');
        }
        if( int(temp) == 8 && p.size()>0 ){
            cout << "\b \b";
            p= p.substr(0, p.size()-1);
        }
    }while( temp!= '\r');

    cout << endl;

    return p.substr(0, p.size());
}
bool Librarian::forgot_pass(){
    cout << endl;
    string email;
    cout << "Enter your email address : ";
    cin >> email;

    Librarian* rec= findRec(email);

    string answer;
    cout << rec->security_quest << endl;
    cout << "Your answer: ";
    cin.ignore();
    getline(cin,answer);

    cout << rec->security_ans << "   " << answer << endl;

    if(rec->security_ans== answer){
        string p1, p2;
        do{
            cout << "ONLY CHARACTER AND NUMBERS ARE ALLOWED IN PASSWORD." << endl;

            cout << "Enter new password: ";
            p1= input_pass();

            cout << "Enter new password again: ";
            p2= input_pass();

            if(p1!=p2)
                cout << "Password did not match. Enter again. " << endl;
        }while(p1!=p2);

        rec->password= p1;
        update(email, *rec);
        cout << "Your password has been updated successfully. You can now login. " << endl;
        return login();

    }

    cout << "Your entered the wrong answer. " << endl;
    return false;

}


bool Librarian::update(string email, Librarian d){
    string newContent="";
    ifstream accounts;
    accounts.open("accounts.txt");


    string account_info;

    while(getline(accounts, account_info)){
        char delimiter='\t';

        string f_email;
        string temp= account_info.substr(account_info.find(delimiter)+1);
        f_email= temp.substr(0,  temp.find(delimiter));
        account_info+="\n";
        if(email==f_email)
                account_info= d.username+"\t"+d.email+"\t"+d.password+"\t"+d.security_quest+"\t"+d.security_ans+"\n";



        newContent+=account_info;


    }

    ofstream o_accounts("accounts.txt");

    o_accounts << newContent;

}
bool Librarian::login(){
    cout << endl;
    cout << "Enter email: ";
    cin >> email;


    cout << "ONLY CHARACTER AND NUMBERS ARE ALLOWED IN PASSWORD." << endl;
    cout << "Enter password: ";
    cin.ignore();
    //getline(cin, password);
    password= input_pass();

    Librarian* rec=findRec(email);




    if(rec && rec->password == password ){
        username= rec->username;
        security_quest= rec->security_quest;
        security_ans= rec->security_ans;
        cout << "You are now logged in as \"" << username << "\"" << endl;

        return true;
    };

    if(rec==NULL)
        cout << "This email is not registered. Login Again(y/n):  ";
    else if(rec->password!= password)
        cout << "Password did not match. Login Again(y/n): ";

    char choice;
    cin >> choice;
    if(choice=='y' || choice=='Y'){
        login();
    }

    return false;
};


Librarian* Librarian::findRec(string email){
    Librarian* rec= new Librarian();
    ifstream accounts;
    accounts.open("accounts.txt");


    string account_info;

    while(getline(accounts, account_info)){
        char delimiter='\t';


        rec->username= account_info.substr(0,  account_info.find(delimiter));
        account_info= account_info.substr(account_info.find(delimiter)+1);
        rec->email= account_info.substr(0,  account_info.find(delimiter));
        account_info= account_info.substr(account_info.find(delimiter)+1);
        rec->password= account_info.substr(0,account_info.find(delimiter));
        account_info= account_info.substr(account_info.find(delimiter)+1);
        rec->security_quest= account_info.substr(0,account_info.find(delimiter));
        account_info= account_info.substr(account_info.find(delimiter)+1);
        rec->security_ans= account_info.substr(0, account_info.find(delimiter));

        if(email==rec->email)
                return rec;


    }
    return NULL;

}

Librarian::~Librarian()
{
    //dtor
}
