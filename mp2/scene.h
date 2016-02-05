#ifndef SCENE_H
#define SCENE_H

#include "image.h"

class Scene {

public: 

// Constructor & Destructor 
Scene(int max);
~Scene();
Scene(const Scene &source);

// Member Function
const Scene & operator = (const Scene &source);
void changemaxlayers (int newmax);
void addpicture (const char *FileName, int index, int x, int y);
void changelayer (int index, int newindex);
void translate (int index, int xcoord, int ycoord);
void deletepicture (int index);
Image * getpicture (int index) const;
Image drawscene () const;

void clear();
void copy(const Scene &source);

Image ** collection;
int * xCoord;
int * yCoord;
int length;

};

#endif
