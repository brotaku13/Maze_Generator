#pragma once
#include <string>
#include <iostream>
using namespace std;

class MazeObject
{
public:
    MazeObject();
    MazeObject(bool);
    MazeObject(bool newWall, MazeObject *north, MazeObject *south, MazeObject *east, MazeObject *west);

    void draw();

    MazeObject* getUp();
    MazeObject* getDown();
    MazeObject* getLeft();
    MazeObject* getRight();

    void setUp(MazeObject *newUp);
    void setDown(MazeObject *newDown);
    void setRight(MazeObject *newRight);
    void setLeft(MazeObject *newLeft);

    bool isVisited() {return visited;}
    void setVisited() {visited = true;}

    void setSearched();
    bool isSearched() {return searched;}

    void setWall();

private:
    MazeObject *up, *down, *left, *right;

    string wall;
    string path;

    bool searched;
    
    bool visited;
    bool isWall;
};