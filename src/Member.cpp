#include "Member.h"


Member::Member(int r, double cnic, string n, double cn){
    regNo=r;
    CNIC=cnic;
    name=n;
    cellNo=cn;
}

double Member::getCNIC(){
    return CNIC;
}

Member::~Member()
{
    //dtor
}
