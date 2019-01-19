//SSNSet.cpp
#include <iostream>
#include "SSNSet.h"
#include "Set.h"

// Create an empty SSN set.
SSNSet::SSNSet()
{
    
}


// Add an SSN to the SSNSet.  Return true if and only if the SSN
// was actually added.
bool SSNSet::add(unsigned long ssn)
{
    return m_ssnset.insert(ssn);
}


// Return the number of SSNs in the SSNSet
int SSNSet::size() const
{
    return m_ssnset.size();
}


// Write every SSN in the SSNSet to cout exactly once, one per
// line.  Write no other text.
void SSNSet::print() const
{
    ItemType temp;
    for(int i=0;i<m_ssnset.size();i++)
    {
        m_ssnset.get(i,temp);
        std::cout<<temp<<std::endl;
    }
}

