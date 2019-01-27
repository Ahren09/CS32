// Set.h
#ifndef SET_H
#define SET_H
#include <string>
using ItemType = std::string;

class Set
{
public:
    Set();
    ~Set();
    Set(const Set& other);
    Set& operator=(const Set& other);
    bool empty() const;  // Return true if the set is empty, otherwise false.
    int size() const;    // Return the number of items in the set.
    
    bool insert(const ItemType& value);
    // Insert value into the set if it is not already present.  Return
    // true if the value was actually inserted.  Leave the set unchanged
    // and return false if the value was not inserted (perhaps because it
    // was already in the set or because the set has a fixed capacity and
    // is full).
    
    bool erase(const ItemType& value);
    // Remove the value from the set if present.  Return true if the
    // value was removed; otherwise, leave the set unchanged and
    // return false.
    
    bool contains(const ItemType& value) const;
    // Return true if the value is in the set, otherwise false.
    
    bool get(int i, ItemType& value) const;
    // If 0 <= i < size(), copy into value the item in the set that is
    // strictly greater than exactly i items in the set and return true.
    // Otherwise, leave value unchanged and return false.
    
    void swap(Set& other);
    // Exchange the contents of this set with the other one.
    
private:
    struct Node
    {
        ItemType val;
        Node* next;
        Node* pre;
    };
    
    Node* head;  // the linked list that stores items
    Node* tail;
    int m_size;               // number of items
    
    int findFirstAtLeast(const ItemType& value) const;
    // Return the position of the smallest item in m_data that is >= value,
    // or m_size if there are no such items.
    
    
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);

#endif // SET_INCLUDED
