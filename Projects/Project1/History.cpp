#include "History.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
{
    m_nRows=nRows;
    m_nCols=nCols;
    for(int i=0;i<m_nRows;i++)
    {
        for(int j=0;j<m_nCols;j++)
        {
            m_history[i][j]=0;
        }
    }
    
}

bool History::record(int r, int c)
{
    if(r<1||c<1||r>m_nRows||c>m_nCols)
        return false;
    
    m_history[r-1][c-1]++;
    return true;
    
}
void History::display() const
{
    
    //Construct a grid with specified size
    char grid[MAXROWS][MAXCOLS];
    
    for(int i=0;i<m_nRows;i++)
    {
        for(int j=0;j<m_nCols;j++)
        {
            if(m_history[i][j]==0)
                grid[i][j]='.';
            else if(m_history[i][j]>=26)
            {
                grid[i][j]='Z';
            }
            else
            {
                grid[i][j]=m_history[i][j]+'@';
            }
        }
        
    }
    
    //Display grid
    for(int i=0;i<m_nRows;i++)
    {
        for(int j=0;j<m_nCols;j++)
        {
            cout<<grid[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
    
    
}
