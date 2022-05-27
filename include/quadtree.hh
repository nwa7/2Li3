#ifndef QUADTREE_H
#define QUADTREE_H

#include "bloc.hh"

typedef struct Quadtree{
    
    Bloc* platforms;

    int xmin, xmax, ymin, ymax;

    Quadtree* upleft;
    Quadtree* downleft;
    Quadtree* upright;
    Quadtree* downright;

    // Method

    void generate(Bloc* map);
    Bloc* searchLeaf(float x, float y);

} Quadtree;

#endif