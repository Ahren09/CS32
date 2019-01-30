// Set.cpp
#include "Set.h"
Set::Set()
: head(nullptr),tail(nullptr),m_size(0)
{}

Set::~Set()
{
    //Empty list, return directly
    Node *p=head;
    while(head)
    {
        head=head->next;
        delete p;
        p=head;
    }
}

Set::Set(const Set& other)
{
    if(other.empty())
    {
        head=tail=nullptr;
    }
    else
    {
        //Initialize head pointer
        head=new Node;
        head->val=other.head->val;
        Node* n=head;
        Node* src=other.head;
        n->pre=nullptr;
        
        while(src->next)
        {
            src=src->next;
            Node* newNode=new Node;
            newNode->val=src->val;
            newNode->pre=n;
            n->next=newNode;
            
            n=n->next;
        }
        
        n->next=nullptr;                    //Reach the end of list
        tail=n;
    }
    
    m_size=other.m_size;
    
}

Set& Set::operator=(const Set& other)
{
    if(this!=&other)
    {
        Node* p=head;
        while(p)
        {
            head=head->next;
            delete p;
            p=head;
        }
        head=tail=nullptr; //###
        m_size=0;
        if(!other.head)
            return *this;
        head=new Node;
        head->val=other.head->val;
        p=head;
        p->pre=nullptr;
        Node* src=other.head;
        
        while(src->next)
        {
            src=src->next;
            Node* newNode=new Node;
            newNode->val=src->val;
            p->next=newNode;
            newNode->pre=p;
            p=newNode;
        }
        tail=p;
        p->next=nullptr;
        m_size=other.m_size;
    }
    return *this;
}


int Set::size() const
{
    return m_size;
}

bool Set::empty() const
{
    return m_size == 0;
}

bool Set::insert(const ItemType &value)
{
    Node* p=head;
    Node* q=nullptr;
    
    while(p)
    {
        //Inserted element is a duplicate
        if(p->val==value)
            return false;
        
        //Node with greater val found, break the loop and insert
        else if(p->val>value)
            break;
        
        q=p;
        p=p->next;
        
    }
    
    Node* n=new Node;
    n->val=value;
    n->next=p;
    n->pre=q;
    
    if(p)
        p->pre=n;
    else tail=n;
    
    if(q)
        q->next=n;
    else head=n;
    
    m_size++;
   
    return true;
}


bool Set::erase(const ItemType& value)
{
    //Empty list
    if(!head)
        return false;
    
    //Value is out of the range of the linked list
    else if(value < head->val || value > tail->val)
        return false;
    
    //Value is in the range of the linked list
    Node* p=head;
    
    while(p)
    {
        if(p->val==value)
            break;
        else if(p->val>value)
            return false;
        p=p->next;
    }
    //At head OR NOT
    if(p->pre)
        p->pre->next=p->next;
    else head=p->next;
    
    //At tail OR NOT
    if(p->next)
        p->next->pre=p->pre;
    else tail=p->pre;
    
    delete p;
    m_size--;
    return true;
    
}

bool Set::contains(const ItemType& value) const
{
    if(!head)
        return false;
    else if (value < head->val || value > tail->val)
        return false;
    
    Node* p = head;
    
    //p can never reach the nullptr after the last node
    while(p && p->val<value)
    {
        p=p->next;
    }
    if(p->val == value)
        return true;
    else return false;
}

bool Set::get(int i, ItemType& value) const
{
    //index out of bound, or size of the linked list equals 0
    if(i<0 || i>=m_size || m_size==0)
        return false;
    
    Node* p;
    if(i<m_size/2)
    {
        int index=0;
        p=head;
        while(index<i)
        {
            p=p->next;
            index++;
        }
    }
    else
    {
        int index=m_size-1;
        p=tail;
        while(index>i)
        {
            p=p->pre;
            index--;
        }
            
    }
    value=p->val;
    return true;
    
}

void Set::swap(Set& other)
{
    if(this==&other)
        return;
    
    //Swap the head and tail pointers
    Node* temp;
    temp = head;
    head = other.head;
    other.head=temp;
    
    temp=tail;
    tail=other.tail;
    other.tail=temp;
    
    //Swap sizes
    int temp_size=m_size;
    m_size=other.m_size;
    other.m_size=temp_size;
}

void unite(const Set& s1, const Set& s2, Set& result)
{
    result=s1;
    if(!s2.empty()){
    int i=0;
    ItemType n;
    while(i<s2.size())
    {
        s2.get(i, n);
        result.insert(n);
        i++;
    }
    }
}

void subtract(const Set& s1, const Set& s2, Set& result)
{
    result=s1;
    
    if(!s2.empty()){
    int i=0;
    ItemType n;
    while(i<s2.size())
    {
        s2.get(i, n);
        result.erase(n);
        i++;
    }
    }
}
