#ifndef BLOC_H
#define BLOC_H

#include "color.hh"
#include "vect.hh"

class Bloc
{
    public:

    Bloc(Vect p, int w, int h, Color c, int animated);
    void drawBloc() const;

    void setX(float x);
    void setY(float y);
    float getPosX();
    float getPosY();
    float getWidth();
    float getHeight();
    

    Vect pos;
    int width;
    int height;
    Color color;
    int animated;
};



#endif
