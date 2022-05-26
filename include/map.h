#ifndef MAP_H
#define MAP_H
#include <vector>
#include "player.h"
#include "bloc.h"

class Map
{
    public:
    // Methods
    Map(int width, int height);
    void displayMap();
    Bloc operator[](int n);

    int width_;
    int height_;
    std::vector<Bloc> platforms_;

};



#endif
