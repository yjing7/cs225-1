#include "scene.h"
#include "image.h"
#include <iostream>
using namespace std;



//Constructor
Scene::Scene (int m)
{
   max = m;
   layers = new Image *[max];
   ycoords = new int[max];
   xcoords = new int[max];
   for (int i = 0; i < m; i++)
    { 
       layers[i] = NULL;
       ycoords[i] = 0;
       xcoords[i] = 0;
    }
}

//Destructor
Scene::~Scene()
{
    _clear();
}

//Copy constructor
Scene::Scene(const Scene &source)
{
    _copy(source);
}

//assignment operator
const Scene & Scene::operator=(const Scene &source)
{
    if (this != &source) {
        _clear();
        _copy(source);
    }
    return *this;
}

//modify size of image without changing their indices
void Scene::changemaxlayers(int newmax)
{
    //first check if there is non-null pointer outside newmax-1
    if (newmax < max)
    {
        for (int i = newmax; i < max; i++)
        {
            if (layers[i] == NULL)
            {
                cout<< "invalid new max" << endl;
                return;
            }
        }
    }

    //allocate arrays of size newmax
    Image **nlayers = new Image *[newmax];
    int *nxcoords = new int[newmax];
    int *nycoords = new int[newmax];

    //initialize all elements
    for (int i =0;i<newmax;i++)
    {
        nlayers[i] = NULL;
        nxcoords[i] = 0;
        nycoords[i] = 0;
    }

    //copy all values through newmax or max, whatever's smaller
    int smaller = (newmax<max)?newmax:max;

    for (int i = 0; i< smaller;i++)
    {
        *nlayers[i] = *layers[i];
        nxcoords[i] = xcoords[i];
        nycoords[i] = ycoords[i];

    }

    //clean old memory
    _clear();

    //now point the orig arrays to new arrays
    layers = nlayers;
    xcoords = nxcoords;
    ycoords = nycoords;

}

//add a picture to scene
void Scene::addpicture(const char *FileName, int index, int x, int y)
{
    //check if index in range
    if (index < max && index >=0)
    {
        //create new image
        Image *image = new Image();
        image->readFromFile(FileName);

        if (layers[index] != NULL)
            delete layers[index];
        
        //place in layers[index]
        layers[index] = image;
        
        //store x,y coords
        xcoords[index] = x;
        ycoords[index] = y;
    } 
    else
        cout<< "index out of bounds" << endl;
}

//Move image from one layer to another
void Scene::changelayer (int index, int newindex)
{   
    //check bound
    if((index >=0 && index < max)&&(newindex >=0 && newindex <max))
    {
        //check self-assignment
        if (index == newindex)
            return;
        // delete the image originally there
        if(layers[newindex]!=NULL)
            delete layers[newindex];
        // have newindex pointer to original image
        layers[newindex] = layers[index];
        layers[index] = NULL;

        //update x,y coords
        xcoords[newindex] = xcoords[index];
        ycoords[newindex] = ycoords[index];
        xcoords[index] = 0;
        ycoords[index] = 0;
    } else
        cout <<"invalid index" <<endl;   
}

//change x, y coord of Image in specified layer
void Scene::translate(int index, int xcoord, int ycoord)
{
    //check null
    if ((index>=0&&index<max)&&(layers[index]!=NULL))
    {
    //change x,y coords
        xcoords[index] = xcoord;
        ycoords[index] = ycoord;
    } else
        cout<<"invalid index" <<endl;
}

//delete image at given index
void Scene::deletepicture(int index)
{
    //check null
    if ((index>=0&&index<max)&&(layers[index]!=NULL))
    {
        //delete image
        delete layers[index];
        layers[index] = NULL;
        xcoords[index] = 0;
        ycoords[index] = 0;
    }
    else
        cout <<"invalid index"<<endl;

}

//return pointer to Image at specified index
Image * Scene::getpicture(int index) const
{

    //check null and index inbound
    if ((index < max) && (index >=0))
    {
        return layers[index];
    }
    else
    {   
        cout<<"invalid index"<<endl;
        return NULL;
    }
}

//draw the scene and return the Image by value
Image Scene::drawscene() const
{
    //determine min height and width
    int min_height = 0;
    int min_width = 0;
    for(int i = 0; i < max; i++)
    {
        if(layers[i] != NULL)
        {
            cout << "Layer number: "<< i << endl;
            if(min_height < (layers[i]->height()+ycoords[i]))
                min_height = layers[i]->height()+ycoords[i];
            if(min_width < (layers[i]->width()+xcoords[i]))
                min_width = layers[i]->width()+xcoords[i];
        }
    }
    //declare an Image with the min height and width
    Image image;
    image.resize(min_width,min_height);
    
    
    //loop through the layers from 0 to max-1
    for(int index = 0; index < max;index++)
    {
        if (layers[index] != NULL)
        {
            for(int x = 0; x < layers[index]->width(); x++)
            {
                for(int y = 0; y< layers[index]->height();y++)
                {
                   *image(xcoords[index]+x,ycoords[index]+y) = *(*layers[index])(x,y);
                }
            }
        }
    }
    
    return image;
}

void Scene::_copy(const Scene & other)
{
    max = other.max;
    layers = new Image *[max];
    xcoords = new int[max];
    ycoords = new int[max];
    for (int i = 0;i < max; i++)
    {
        if (other.layers[i] != NULL) {
            layers[i] = new Image(*(other.layers[i]));
        }
        else
            layers[i] = NULL;
            
        xcoords[i] = other.xcoords[i];
        ycoords[i] = other.ycoords[i];
    }
}

void Scene::_clear()
{
    for (int i=0;i<max;i++)
    {
        delete layers[i];
    }
    delete [] layers;
    delete [] xcoords;
    delete [] ycoords;
}
