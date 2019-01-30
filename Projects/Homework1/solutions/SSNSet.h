// SSNSet.h

#ifndef SSNSET_INCLUDED
#define SSNSET_INCLUDED

#include "Set.h"  // ItemType is a type alias for unsigned long

class SSNSet
{
public:
    SSNSet();          // Create an empty SSNSet
    
    bool add(unsigned long ssn);
    // Add an SSN to the SSNSet.  Return true if and only if the SSN
    // was actually added.
    
    int size() const;  // Return the number of SSNs in the SSNSet.
    
    void print() const;
    // Write every SSN in the SSNSet to cout exactly once, one per
    // line.  Write no other text.
    
private:
    Set m_SSNs;
};

// Inline implementations

// Actually, we did not have to declare and implement the default
// constructor:  If we declare no constructors whatsoever, the compiler
// writes a default constructor for us that would do nothing more than
// default construct the m_SSNs data member.

inline
SSNSet::SSNSet()
{}

inline
bool SSNSet::add(unsigned long ssn)
{
    return m_SSNs.insert(ssn);
}

inline
int SSNSet::size() const
{
    return m_SSNs.size();
}

#endif // SSNSET_INCLUDED
