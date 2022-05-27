#ifndef PLAYER_H
#define PLAYER_H

#include "bloc.hh"
#include "map.hh"

int const RIGHT=1;
int const LEFT=2;
int const UP=3;
int const NONE=0;


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
    void command(int direction);
    void move(double dt);
    //void move(float dt, Map map);

    int hasOrder=0;
    int hasCollision;

    char name;
    Vect acceleration;
    Vect speed;
};

#endif
