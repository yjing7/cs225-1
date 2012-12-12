#ifndef SCENE_H
#define SCENE_H

#include "image.h"
#include "png.h"

class Scene
{
    public:
        //Initialize this Scene object to be ablet o hold "max" number of images with indices 0 through max-1
        Scene(int max);

        /*
         * Frees all space that was dynamically allocated by this Scene
         */
        ~Scene();

        /*
         * The copy constructor make this Scene an independent copy of the
         * source
         */
        Scene(const Scene & source);
        
        /*
         * assignment operator for the Scene class
         */ 
        const Scene & operator= (const Scene &source);

        /*
         * Modifies the size of the array of Image pointers without changing 
         * their indices
         */ 
        void changemaxlayers(int newmax);
        
        /*
         * This function will add a picture to the scene, by placing it in the 
         * array cell corresponding to the fiven index, and sotring its x
         * coordinate and y coordinte
         */ 
        void addpicture (const char *FileName, int index, int x, int y);
        
        /*
         * Moves and Image from one layer to another
         */ 
        void changelayer (int index, int newindex);
        
        /* Changes the x and y coordinate fo the Image in the specified layer
         */
        void translate(int index, int xcoord, int ycoord);
        
        /* Deletes the mage at the given index
         */
        void deletepicture(int index);
        
        /* return a pointer to the Image at the specified index, not a copy of 
         * it
         */
        Image * getpicture ( int index) const;
        
        /* draws the whole scene on one Image and returns that Image by value
         */
        Image drawscene() const;
        
        private:

        int max;
        Image ** layers; 
        int * xcoords;
        int * ycoords;
        void _copy(const Scene & other);
        void _clear();
};

#endif //SCENE_H
