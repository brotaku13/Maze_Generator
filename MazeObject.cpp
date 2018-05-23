#include "MazeObject.h"

MazeObject::MazeObject()
{
    isWall = true;

    up = nullptr;
    down = nullptr;
    left = nullptr;
    right = nullptr;
    isWall = false;

    wall = "██";
    path = "  ";

    visited = false;
}
MazeObject::MazeObject(bool newWall)
{
    isWall = newWall;

    up = nullptr;
    down = nullptr;
    left = nullptr;
    right = nullptr;

    wall = "██";
    path = "  ";

    visited = false;
}
void MazeObject::draw()
{
    cout << (isWall ? wall : path);
}

void MazeObject::setSearched()
{
    searched = true;
    path = "\033[1;31m██\033[0m";
}

MazeObject::MazeObject(bool newWall, MazeObject *north, MazeObject *south, MazeObject *east, MazeObject *west)
{
    isWall = newWall;

    up = north;
    down = south;
    left = west;
    right = east;

    wall = "██";
    path = "  ";

    visited = false;
}

void MazeObject::setWall()
{
    if(!visited)
        isWall = true;
}

MazeObject* MazeObject::getUp() {return up;}
MazeObject* MazeObject::getDown() {return down;}
MazeObject* MazeObject::getLeft() {return left;}
MazeObject* MazeObject::getRight() {return right;}

void MazeObject::setDown(MazeObject* newDown) {down = newDown;}
void MazeObject::setLeft(MazeObject* newLeft) {left = newLeft;}
void MazeObject::setRight(MazeObject* newRight) {right = newRight;}
void MazeObject::setUp(MazeObject* newUp) {up = newUp;}


