#include <string>
#include <iostream>
using namespace std;

void printOutPath(string maze[],int nRows)
{
    for(int i=0;i<nRows;i++)
        cerr<<maze[i]<<endl;
}

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if(sr == er && sc == ec)
        return true;
    maze[sr][sc]='@';
    cout<<'('<<sr<<','<<sc<<')'<<endl;
    
    printOutPath(maze,nRows);
    cin.ignore();
    
    if(maze[sr+1][sc] == '.')
        if(pathExists(maze,nRows,nCols,sr+1,sc,er,ec))
            return true;
    
    if(maze[sr][sc-1] == '.')
        if(pathExists(maze,nRows,nCols,sr,sc-1,er,ec))
            return true;
    
    if(maze[sr-1][sc] == '.')
        if(pathExists(maze,nRows,nCols,sr-1,sc,er,ec))
            return true;
    
    if(maze[sr][sc+1] == '.')
        if(pathExists(maze,nRows,nCols,sr,sc+1,er,ec))
            return true;
    
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
    
    if (pathExists(maze, 10,10, 1,1, 8,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}


