#ifndef BLOC_H
#define BLOC_H

#include "color.hh"
#include "vect.hh"

class Bloc
{
    public:

    Bloc(Vect p, int w, int h, Color c, int animated);
    void drawBloc(int time);

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

int const NOCOLLISION = 0; 
int const COLLISION= 16;

/*int const COLLISIONLEFT = 1;
int const COLLISIONRIGHT = 2;
int const COLLISIONUP = 4;
int const COLLISIONDOWN = 8;*/


class BoundingBox
{
    public:

    Vect upperLeft;
    Vect downRight;

    int collide(BoundingBox other);

};

//dans la map il faut aussi une fonction collide pour pouvoir verifier que y a bien collision

#endif
