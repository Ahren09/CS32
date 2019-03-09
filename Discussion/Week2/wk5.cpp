
//#2
void LL::deleteList()
{
    deleteListHelper(head);
}

void LL::deleteListHelper(Node* p)
{
    if(!p) return;
    deleteListHelper(p->next);
    delete p;
}

//#3

int fun(int a[],int n)
{
    //Assume n>0
    if(n==1)
        return a[0];
    
    //1
    int last_max=fun(a+1,n-1)
    return a[0]>last_max ? a[0] : last_max;
    
    //2
    int prev_max=fun(a,n-1);
    return a[n-1]>prev_max? a[n-1] : prev_max;
    
}


//#4
string endX(string str)
{
    if(str.size()<=1) //$ Take into account empty string
        return str;
    else if(str[0]=='x')
        return endX(str.substr(1))+'x';
    else return str[0]+endX(str.substr(1));
    
}

//#5
bool isSolvable(int x, int y, int c)
{
    if(c<0)
        return false;
    else if (c==0)
        return true;
    return isSolvable(x,y,c-x) || isSolvable(x,y,c-y);
    
}
