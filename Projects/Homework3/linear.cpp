bool somePredicate(double x);

// Return true if the somePredicate function returns true for at
// least one of the array elements, false otherwise.

bool anyTrue(const double a[], int n)
{
    if(n<=0)
        return false;
    return somePredicate(a[0]) || anyTrue(a+1,n-1); // This is not always correct.
}

// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const double a[], int n)
{
    if(n<=0)
        return 0;
    return somePredicate(a[0]) ? 1+countTrue(a+1, n-1):countTrue(a+1, n-1);
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const double a[], int n)
{
    if(n<=0) return -1;

    //true1 indicates the first element in current array that evaluates to true
    int true1 = firstTrue(a, n-1);

    if(true1==-1)
        return somePredicate(a[n-1]) ? n-1 : -1;
    else return true1;

/*
     Here is another implementation
     Evaluate the statement from end to start
     
    if(n<=0) return -1;
    
    //true1 indicates the first element in current array that evaluates to true
    int true1 = firstTrue(a+1, n-1);
    

    //IF current statement is true
    if(somePredicate(a[0]))
    {
        return 0;
    }
    //IF current statement is false
    else return true1==-1 ? -1 : 1+true1;
 
 */
}

// Return the subscript of the smallest element in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
int positionOfMin(const double a[], int n)
{
    if(n<=0)
        return -1;
    if(n==1)
        return 0;
    int smallest=positionOfMin(a, n-1);
    return (a[n-1]<a[smallest]) ? n-1 : smallest;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20

bool includes(const double a1[], int n1, const double a2[], int n2)
{
    //if n2 and n1 are both empty, return true;
    if(n2<=0)
    { return true; }
    if(n1<=0)
    { return false; }
    return (a1[0] == a2[0]) ? includes(a1+1,n1-1,a2+1,n2-1) : includes(a1+1,n1-1, a2, n2);
}


//int main()
//{
//    double a[] = {1,2,3,4,1};
//    double b[]={10,1,5,4,1,2};
//    double c[]={6,5,5,5,1};
//
//    cout<<anyTrue(a,5)<<endl;
//    cout<<countTrue(a,5)<<endl;
//    cout<<firstTrue(a,5)<<endl;
//    cout<<firstTrue(b,5)<<endl;
//    cout<<firstTrue(c,5)<<endl;
//    cout<<firstTrue(c,0)<<endl;
//    cout<<firstTrue(c+4,1)<<endl<<endl;
//
//    cout<<positionOfMin(a,5)<<endl;
//    cout<<positionOfMin(b,5)<<endl;
//    cout<<positionOfMin(b,4)<<endl;
//    cout<<positionOfMin(c,5)<<endl;
//
//    double a1_1[]={10,50,40,20,50,40,30};
//    double a2_1[]={50,20,30};
//    double a2_2[]={50,40,40};
//    double a2_3[]={50,30,20};
//    double a2_4[]={10,20,20};
//    double a2_5[]={};
//
//    assert(includes(a1_1,7,a2_1,3));
//    assert(includes(a1_1,7,a2_2,3));
//    assert(!includes(a1_1,7,a2_3,3));
//    assert(!includes(a1_1,7,a2_4,3));
//    assert(includes(a1_1,7,a2_4,0));
//    assert(includes(a1_1,7,a2_4,-1));
//    cerr<<"Pass all tests"<<endl;
//
//
//}


