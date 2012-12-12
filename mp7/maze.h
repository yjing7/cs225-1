#ifndef MAZE_H
#define MAZE_H

#include "dsets.h"
#include <iostream>
#include "png.h"
#include <map>
#include <queue>
#include <stack>
using namespace std;

class SquareMaze {

    public:
    SquareMaze();
    void makeMaze(int width, int height);
    bool canTravel(int x, int y, int dir) const;
    void setWall (int x, int y, int dir, bool exist);
    vector <int> solveMaze();
    PNG * drawMaze() const;
    PNG * drawMazeWithSolution();


    private:
    int mazeWidth;
    int mazeHeight;
    int size;
    int exitCell;
    vector <int> solution;
    DisjointSets cells;
    vector< pair< pair<int, int>, int > >  walls;
    vector<bool> rightWalls;
    vector<bool> bottomWalls;

    int getCellIndex(int x, int y) const;
    int getCellX( int cellID);
    int getCellY( int cellID);
    int getNextCell( int x, int y, int dir );

};

#endif
