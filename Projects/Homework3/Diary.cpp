#include <string>
#include <iostream>
using namespace std;

class Diary
{
public:
    Diary(const string& title)
    :m_title(title) {}
    virtual ~Diary(){}
    string getTitle() const
    { return m_title; }
    
    virtual void writeEntry(const string& entry)
    { m_entry+=entry; }
    
    virtual string read() const
    { return m_entry; }
    
private:
    string m_title, m_entry;
};

class SecretDiary:public Diary
{
public:
    SecretDiary():Diary("TOP-SECRET"){}
    
    virtual void encode(const string &s) {}
    virtual void decode(const string &s) {}
    
    virtual void writeEntry(const string& s)
    { Diary::writeEntry(encode(s)); }
    
    virtual string read() const
    { return decode(Diary::read());}

    
};
