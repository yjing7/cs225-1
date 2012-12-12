// **************************************************************
// *		   
// *  quadtree.h
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

class Quadtree
{
	public:
    /**
     * Big three
     */
    Quadtree();

    Quadtree(const PNG & source, int resolution);

    Quadtree(Quadtree const & other);

    ~Quadtree();


    /**
     *  Member functions
     */
    Quadtree const & operator= (Quadtree const &other);

    void buildTree (PNG const & source, int resolution);

    RGBAPixel getPixel (int x, int y) const;

    PNG decompress() const;

    void clockwiseRotate();

    void prune(int tolerance);

    int pruneSize(int tolerance) const;

    int idealPrune(int numLeaves)const;
	
	
	private:
    
    // A simple class representing a single node of a Quadtree.
	// You may want to add to this class; in particular, it could probably
	// use a constructor or two...
	class QuadtreeNode
	{
		public:
		QuadtreeNode* nwChild;  // pointer to northwest child
		QuadtreeNode* neChild;  // pointer to northeast child
		QuadtreeNode* swChild;  // pointer to southwest child
		QuadtreeNode* seChild;  // pointer to southeast child
		RGBAPixel element;  // the pixel stored as this node's "data"
        int x;
        int y;
        int res;

        /**
         * Constructor to be called for new non-leaf QuadtreeNodes.
         */
        QuadtreeNode(int xcoord, int ycoord, int resolution)
        {
            x = xcoord;
            y = ycoord;
            res = resolution;
            nwChild = neChild = swChild = seChild = NULL;
        }

        /**
         * Constructor to be called for leaf QuadtreeNodes
         */
        QuadtreeNode(int xcoord, int ycoord, int resolution, PNG & source)
        {
            x = xcoord;
            y = ycoord;
            res = resolution;
            nwChild = neChild = swChild = seChild = NULL;
            element = *(source(x,y));
        }

        QuadtreeNode(QuadtreeNode const * other)
        {
            x = other->x;
            y = other->y;
            res = other->res;
            nwChild = neChild = swChild = seChild = NULL;
            element = other->element;
        }

	};

    void clearTree( QuadtreeNode * & subRoot);

    QuadtreeNode* copy(QuadtreeNode *otherRoot);

    void buildTreeHelper (PNG const & source, int resolution, QuadtreeNode *subRoot);

    RGBAPixel getPixelHelper(int x, int y, QuadtreeNode *subRoot) const;

    bool isInRange(int x, int y, QuadtreeNode *subRoot) const;

    void clockwiseRotate(QuadtreeNode *subRoot);

    void prune(int tolerance, QuadtreeNode * subRoot);

    int difference(QuadtreeNode * a, QuadtreeNode * b) const;
    
    int pruneSize(int tolerance, QuadtreeNode * subRoot) const;
	
	QuadtreeNode* root;    // pointer to root of quadtree

    int idealPrune(int numLeaves, int n, int interval) const;

    bool checkTol(QuadtreeNode * subRoot, QuadtreeNode * avgRoot, int avg)const;
	
	
	
	/**** Functions added for testing/grading                ****/
	/**** Do not remove this line or copy its contents here! ****/
	#include "quadtree_given.h"
};

#endif
