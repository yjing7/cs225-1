/**
 * @file testsquaremaze.cpp
 * Performs basic tests of SquareMaze.
 * @date April 2007
 * @author Jonathan Ray
 */

#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "png.h"


#define TEST 50
#define RIGHT 0
#define BOTTOM 1


int main()
{ 
   SquareMaze m;
   m.makeMaze(TEST,TEST);
   std::cout << "MakeMaze complete" << std::endl;

    /*
    for ( int i = 0; i < TEST; i++)
    {
        for ( int j = 0; j < TEST ; j++)
        {
            cout <<"RIGHT: "<< m.canTravel(i,j,RIGHT)<< " x: "<<i<<" y: "<<j<<endl;
            cout <<"BOTTOM: "<< m.canTravel(i,j,BOTTOM)<< " x: "<<i<<" y: "<<j<<endl;
        }
    }
    */

   PNG* unsolved = m.drawMaze();
   unsolved->writeToFile("unsolved.png");
   delete unsolved;
   std::cout << "drawMaze complete" << std::endl;
   
   vector<int> sol = m.solveMaze();
   std::cout << "solveMaze complete" << std::endl;
   
   PNG* solved = m.drawMazeWithSolution();
   solved->writeToFile("solved.png");
   delete solved;
   std::cout << "drawMazeWithSolution complete" << std::endl;

   return 0;
}

