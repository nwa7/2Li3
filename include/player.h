#ifndef PLAYER_H
#define PLAYER_H

#include "quad.h"


class Player : public Quad
{
    public:
    Player(Vect pos, int width, int height, Color color, char c, Vect a, Vect s)
        : Quad::Quad(pos, width, height, color), name(c), acceleration(a), speed(s)
    {}

    /*** Methods 

    void setAccX(float x);
    void moveAndCollide();
    int collision(Rectangle);
***/

    char name;
    Vect acceleration;
    Vect speed;
};

#endif
