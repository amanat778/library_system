#ifndef MEMBER_H
#define MEMBER_H
#include <string>

using namespace std;

class Member
{
    private:
        int regNo;
        double CNIC;
        string name;
        double cellNo;

    public:
        Member(int r, double cnic, string n, double cn);
        double getCNIC();

        ~Member();




};

#endif // MEMBER_H
