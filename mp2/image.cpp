#include "image.h"

void Image::flipleft()
{
    int width = (*this).width();
    int height = (*this).height();
    RGBAPixel temp = *(*this)(0,0);
    for (int x = 0;x< width/2;x++)
    {
        for (int y = 0;y<height;y++)
        {
            //RGBAPixel *left = (*this)(x,y);   
            temp =*(*this)(x,y);
            *(*this)(x,y) = *(*this)(width-x-1,y);
            *(*this)(width-x-1,y)= temp;
        }
    }
    /*
    if (width%2==1) 
    {
        for (int x= 0;x<width;x++)
        {
            temp =*(*this)(x,height/2);
            *(*this)(x,height/2) = *(*this)(width-x-1,height/2);
            *(*this)(width-x-1,height/2)=temp;
        }
    }*/
}

void Image::adjustbrightness(int r, int g, int b)
{
    int width = this->width();
    int height = this->height();
    for (int x = 0; x < width;x++)
    {
        for (int y = 0; y<height;y++)
        {
            RGBAPixel * temp = (*this)(x,y);
            
            if (temp->red+r > 255)
                temp->red = 255;
            else if (temp->red+r < 0)
                temp->red = 0;
            else
                temp->red+=r;
            
            if (temp->green+g > 255)
                temp->green = 255;
            else if (temp->green+g < 0)
                temp->green = 0;
            else
                temp->green+=g;
            
            if (temp->blue+b > 255)
                temp->blue = 255;
            else if (temp->blue+b < 0)
                temp->blue = 0;
            else
                temp->blue+=b;
        }
    }
}

void Image::invertcolors()
{
    int width = this->width();
    int height = this->height();
    for (int x = 0; x < width;x++)
    {
        for (int y = 0; y < height;y++)
        {
            RGBAPixel * temp = (*this)(x,y);

            temp->red = 255-temp->red;
            temp->green = 255-temp->green;
            temp->blue = 255-temp->blue;
        }
    }
}

