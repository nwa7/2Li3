#ifndef QUADTREE_H
#define QUADTREE_H

#include "bloc.hh"
#include "player.hh"

class Quadtree{
    
    public :

    int xmin, xmax, ymin, ymax;

    Bloc* platforms[5];
    int ind=0;

    Quadtree* upleft;
    Quadtree* downleft;
    Quadtree* upright;
    Quadtree* downright;

    // constructeur
    //Quadtree(Player p);

    void generate(Bloc* map);
    void split();
    //Bloc* searchLeaf(float x, float y);
    int searchLeaf(Bloc* obj);
    void insertBloc(Bloc* obj);
    Bloc* collision(Bloc* returnObjets[], Bloc* bloc);

};

#endif