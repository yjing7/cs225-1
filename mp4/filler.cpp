/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. Heavily based on
 * old MP4 by CS225 Staff, Fall 2010.
 * 
 * @author Chase Geigle
 * @date Fall 2012
 */
#include "filler.h"

animation filler::dfs::fillSolid( PNG & img, int x, int y, 
        RGBAPixel fillColor, int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to fill with the correct colorPicker parameter.
     */
    solidColorPicker solid(fillColor);
    
    return filler::fill<Stack>(img, x, y, solid, tolerance, frameFreq);
}

animation filler::dfs::fillGrid( PNG & img, int x, int y, 
        RGBAPixel gridColor, int gridSpacing, int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to fill with the correct colorPicker parameter.
     */
    gridColorPicker fillColor(gridColor, gridSpacing);
    return filler::fill<Stack>(img, x, y, fillColor, tolerance, frameFreq);
}

animation filler::dfs::fillGradient( PNG & img, int x, int y, 
        RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, 
        int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to fill with the correct colorPicker parameter.
     */
    gradientColorPicker fillColor(fadeColor1, fadeColor2, radius, x, y);
    return filler::fill<Stack>(img, x, y, fillColor, tolerance, frameFreq);
}

animation filler::dfs::fill( PNG & img, int x, int y, 
        colorPicker & fillColor, int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to filler::fill with the correct template parameter
     *  indicating the ordering structure to be used in the fill.
     */
    animation anim = filler::fill<Stack>(img, x, y, fillColor, tolerance, frameFreq);
    return anim;
}

animation filler::bfs::fillSolid( PNG & img, int x, int y, 
        RGBAPixel fillColor, int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to fill with the correct colorPicker parameter.
     */
    solidColorPicker solid(fillColor);
    return filler::fill<Queue>(img, x, y, solid, tolerance, frameFreq);
}

animation filler::bfs::fillGrid( PNG & img, int x, int y, 
        RGBAPixel gridColor, int gridSpacing, int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to fill with the correct colorPicker parameter.
     */
    gridColorPicker fillColor(gridColor, gridSpacing);
    return filler::fill<Queue>(img, x, y, fillColor, tolerance, frameFreq);
}

animation filler::bfs::fillGradient( PNG & img, int x, int y, 
        RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, 
        int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to fill with the correct colorPicker parameter.
     */
    gradientColorPicker fillColor(fadeColor1, fadeColor2, radius, x, y);
    return filler::fill<Queue>(img, x, y, fillColor, tolerance, frameFreq);
}

animation filler::bfs::fill( PNG & img, int x, int y, 
        colorPicker & fillColor, int tolerance, int frameFreq ) {
    /**
     * @todo Your code here! You should replace the following line with a
     *  correct call to filler::fill with the correct template parameter
     *  indicating the ordering structure to be used in the fill.
     */
    animation anim = filler::fill<Queue>(img, x, y, fillColor, tolerance, frameFreq);
    return anim;
}

template <template <class T> class OrderingStructure>
animation filler::fill( PNG & img, int x, int y,
        colorPicker & fillColor, int tolerance, int frameFreq ) {
    /**
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a Queue, for a depth-first-search, that
     * structure is a Stack. To begin the algorithm, you simply place the
     * given point in the ordering structure. Then, until the structure is
     * empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure. 
     *
     *        If it has not been processed before and if its color is
     *        within the tolerance distance (up to and **including**
     *        tolerance away in square-RGB-space-distance) to the original
     *        point's pixel color [that is, \f$(currentRed - OriginalRed)^2 +
              (currentGreen - OriginalGreen)^2 + (currentBlue -
              OriginalBlue)^2 \leq tolerance\f$], then: 
     *        1.    indicate somehow that it has been processed (do not mark it
     *              "processed" anywhere else in your code) 
     *        2.    change its color in the image using the appropriate
     *              colorPicker
     *        3.    add all of its neighbors to the ordering structure, and 
     *        4.    if it is the appropriate frame, send the current PNG to the
     *              animation (as described below).
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore neighboring
     *        pixels in some order.
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! The order you should put
     *        neighboring pixels **ONTO** the queue or stack is as follows:
     *        **RIGHT(+x), DOWN(+y), LEFT(-x), UP(-y). IMPORTANT NOTE: *UP*
     *        here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction.** To reiterate, when you are exploring (filling out)
     *        from a given pixel, you must first try to fill the pixel to
     *        it's RIGHT, then the one DOWN from it, then to the LEFT and
     *        finally UP. If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq. 
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     */
    OrderingStructure<RGBAPixel> pixels;
    OrderingStructure<int> xcoords;
    OrderingStructure<int> ycoords;
    int processed[img.width()][img.height()];
    for (int i = 0; i < img.width(); i++) 
    {
        for (int j = 0; j <img.height(); j++)
        {
            processed[i][j] = false;
        }
    }
    animation myAnim;
    int frameCount = 0;

    RGBAPixel origPixel = *(img(x,y));
    int origRed = origPixel.red;
    int origGreen = origPixel.green;
    int origBlue = origPixel.blue;
    
    /*
    cout<<"[Original]: "<<endl;
    cout<<"     R: "<<origRed<<endl;
    cout<<"     G: "<<origGreen<<endl;
    cout<<"     B: "<<origBlue<<endl;
    cout<<"----------------"<<endl;
    */

    //add first point
    pixels.add(*img(x,y));
    xcoords.add(x);
    ycoords.add(y);

    while (!pixels.isEmpty())
    {
        //remove one point in the structure
        RGBAPixel currPixel = pixels.remove();

        int currRed = currPixel.red;
        int currGreen = currPixel.green;
        int currBlue = currPixel.blue;
        int currX = xcoords.remove();
        int currY = ycoords.remove();

        /*
        cout<<"[Current]  :"<<endl;
        cout<<"|  (x,y)   |"<<"("<<currX<<","<<currY<<")"<<endl;
        cout<<"| processed|"<<processed[currX][currY]<<endl;
        cout<<"============"<<endl;
        */

        //compute min
        int min = pow(origRed-currRed,2)+pow(origGreen-currGreen,2)+pow(origBlue-currBlue,2);

        //compute if min is within tolerance
        bool inTolDis = min <= tolerance;

        //process a currPixel if it's not processed yet and it's within tolerance 
        if (inTolDis && !processed[currX][currY])
        {
            //mark it processed
            processed[currX][currY] = true;
            frameCount++;

            //change color
            *(img(currX,currY)) = fillColor(currX,currY); 

            /*
            cout<<currX<<endl;
            cout<<currY<<endl;

            cout<<"___"<<endl;
            */
            //add neighbors to structure
            if (currX+1 <img.width())
            {
            //RIGHT
            pixels.add(*(img(currX+1,currY)));
            xcoords.add(currX+1);
            ycoords.add(currY);
            }
            
            if (currY+1 <img.height())
            {
            //DOWN
            pixels.add(*(img(currX,currY+1)));
            xcoords.add(currX);
            ycoords.add(currY+1);
            }

            if (currX-1>= 0)
            {
            //LEFT
            pixels.add(*(img(currX-1,currY)));
            xcoords.add(currX-1);
            ycoords.add(currY);
            }

            if (currY-1>= 0)
            {
            //DOWN
            pixels.add(*(img(currX,currY-1)));
            xcoords.add(currX);
            ycoords.add(currY-1);
            }
            

            //add frame to animation if frame count is divisible by framefreq
            if (frameCount % frameFreq == 0)
            {
                //add the current image to the animation
                myAnim.addFrame(img);
            }
       } 
    }
    return myAnim;
}
