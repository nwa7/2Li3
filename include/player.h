#ifndef PLAYER_H
#define PLAYER_H

#include "bloc.h"


class Player : public Bloc
{
    public:
    Player(Vect pos, int width, int height, Color color, char c, Vect a, Vect s)
        : Bloc::Bloc(pos, width, height, color), name(c), acceleration(a), speed(s)
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
