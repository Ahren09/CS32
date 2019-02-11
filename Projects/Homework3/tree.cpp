#include <iostream>

using namespace std;
// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then for this value of a2     the function must return
//    10 20 40            1
//    10 40 30            2
//    20 10 40            0
//    50 40 30            3
int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
    //If n1 and n2 both equal 0, then result is 1
    if(n1<=0) n1=0;
    if(n1<n2)
        return 0;
    if(n2==0)
        return 1;
    
    //The first elements in current arrays are equal
    //There are two conditions:
    //We search current first element of a2 in subarray of a1
    //We search current second element of a2 in subarray of a1
    if(a1[0]==a2[0])
    {
        int fromCurrent=countIncludes(a1+1,n1-1,a2+1,n2-1);
        int fromNext=countIncludes(a1+1, n1-1, a2, n2);
        return fromCurrent+fromNext;
    }
    else return countIncludes(a1+1, n1-1, a2, n2);
    
}

// Exchange two doubles
void exchange(double& x, double& y)
{
    double t = x;
    x = y;
    y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is > divider come before all the other elements,
// and all the elements whose value is < divider come after all
// the other elements.  Upon return, firstNotGreater is set to the
// index of the first element in the rearranged array that is
// <= divider, or n if there is no such element, and firstLess is
// set to the index of the first element that is < divider, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotGreater, a[i] > divider
//   * for firstNotGreater <= i < firstLess, a[i] == divider
//   * for firstLess <= i < n, a[i] < divider
// All the elements > divider end up in no particular order.
// All the elements < divider end up in no particular order.
void divide(double a[], int n, double divider,
            int& firstNotGreater, int& firstLess)
{
    if (n < 0)
        n = 0;
    
    // It will always be the case that just before evaluating the loop
    // condition:
    //  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
    //  Every element earlier than position firstNotGreater is > divider
    //  Every element from position firstNotGreater to firstUnknown-1 is
    //    == divider
    //  Every element from firstUnknown to firstLess-1 is not known yet
    //  Every element at position firstLess or later is < divider
    
    firstNotGreater = 0;
    firstLess = n;
    int firstUnknown = 0;
    while (firstUnknown < firstLess)
    {
        if (a[firstUnknown] < divider)
        {
            firstLess--;
            exchange(a[firstUnknown], a[firstLess]);
        }
        else
        {
            if (a[firstUnknown] > divider)
            {
                exchange(a[firstNotGreater], a[firstUnknown]);
                firstNotGreater++;
            }
            firstUnknown++;
        }
    }
}

// Rearrange the elements of the array so that
// a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
// If n <= 1, do nothing.
void order(double a[], int n)
{
    if(n<=1)
        return;
    int firstNotGreater, firstLess;
    divide(a,n,a[n/2],firstNotGreater,firstLess);
    order(a,firstNotGreater);
    order(a+firstLess, n-firstLess);
}

//void printArr(double a[], int n)
//{
//    for(int i=0;i<n;i++)
//        cerr<<a[i]<<',';
//}
//
//int main()
//{
//    double a1_1[]={10,50,40,20,50,40,30};
//    double a2_1[]={10,20,40};
//    double a2_2[]={10,40,30};
//    double a2_3[]={20,10,40};
//    double a2_4[]={50,40,30};
//    double a2_5[]={10,20,20};
//    assert(countIncludes(a1_1, 7, a2_1, 3) == 1);
//    assert(countIncludes(a1_1, 7, a2_2, 3) == 2);
//    assert(countIncludes(a1_1, 7, a2_3, 3) == 0);
//    assert(countIncludes(a1_1, 7, a2_4, 3) == 3);
//    assert(countIncludes(a1_1, 7, a2_4, 0) == 1);
//    assert(countIncludes(a1_1, 0, a2_4, 1) == 0);
//    assert(countIncludes(a1_1, 0, a2_4, 0) == 1);
//    assert(countIncludes(a1_1, 7, a2_5, 3) == 0);
//
//    double a1[8]={1,7,5,9,8,6,4,2};
//    double a2[9]={9,5,4,8,4,7,2,6,3};
//    double a3[8]={5,5,5,5,5,5,5,9};
//
//    order(a1, 8);
//    printArr(a1, 8);
//    cerr<<endl;
//    order(a2,9);
//    printArr(a2, 9);
//    cerr<<endl;
//    order(a3,8);
//    printArr(a3, 8);
//
//}
