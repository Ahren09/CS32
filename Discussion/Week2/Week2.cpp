
#include <iostream>

//#2
class A {
public:
    A(int sz) {
        n = sz;
        b = new B;
        arr = new int[n];
    }
    A(const A& other)
    :n(other.n),str(other.str)
    {
        b = new B(other.b); //SHOULD BE: b = new B(*other.b);
        arr=new int[n];
        for(int i=0;i<n;i++)
        {
            arr[i]=other.arr[i];
        }
    }
    A& operator=(const A& other)
    {
        //MISSING: If(*this==other) return *this;
        n=other.n;
        str=other.str;
        delete [] arr;
        delete b;
        
        for(int i=0;i<n;i++)
        {
            arr[i]=other.arr[i];
        }
        *b=new B(*other.b);
    }

    ~A() {
        delete [] arr;
        delete b;
    }
private:
    //one dynamically allocated B object; assume B has a default
    //constructor, a copy constructor, and an assignment operator
    B* b;
    //dynamically allocated array
    int* arr;
    //size of arr (determined by a constructor)
    int n;
    string str;
};

//#4

Billionaire::Billionaire(int other)
:account(other.account),name(other.n.name)
{
    offshore=new Account(other.offshore);
    
}

//#5
int cmpr(Node* head, int *arr, int arr_size)
{
    int i=0;
    while(head && i<arr_size)
    {
        if(i==0)
            if(head->val!=*(arr))
                return -1;
        if(head->val==*(arr+i))
        {
            head=head->next;
            i++;
        }
        else return i;
    }
    return arr_size;
}
