#include <stdio.h>
#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    
    //##### TEST FOR std::string #####

    //Test the initialization of Set
    Set s;
    
    assert(s.empty());
    ItemType x = "arepa";
    
    //Test empty()
    assert( !s.get(42, x)  &&  x == "arepa" && s.empty()); // x unchanged since get() fails
   
    //Test insert() and size()
    s.insert("chapati");
    assert(s.size() == 1);
    assert(s.get(0, x)  &&  x == "chapati");
    s.insert("luzhu");
    s.insert("chaogan");
    s.insert("luzhu");          //Duplicate should not be inserted
    s.insert("guanchang");
    assert(s.size() == 4);
    
    //Test get()
    assert(s.get(0,x) && x=="chaogan");
    assert(s.get(3,x) && x=="luzhu");
    
    //Test swap()
    Set s1;
    s1.insert("roti");
    s1.insert("matzo");
    s1.insert("roti");
    s1.swap(s);
    
    //Test contains()
    ItemType y;
    assert(s.size()==2 && s.get(0,x) && x=="matzo" && s1.size()==4
           && s1.get(0,y) && y=="chaogan" && s1.get(3,y) && y=="luzhu");
    assert(s1.contains("guanchang") && s.contains("matzo"));
    
    //Test erase()
    //Erase elements at the beginning
    assert(s1.erase("chaogan"));
    assert(s1.size()==3);
    assert(s1.get(0,x) && x=="chapati");
    
    //Erase elements in the middle
    assert(s1.erase("guanchang") && !s1.contains("guanchang"));
    assert(s1.erase("luzhu") && !s1.contains("luzhu"));
    
    //Erase non-existent element
    //NOTICE: size should NOT be changed
    assert(!s1.erase("Luzhu") && s1.size()==1);
    
    //Inserting empty string
    //Test that "" is a valid variable of ItemType
    assert(!s1.contains(""));
    s1.insert("");
    assert(s1.contains("") && s1.size()==2);
    assert(s1.insert("hotpot"));
    
    //Test the copy constructor
    Set s2(s1);
    assert(s2.size()==3 && s2.get(0,x) && x=="");
    
    //Test the assignment operator;
    Set s3;
    s3=s1;
    assert(s1.size()==3 && !s1.get(3,x));
    
    cout << "Passed all tests" << endl;
    
    //##### TEST FOR unsigned long #####
    
    /*
    //Test the initialization of Set
    Set s;
    
    //Test empty() and get()
    assert(s.empty());
    ItemType x = 9876543;
    assert(!s.get(42, x)  &&  x == 9876543); // x unchanged by get failure
    s.insert(123456789);
    assert(s.size() == 1);
    assert(s.get(0, x)  &&  x == 123456789 && !s.empty());
    
    //Test insert()
    s.insert(222222222);
    s.insert(333222333);
    
    //Test whether duplicates are not inserted
    assert(!s.insert(222222222) && s.size()==3);
    assert(s.insert(111111111) && s.size()==4);
    
    //Test whether elements are in the right order
    assert(s.get(0,x) && x==111111111);
    assert(s.get(3,x) && x==333222333);
    
    //Test contains() function
    assert(s.contains(111111111) && !s.contains(111111));
    
    //Test the compiler-generated copy constructor
    Set s1=s;
    assert(s.size()==4 && s1.get(3,x) && x==333222333);
    
    //Test the compiler-generated assignment operator;
    Set s2;
    s1=s2;
    assert(s1.size()==0 && !s1.get(0,x));
    
    s1.swap(s);
    assert(s.size()==0 && s.empty() &&
           s1.size()==4 && s1.contains(333222333));
    
    //Test erase() function
    assert(s1.erase(111111111) && s1.size()==3);
    assert(!s1.erase(111111111));
    
    
    cout << "Passed all tests" << endl;
 */
}

