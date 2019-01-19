//testSSNSet.cpp
#include <iostream>
#include "SSNSet.h"
using namespace std;


int main()
{
    SSNSet s;
    assert(s.size()==0);
    //ItemType man1 = 123456789;
    
    //Insertion
    s.add(888444888);
    assert(s.size() == 1);
    s.add(111111111);
    s.add(777373733);
    
    //Print all elements
    //s.print();
    
    //Insertion fails since the number is a duplicate
    assert(!s.add(111111111) && s.size()==3);
    
    
    
    cout << "Passed all tests" << endl;
    
}

