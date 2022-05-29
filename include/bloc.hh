#ifndef BLOC_H
#define BLOC_H

#include "color.hh"
#include "vect.hh"

// Collision définit le type de collision et les éventuelles valeurs aux murs
// par exemple, si result == CÔLLISIONLEFT, xmin représente la valeur mini de la collision
// collision.result est un binaire, car on peut avoir des collisions simultanées (par exemple droite et bas en même temps)
struct Collision{
    int result;
    float xmin, xmax, ymin, ymax;
};


class BoundingBox
{
    public:

    Vect upperLeft;
    Vect downRight;

    BoundingBox(Vect upperLeft, Vect downRight);

    int collide(BoundingBox other, float offsetx, float offsety);
    
    // Retourne la position des différentes collisions
    Collision collision_side(BoundingBox other, float offsetx, float offsety);


};

class Bloc
{
    public:

    Bloc(Vect p, int w, int h, Color c, int animated);
    void drawBloc();

    void setX(float x);
    void setY(float y);
    float getPosX();
    float getPosY();
    float getWidth();
    float getHeight();

    BoundingBox getBoundingBox();
    

    Vect pos;
    Vect initial_pos;
    int width;
    int height;
    Color color;
    int animated;
};

int const NOCOLLISION = 0; 
int const COLLISION= 16;

int const COLLISIONLEFT = 1;
int const COLLISIONRIGHT = 2;
int const COLLISIONUP = 4;
int const COLLISIONDOWN = 8;







//dans la map il faut aussi une fonction collide pour pouvoir verifier que y a bien collision

#endif