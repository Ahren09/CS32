
#include <iostream>
#include <cassert>
#include <stdio.h>
#include "Set.h"

void test1();
void test2();
void test3();

int main()
{
    test1();
    test2();
    std::cout << "Passed all tests" << std::endl;
}

//test2() tests the copy constructor, assignment operator, unite() and subtract()
void test2()
{
    Set a;
    a.insert("a_first");
    a.insert("b_second");
    a.insert("c_third");
    a.insert("d_fourth");
    Set b;
    b.insert("c_third");
    b.insert("d_fourth");
    b.insert("e_fifth");
    
    //test unite()
    Set c;
    unite(a,b,c);
    assert(c.size()==5 && c.contains("e_fifth") && c.contains("d_fourth")
           && c.contains("b_second"));
    
    //test subtract()
    Set d;
    subtract(a,b,d);
    assert(d.size()==2 && !d.contains("d_fourth") && d.contains("b_second"));
    
    //e is an empty set, so d should be empty
    Set e;
    Set f;
    f.insert("f_sixth");
    subtract(e, a, f);
    assert(e.size()==0 && f.size()==0);
    subtract(e, a, d);
    
    //Now d is empty, e should be equal to a
    subtract(a,d,e);
    assert(e.size()==4 && e.contains("a_first") && e.contains("b_second") &&
           e.contains("c_third") && e.contains("d_fourth"));
    
    //a equals b, then a subtract b is empty Set
    subtract(a, e, d);
    assert(d.empty());
    
    Set ss;
    ss.insert("ccc");
    ss.insert("aaa");
    ss.insert("bbb");
    ItemType x = "abc";
    assert(!ss.get(3, x)  &&  x == "abc");  // x is unchanged
    assert(ss.get(1, x)  &&  x == "bbb");
    // exactly 1 item
    Set ss2;
    ss2.insert("nothing");
    ss2=ss;
    assert(ss2.size()==3);
    
    
}

//test1() tests the rest of functions
void test1()
{
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
    for(int i=0;i<4;i++)
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
    Set s3=s1;
    assert(s1.size()==3 && !s1.get(3,x));
}
