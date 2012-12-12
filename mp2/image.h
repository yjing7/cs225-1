#ifndef IMAGE_H
#define IMAGE_H 

#include "png.h"

class Image : public PNG
{
    public:
    /*
     * flips the image to the left with respect to central y-axis
     */
    void flipleft();

    /*
     * adds to the red, blue, green part of the image
     */
    void adjustbrightness(int r, int g, int b);
    
    /* Make RGB of each pixel equal to 255 minus original value
     */
    void invertcolors();
};

#endif
