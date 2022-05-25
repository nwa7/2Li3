#ifndef BLOC_H
#define BLOC_H

#include "color.h"
#include "vect.h"

class Bloc
{
    public:

    Bloc(Vect p, int w, int h, Color c);
    void drawBloc(int filled) const;

    Vect pos;
    int width;
    int height;
    Color color;
};



#endif
