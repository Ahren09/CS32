#include "Set.h"

Set::Set()
{
    m_numOfItems=0;
}

bool Set::empty() const
{
    if(m_numOfItems==0)
        return true;
    return false;
}

int Set::size() const
{
    return m_numOfItems;
}


// Insert value into the set if it is not already present.  Return
// true if the value was actually inserted.  Leave the set unchanged
// and return false if the value was not inserted (perhaps because it
// was already in the set or because the set has a fixed capacity and
// is full).


/*
 PSEUDOCODE:
 
IF set is full
    RETURN FALSE
 
ELSE IF set is empty
    insert value at the start of the set
    INCREMENT number of items by 1

ELSE
    INITIALIZE count to 0
 
    WHILE count is smaller than number of items
         IF item at position count <= value
            INCREMENT count by 1
         ELSE
             insert value at position count
             move the items behind the new item by 1
             BREAK
         insert value at end of the set
         INCREMENT number of items by 1
 
    ENDWHILE
 
 RETURN TRUE
 
 ENDIF
 
 */

bool Set::insert(const ItemType& value)
{
    //set is full, element cannot be inserted
    if(m_numOfItems==DEFAULT_MAX_ITEMS)
        return false;
    
    //empty set, element can be inserted
    else if(empty())
    {
        m_set[0]=value;
        m_numOfItems++;
    }
    
    //normal condition, element can be inserted in the middle
    else
    {
        int i=0;
        
        while(i<m_numOfItems)
        {
            if(m_set[i]<value)
                i++;
            else break;
        }
        
        if(m_set[i]==value)
            return false;
        
        else if(i!=m_numOfItems)
        {
            move(i, true);
            m_set[i]=value;
        }
        
        //inserted element is the greatest
        else
        {
            
            m_set[m_numOfItems]=value;
        }
        m_numOfItems++;
    }
    return true;
    
}





// Remove the value from the set if present.  Return true if the
// value was removed; otherwise, leave the set unchanged and
// return false.

/*
 PSEUDOCODE:
 IF set is empty OR value is greater than the last item in the set
    RETURN FALSE
 
 ENDIF
 
 set count to zero
 
 WHILE ItemType at position count is smaller than value
    increment count by 1
 ENDWHILE
 
 IF item at position count is equal to value
     copy all items after this value to their respective preceding item
     RETURN TRUE
 
 ELSE
    RETURN FALSE

 ENDIF

 
 */

bool Set::erase(const ItemType& value)
{
    if(empty()||value>m_set[m_numOfItems-1])
        return false;
    
    int i=0;
    while(i<m_numOfItems)
    {
        if(m_set[i]<value)
            i++;
        else if(m_set[i]==value)
        {
            move(i,false);
            m_numOfItems--;
            return true;
        }
        else return false;
    }
    
    return false;
    
    
    
}

// Return true if the value is in the set, otherwise false.
bool Set::contains(const ItemType& value)
{
    if(empty())
        return false;
    int i=0;
    while(i<m_numOfItems)
    {
        if(m_set[i]<value)
            i++;
        else if(m_set[i]==value)
            return true;
        else return false;
    }
    return false;
    
}


// If 0 <= i < size(), copy into value the item in the set that is
// strictly greater than exactly i items in the set and return true.
// Otherwise, leave value unchanged and return false.

/*
 get() fails when:
 1. index out of bounds
 2. the set is empty
 */

bool Set::get(int i, ItemType& value)
{
    if(i<0||i>=m_numOfItems||empty())
        return false;
    
    value = m_set[i];
    return true;
    
}

// Exchange the contents of this set with the other one.
void Set::swap(Set& other)
{
    for(int i=0;i<m_numOfItems||i<other.m_numOfItems;i++)
    {
        ItemType temp=m_set[i];
        m_set[i]=other.m_set[i];
        other.m_set[i]=temp;
    }
    int temp=m_numOfItems;
    m_numOfItems=other.m_numOfItems;
    other.m_numOfItems=temp;
    
    
}

bool Set::move(int i,bool moveForward)
{
    if(moveForward)
    {
        if(m_numOfItems==DEFAULT_MAX_ITEMS)
        {
            return false;
        }
        
        //vacate i th item for the new element
        int k=m_numOfItems;
        while(k>i)
        {
            m_set[k]=m_set[k-1];
            k--;
        }
        return true;
    }
    else
    {
        if(m_numOfItems==0)
            return false;
        
        //the i th item is destroyed
        //moving items starting from m_set[i]
        int k=i;
        while(k<m_numOfItems-1)
        {
            m_set[k]=m_set[k+1];
            k++;
        }
        return true;
    }
    
}
