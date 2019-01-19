#include <stdio.h>
#include "newSet.h"
#include <iostream>
#include <cassert>
using namespace std;


int main()
{
    
     //##### TEST FOR std::string #####
    
    Set s;
    assert(s.empty());
    ItemType x = "arepa";
    assert( !s.get(42, x)  &&  x == "arepa"); // x unchanged since get() fails
    s.insert("chapati");
    assert(s.size() == 1);
    assert(s.get(0, x)  &&  x == "chapati");
    s.insert("luzhu");
    s.insert("chaogan");
    s.insert("luzhu");          //Duplicate should not be inserted
    s.insert("guanchang");
    assert(s.size() == 4);
    assert(s.get(0,x) && x=="chaogan");
    assert(s.get(3,x) && x=="luzhu");
    
    
    Set s1;
    s1.insert("roti");
    s1.insert("matzo");
    s1.insert("roti");
    s1.swap(s);
    ItemType y;
    assert(s.size()==2 && s.get(0,x) && x=="matzo" && s1.size()==4
           && s1.get(0,y) && y=="chaogan" && s1.get(3,y) && y=="luzhu");
    assert(s1.contains("guanchang") && s.contains("matzo"));
    
    //Erase elements at the beginning
    assert(s1.erase("chaogan"));
    assert(s1.size()==3);
    assert(s1.get(0,x) && x=="chapati");
    
    //Erase elements in the middle
    assert(s1.erase("guanchang") && !s1.contains("guanchang"));
    assert(s1.erase("luzhu") && !s1.contains("luzhu"));
    
    //Erase non-existent element
    //size should NOT be changed
    assert(!s1.erase("Luzhu") && s1.size()==1);
    
    s1.insert("");
    assert(s1.contains("") && s1.size()==2);
    
    
    cout << "Passed all tests" << endl;
    
    
    /*
    //##### TEST FOR unsigned long #####
    
    Set s;
    assert(s.empty());
    ItemType x = 9876543;
    assert( !s.get(42, x)  &&  x == 9876543); // x unchanged by get failure
    s.insert(123456789);
    assert(s.size() == 1);
    assert(s.get(0, x)  &&  x == 123456789);
    cout << "Passed all tests" << endl;
     */
}
