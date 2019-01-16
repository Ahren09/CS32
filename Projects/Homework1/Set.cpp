#include "Set.h"

using content=std::string;

Set::Set(){
    
    m_set="";
    
    
}

bool Set::empty const(){
    if(m_set=="")
        return true;
    return false;
}

int Set::size() const{
    return m_set.length();
    
}
