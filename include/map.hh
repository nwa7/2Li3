#ifndef MAP_H
#define MAP_H
#include <vector>
#include "player.hh"
#include "bloc.hh"

class Map
{
    public:
    
    int width_;
    int height_;
    int level;
    std::vector<Bloc> platforms_;

    // Methods
    Map(int width, int height);
    void clean();

    void loadLvl(int lvl);

    void displayMap();
    Bloc operator[](int n);

    BoundingBox* collide(BoundingBox box);
};





#endif
