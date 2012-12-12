// **************************************************************
// *		   
// *  quadtree.cpp
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#include "quadtree.h"
#include <cmath>
#include <iostream>

using namespace std;

/**
 *  Big Three
 */
Quadtree::Quadtree()
{
    root = NULL;
}

Quadtree::Quadtree(const PNG & source, int resolution)
{
   // cout<<"[In constructor]..."<<endl;
    buildTree(source, resolution);
    //cout<<"[Done building a tree!]"<<endl;
}

Quadtree::Quadtree(Quadtree const & other)
{
    //cout<<"[In copy constructor]..."<<endl;
    if (other.root == NULL)
    {
        root = NULL;
        return;
    }
    root = copy(other.root);
    //cout<<"[Done copying a tree!]"<<endl;
}

Quadtree::QuadtreeNode * Quadtree::copy( QuadtreeNode *otherRoot)
{
    if (otherRoot == NULL)
    {
        return NULL;
    }
    QuadtreeNode *retVal = new QuadtreeNode::QuadtreeNode(otherRoot);
    retVal->nwChild = copy(otherRoot->nwChild);
    retVal->neChild = copy(otherRoot->neChild);
    retVal->swChild = copy(otherRoot->swChild);
    retVal->seChild = copy(otherRoot->seChild);
    return retVal;
}

Quadtree::~Quadtree()
{
    clearTree(root);
}

void Quadtree::clearTree( QuadtreeNode * & subRoot)
{
    // base case
    if ( subRoot == NULL )
        return;
    
    // recursively clear all other nodes
    clearTree(subRoot->nwChild);
    clearTree(subRoot->neChild);
    clearTree(subRoot->swChild);
    clearTree(subRoot->seChild);
    // delete the root and set it to NULL
    delete subRoot;
    subRoot = NULL;
}


/**
 *  Member Fucntion
 */
Quadtree const & Quadtree::operator= (Quadtree const &other)
{
    //check self-assignment
    if (root == other.root)
        return *this;

    //clear self
    clearTree(root);

    //copy other
    root = copy(other.root);
    return *this;
}

void Quadtree::buildTree (PNG const & source, int resolution)
{
    //first construct a tree that has enough leaves
    //  with: x, y, res

    //Then load the leaves with the correct pixels
    
    //compute and store the average color of the children of non-leave nodes on the way back up
    //cout<<"[In buildTree]..."<<endl;
    root = new QuadtreeNode(0,0,resolution);

    buildTreeHelper (source, resolution, root);
    //cout<<"[Tree built!]"<<endl;
}

void Quadtree::buildTreeHelper (PNG const & source, int resolution, QuadtreeNode *subRoot)
{
    //base case when res == 1
    //load correct pixels
    if (resolution ==1)
    {
        subRoot->element = *(source(subRoot->x,subRoot->y));
        return;
    }
    //initialize new nodes
    subRoot->nwChild = new QuadtreeNode(subRoot->x, subRoot->y, resolution/2);
    subRoot->neChild = new QuadtreeNode(subRoot->x + resolution/2, subRoot->y, resolution/2);
    subRoot->swChild = new QuadtreeNode(subRoot->x, subRoot->y + resolution/2, resolution/2);
    subRoot->seChild = new QuadtreeNode(subRoot->x + resolution/2, subRoot->y + resolution/2, resolution/2);

    //recursively build tree on children
    buildTreeHelper(source, resolution/2, subRoot->nwChild);
    buildTreeHelper(source, resolution/2, subRoot->neChild);
    buildTreeHelper(source, resolution/2, subRoot->swChild);
    buildTreeHelper(source, resolution/2, subRoot->seChild);

    //store average color
    subRoot->element.red = (subRoot->nwChild->element.red + subRoot->neChild->element.red + subRoot->swChild->element.red + subRoot->seChild->element.red)/4; 
    subRoot->element.green = (subRoot->nwChild->element.green + subRoot->neChild->element.green + subRoot->swChild->element.green + subRoot->seChild->element.green)/4; 
    subRoot->element.blue = (subRoot->nwChild->element.blue + subRoot->neChild->element.blue + subRoot->swChild->element.blue + subRoot->seChild->element.blue)/4; 
}

RGBAPixel Quadtree::getPixel (int x, int y) const
{
    return getPixelHelper(x,y,root); 
}

RGBAPixel Quadtree::getPixelHelper(int x, int y, QuadtreeNode *subRoot) const
{
    if ((subRoot->x == x && subRoot->y == y && subRoot->res == 1) || (subRoot->nwChild == NULL))
        return subRoot->element;
    if (isInRange(x,y,subRoot->nwChild))
    {
        //in nw
        return getPixelHelper(x,y,subRoot->nwChild);

    } else if (isInRange(x,y,subRoot->neChild))
    {
        //in ne
        return getPixelHelper(x,y,subRoot->neChild);

    } else if (isInRange(x,y,subRoot->swChild))
    {
        //in sw
        return getPixelHelper(x,y,subRoot->swChild);

    } else
    {
        //in se
        return getPixelHelper(x,y,subRoot->seChild);
    }
}

/**
 *  Computes whether a given (x,y) is in range of a QuadtreeNode with its left-top most index as startX and startY
 */
bool Quadtree::isInRange(int x, int y, QuadtreeNode *subRoot) const
{
    int x_range = subRoot->x+subRoot->res;
    int y_range = subRoot->y+subRoot->res;

    return (x >= subRoot->x && x< x_range)&& (y >= subRoot->y && y < y_range);
}

PNG Quadtree::decompress() const
{
    if (root == NULL)
        return *(new PNG());
    int resolution = root->res;
    PNG retVal(resolution, resolution);
    for (int i = 0; i < resolution; i++)
    {
        for (int j = 0; j < resolution; j++)
        {
            *(retVal(i,j)) = getPixel(i,j);
        }
    }
    return retVal;

}

void Quadtree::clockwiseRotate()
{
   clockwiseRotate(root); 

}

void Quadtree::clockwiseRotate(QuadtreeNode * subRoot)
{
    //base case: do nothing and return
    if (subRoot->nwChild == NULL)
        return;

    //swap the pointers to point to the correct node after rotation
    QuadtreeNode * temp = subRoot->nwChild;
    subRoot->nwChild = subRoot->swChild;
    subRoot->swChild = subRoot->seChild;
    subRoot->seChild = subRoot->neChild;
    subRoot->neChild = temp;
    
    //start assigning new x,y coordinates after the rotation
    subRoot->nwChild->x = subRoot->x;
    subRoot->nwChild->y = subRoot->y;

    subRoot->neChild->x = subRoot->x + subRoot->res/2;
    subRoot->neChild->y = subRoot->y;
    
    subRoot->swChild->x = subRoot->x;
    subRoot->swChild->y = subRoot->y + subRoot->res/2;
    
    subRoot->seChild->x = subRoot->x + subRoot->res/2;
    subRoot->seChild->y = subRoot->y + subRoot->res/2;

    //recursively call rotate on children
    clockwiseRotate(subRoot->nwChild);
    clockwiseRotate(subRoot->neChild);
    clockwiseRotate(subRoot->swChild);
    clockwiseRotate(subRoot->seChild);
    
}

void Quadtree::prune(int tolerance)
{
   prune(tolerance, root); 
}

void Quadtree::prune(int tolerance, QuadtreeNode * subRoot)
{
    if (subRoot->nwChild == NULL)
        return;
    
    if (checkTol(subRoot, subRoot, tolerance))
    {
        //prune
        clearTree(subRoot->nwChild);
        clearTree(subRoot->neChild);
        clearTree(subRoot->swChild);
        clearTree(subRoot->seChild);
        return;
    }
    //recursively call prune on children
    prune(tolerance,subRoot->nwChild);
    prune(tolerance,subRoot->neChild);
    prune(tolerance,subRoot->swChild);
    prune(tolerance,subRoot->seChild);
}

bool Quadtree::checkTol(QuadtreeNode * subRoot, QuadtreeNode * avgRoot, int tol) const
{
    if (subRoot->nwChild == NULL)
    {
        return (difference(subRoot, avgRoot)<=tol);
    }
    return  (checkTol(subRoot->nwChild, avgRoot, tol) &&
                checkTol(subRoot->neChild, avgRoot, tol) &&
                checkTol(subRoot->swChild, avgRoot, tol) &&
                checkTol(subRoot->seChild, avgRoot, tol)); 
}


int Quadtree::difference(QuadtreeNode * a, QuadtreeNode * b) const
{
    return (a->element.red-b->element.red)*(a->element.red-b->element.red)+(a->element.green-b->element.green)*(a->element.green-b->element.green)+(a->element.blue-b->element.blue)*(a->element.blue-b->element.blue);
}

int Quadtree::pruneSize(int tolerance) const
{

    return pruneSize(tolerance, root);
}

int Quadtree::pruneSize(int tolerance, QuadtreeNode * subRoot) const
{
    if (subRoot->nwChild == NULL)
        return 1;
    if (checkTol(subRoot, subRoot, tolerance))
    {
        return 1;
    }
    return pruneSize(tolerance, subRoot->nwChild) + pruneSize(tolerance, subRoot->neChild) + pruneSize(tolerance, subRoot->swChild) + pruneSize(tolerance, subRoot->seChild);
}

int Quadtree::idealPrune(int numLeaves)const
{
    //max difference is 195075
    
    return idealPrune(numLeaves, 255*255*3, 255*255*3);
    /*
    for (int i = 0; i < 255*255*3; i++)
        cout<<pruneSize(i)<<" "<<i<<endl;
    return 0;
    */
}


int Quadtree::idealPrune(int numLeaves, int n, int interval) const
{
    if (pruneSize(n) == numLeaves)
    {
        while (pruneSize(n) == numLeaves)
            n--;
        return n+1;
    }
    if (pruneSize(n) < numLeaves)
    {
        return idealPrune(numLeaves, n-interval/2, interval/2);
    }
    else
    {
        return idealPrune(numLeaves, n+interval/2, interval/2);
    }
}


