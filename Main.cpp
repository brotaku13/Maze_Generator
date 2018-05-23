#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <unistd.h>
#include <stdio.h>
#include "Maze.h"

using namespace std;

void mazeBFS(Maze* maze);
void mazeBFS(MazeObject* end, queue<MazeObject*>& q, Maze* maze);

void mazeDFS(Maze* maze);
void mazeDFS(MazeObject* node, MazeObject* end, Maze* maze);


int main()
{
    //numbers must be odd: (size_y, size_x)
    //Maze maze(61, 41);
    cout << "Create maze: X x Y" << endl;
    int x, y;
    cout << "X: ";
    cin >> x;
    cout << "Y: ";
    cin >> y;

    //numbers must be odd: (size_y, size_x)
    //Maze maze(y, x);
    Maze* maze = new Maze(x, y);
    maze->buildMaze();
    maze->print();

    int choice = 0;
    while(choice != -1)
    {
        cout << "   0.     DFS" << endl;
        cout << "   1.     BFS" << endl;
        cout << "   2.     Create New Maze" << endl;
        cout << "  -1.     Quit" <<  endl << endl;
        cout << "-->";
        cin >> choice;
        cout << endl;
        switch(choice)
        {
            case 0:
                mazeDFS(maze);
                break;
            case 1:
                mazeBFS(maze);
                break;
            case 2:
                cout << "Create maze: X x Y (use odd numbers)" << endl;
                int x, y;
                cout << "X: ";
                cin >> x;
                cout << endl << "Y: ";
                cin >> y;
                cout << endl;
                delete maze;
                maze = new Maze(x, y);
                break;
            default:
                return 0;
                
        }
        
    }


}

void mazeBFS(Maze* maze)
{
    MazeObject* start = maze->getStartingPoint();
    MazeObject* end = maze->getEndingPoint();

    queue<MazeObject*> q;
    q.push(start);
    mazeBFS(end, q, maze);
    
}

void mazeBFS(MazeObject* end, queue<MazeObject*>& q, Maze* maze)
{
    usleep(50 * 1000);
    system("clear");
    maze->print();

    MazeObject* node = q.front();
    if(node == end || node == nullptr)
        return;
    else
    {
        q.pop();
        node->setSearched();

        if(node->getUp() != nullptr && node->getUp()->isVisited() && !node->getUp()->isSearched())
        {
            q.push(node->getUp());
        }
        if(node->getRight()->isVisited() && !node->getRight()->isSearched())
        {
            q.push(node->getRight());          
        }
        if(node->getDown() != nullptr && node->getDown()->isVisited() && !node->getDown()->isSearched())    
        {
            q.push(node->getDown());
        }    

        if(node->getLeft()->isVisited() && !node->getLeft()->isSearched())
        {
            q.push(node->getLeft());
        }    

        mazeBFS(end, q, maze);
    }
}

void mazeDFS(Maze* maze)
{
    MazeObject* start = maze->getStartingPoint();
    MazeObject* end = maze->getEndingPoint();

    try{
        mazeDFS(start, end, maze);
    }
    catch (exception e){
        cout << endl;
    }
    
}

void mazeDFS(MazeObject* node, MazeObject* end , Maze* maze)
{
    usleep(50 * 1000);
    system("clear");
    maze->print();

    if(node == end || node == nullptr)
        throw exception();
    else
    {
        node->setSearched();

        if(node->getUp() != nullptr && node->getUp()->isVisited() && !node->getUp()->isSearched())
        {
            mazeDFS(node->getUp(), end, maze);
        }
        if(node->getRight()->isVisited() && !node->getRight()->isSearched())
        {
            mazeDFS(node->getRight(), end, maze);        
        }
        if(node->getDown() != nullptr && node->getDown()->isVisited() && !node->getDown()->isSearched())    
        {
            mazeDFS(node->getDown(), end, maze);
        }    

        if(node->getLeft()->isVisited() && !node->getLeft()->isSearched())
        {
            mazeDFS(node->getLeft(), end, maze);
        }    
    }
}