#include <stack>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cassert>

using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    stack<Coord> s;
    Coord start(sr,sc);
    
    s.push(start);
    while(!s.empty())
    {
        Coord cur=s.top();
        s.pop();
        int r=cur.r();
        int c=cur.c();
        cerr<<"("<<r<<','<<c<<")"<<endl;
        //Mark current position as "Visited" - '@'
        maze[r][c]='@';
        
        //If current coordinates equal the destination, then we reach the end.
        if(r == er && c == ec)
            return true;
        
        //Check coordinates of each direction
        if(maze[r+1][c] == '.')
        {
            Coord south(r+1,c);
            s.push(south);
        }
        if(maze[r][c-1] == '.')
        {
            Coord west(r,c-1);
            s.push(west);
        }
        if(maze[r-1][c] == '.')
        {
            Coord north(r-1,c);
            s.push(north);
        }
        if(maze[r][c+1] == '.')
        {
            Coord east(r,c+1);
            s.push(east);
        }
    }
    return false;
}

int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X....X...X",
        "X.XX.XX..X",
        "XXX....X.X",
        "X.XXX.XXXX",
        "X.X...X..X",
        "X...X.X..X",
        "XXXXX.X.XX",
        "X........X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10,10, 3,5, 8,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
