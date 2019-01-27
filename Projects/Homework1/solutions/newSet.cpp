// SSNSet.cpp

#include "Set.h"
#include "SSNSet.h"
#include <iostream>
using namespace std;

void SSNSet::print() const
{
    for (int k = 0; k < m_SSNs.size(); k++)
    {
        unsigned long x;
        m_SSNs.get(k, x);
        cout << x << endl;
    }
}
