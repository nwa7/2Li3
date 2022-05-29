#ifndef MAP_H
#define MAP_H
#include <vector>
#include "player.hh"
#include "bloc.hh"

class Map
{
    public:
    // Methods
    Map(int width, int height, std::vector<Bloc> data);
    void displayMap();
    Bloc operator[](int n);//ca schmoutz
    //faut faire un arbre pas une liste les bg

    int width_;
    int height_;
    std::vector<Bloc> platforms_;

    //fonction collide ou on récupère la liste des blocs avec lesquels le joueur a une collision

    BoundingBox* collide(BoundingBox box);

};





#endif
