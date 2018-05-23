
#include "Maze.h"

Maze::Maze()
{
    start = nullptr;
    end = nullptr;
}

Maze::Maze(int size_x, int size_y)
{
    //build top row
    //up, down, right, left
    bool initWithWalls = false;

    start = new MazeObject(initWithWalls);

    // top row
    MazeObject* current = start;
    for(int i = 0; i < size_x - 1; ++i)
    {
        current->setRight(new MazeObject(initWithWalls, nullptr, nullptr, nullptr, current));
        current = current->getRight();
    }
    MazeObject* rowStart = start;
    MazeObject* rowAbove = start;

    for(int i = 0; i < size_y - 1; ++i)
    {
        rowStart->setDown(new MazeObject(initWithWalls, rowStart, nullptr, nullptr, nullptr));
        rowStart = rowStart->getDown();
        current = rowStart;
        for(int j = 0; j < size_x - 1; ++j)
        {
            //build next node
            current->setRight(new MazeObject(initWithWalls, rowAbove->getRight(), nullptr, nullptr, current));
            current = current->getRight();

            //set above links
            rowAbove->getRight()->setDown(current);
            rowAbove = rowAbove->getRight();
        }
        rowAbove = rowStart;
    }
    while(rowStart->getRight() != nullptr)
        rowStart = rowStart->getRight();
    
    end = rowStart;
    setEntrance(start);
    setExit(end);

}

void Maze::print() const
{
    cout << endl <<  "-----------  [ Maze ] -----------" << endl << endl;
    MazeObject* row = start;
    while(row != nullptr)
    {
        MazeObject* col = row;
        while(col != nullptr)
        {
            col->draw();
            col = col->getRight();
        }
        cout << endl;
        row = row->getDown();
    }
    cout << endl;
    //system("clear");
}

void Maze::buildMaze()
{
    //build maze
    MazeObject* drawStart = start->getRight()->getDown();
    buildMaze(drawStart);

    //all nodes not visited are walls
    MazeObject* row = start;
    while(row != nullptr)
    {
        MazeObject* col = row;
        while(col != nullptr)
        {
            col->setWall();
            col = col->getRight();
        }
        row = row->getDown();
    }
}

void Maze::buildMaze(MazeObject* node)
{
    node->setVisited();
    bool possiblePaths[4] = {true, true, true, true};
    int numVisited = 0;
    while(numVisited < 4)
    {
        int choice = rand() % 4;
        if(possiblePaths[choice])
        {
            ++numVisited;
            possiblePaths[choice] = false;

            switch(choice)
            {
                case 0:
                    if(node->getUp() != nullptr && node->getUp()->getUp() != nullptr)
                    {
                        if(!node->getUp()->getUp()->isVisited())
                        {
                            node->getUp()->setVisited();
                            buildMaze(node->getUp()->getUp());
                        }
                    }
                    break;

                case 1:
                    if(node->getDown() != nullptr && node->getDown()->getDown() != nullptr)
                    {
                        if(!node->getDown()->getDown()->isVisited())
                        {
                            node->getDown()->setVisited();
                            buildMaze(node->getDown()->getDown());
                        }
                    }
                    break;

                case 2:
                    if(node->getRight() != nullptr && node->getRight()->getRight() != nullptr)
                    {
                        if(!node->getRight()->getRight()->isVisited())
                        {
                            node->getRight()->setVisited();
                            buildMaze(node->getRight()->getRight());
                        }
                    }
                    break;

                case 3:
                    if(node->getLeft() != nullptr && node->getLeft()->getLeft() != nullptr)
                    {
                        if(!node->getLeft()->getLeft()->isVisited())
                        {
                            node->getLeft()->setVisited();
                            buildMaze(node->getLeft()->getLeft());
                        }

                    }
                    break;
            }
        }
    }

}

void Maze::setEntrance(MazeObject* node)
{
    if(node->getRight())
        node->getRight()->setVisited();
}

void Maze::setExit(MazeObject* node)
{
    if(node->getLeft())
        node->getLeft()->setVisited();
}

MazeObject* Maze::getStartingPoint()
{
    return start->getRight();
}

MazeObject* Maze::getEndingPoint()
{
    return end->getLeft();
}

Maze::~Maze()
{
    while(start != nullptr)
    {
        MazeObject* current = start->getRight();
        MazeObject* t_current = start;
        
        start = start->getDown();

        while(current != nullptr)
        {
            current = current->getRight();
            delete t_current;
            t_current = current;
        }
    }
}