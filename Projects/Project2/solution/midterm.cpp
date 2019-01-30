
#include <stdio.h>

void swapLastNode()
{
    if(!head || head==tail)
        return;
    Node* q=tail;
    Node* p=tail->prev;
    
    q->prev=p->prev;
    if(p->prev)
        p->prev->next=q;
    else head->next=q;
    
    p->next=nullptr;
    p->prev=q;
    q->next=p;
    
    tail=p;
    
}
