#pragma once
#include <stdlib.h> 
#include "MazeObject.h"
using namespace std;

class Maze
{
public:
    Maze();
    Maze(int, int);
    void print() const;

    void buildMaze();
    void buildMaze(MazeObject*);

    void setEntrance(MazeObject*);
    void setExit(MazeObject*);

    MazeObject* getStartingPoint();
    MazeObject* getEndingPoint();

    ~Maze();

private:
    MazeObject* start;
    MazeObject* end;
};