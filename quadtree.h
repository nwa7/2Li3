#ifndef QUADTREE_H
#define QUADTREE_H

#include "quad.h"

typedef struct Quadtree{
    
    Quad* platforms;

    int xmin, xmax, ymin, ymax;

    Quadtree* upleft;
    Quadtree* downleft;
    Quadtree* upright;
    Quadtree* downright;

    // Method

    void generate(Quad* map);
    Quad* searchLeaf(float x, float y);

} Quadtree;

#endif