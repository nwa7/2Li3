#ifndef MAP_H
#define MAP_H
#include <vector>
// #include "player.hh"
#include "bloc.hh"

class Map
{
    public:

    int width_;
    int height_;
    int level_;
    std::vector<Bloc> platforms_;
    
    // Methods
    Map(int width, int height);
    void loadLvl(int lvl);

    void displayMap(int time);
    Bloc operator[](int n);
    
    BoundingBox* collide(BoundingBox box);

};

#endif
