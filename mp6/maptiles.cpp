/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */
	 			
#include <iostream>
#include <map>
#include "maptiles.h"
#include "kdtree.h"

using namespace std;

MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
    //Build a kdtree with a vector of Point<3> representing the colors

    //Convert vector<TileImage> to vector< Point<3> >
    vector< Point<3> > colors;
    vector< TileImage >::iterator it;
    
    //Build a map between average color and the tile that would generate the average color
    map<Point<3>, TileImage> theMap;
    
    //Loop through the tiles
    //for (it = theTiles.begin(); it != theTiles.end(); it++)
    for (int i = 0; i < theTiles.size(); i++)
    {
        //get average color
        RGBAPixel pi = theTiles.at(i).getAverageColor();
        Point<3> po(pi.red, pi.green, pi.blue);
        
        //map it
        theMap[po] = theTiles.at(i);
        
        //put in vector
        colors.push_back(po);
    }

    //Call kdtree constructor
    KDTree<3>::KDTree tree(colors);

    //Start building the canvas
    //Declare a new canvas
    int r = theSource.getRows();
    int c = theSource.getColumns();
    MosaicCanvas::MosaicCanvas *canvas = new MosaicCanvas(r, c);

    //loop through each tile
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            //for each tile: 
            //grab the pixel from source
            RGBAPixel regionColor = theSource.getRegionColor(i, j); 
            //find the closest average color from kdtree using NNS
            Point<3> regionPoint(regionColor.red, regionColor.green, regionColor.blue);
            Point<3> closestPoint = tree.findNearestNeighbor(regionPoint);
            //use the map to find the tile 
            TileImage theTile = theMap[closestPoint];

            //put the tile onto canvas
            canvas->setTile(i,j,theTile);
        }
    }

    //return canvas
    return canvas;
}
