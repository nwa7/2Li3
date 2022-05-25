#ifndef QUAD_H
#define QUAD_H

#include "color.h"
#include "vect.h"

class Quad
{
    public:

    Quad(Vect p, int w, int h, Color c);
 
    Vect pos;
    int width;
    int height;
    Color color;
};

#endif
