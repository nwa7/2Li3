#ifndef PLAYER_H
#define PLAYER_H

#include "bloc.hh"


class Player : public Bloc
{
    public:
    Player(Vect pos, int width, int height, Color color, int an, char c, Vect a, Vect s)
        : Bloc::Bloc(pos, width, height, color, an), name(c), acceleration(a), speed(s)
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
