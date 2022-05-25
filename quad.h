#ifndef QUAD_H
#define QUAD_H
#include "geometry.h"

// Utilisable pour afficher des textures par exemple
// Utilisable comme plateformes

/**
    float x;
    float y;
    float sizeX;
    float sizeY;

    // Methods

    //lit les donnees
    float getPosX();
    float getPosY();
    float getSizeX();
    float getSizeY();

    //definir les donnees
    void setX(float x);
    void setY(float y);

} Vect;
**/

// Classes
class Quad
{
    public:

    Quad(Vect p, int w, int h, Color c)
        : pos(p), width(w), height(h), color(c)
    {}
 
    Vect pos;
    int width;
    int height;
    Color color;
};


#endif
