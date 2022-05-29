#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include "bloc.hh"

class Quadtree {
    
    public :

    // Variables
    int xmin, xmax, ymin, ymax;

    std::vector<Bloc> blocs;

    Quadtree* upleft = nullptr;
    Quadtree* downleft = nullptr;
    Quadtree* upright = nullptr;
    Quadtree* downright = nullptr;

    // Methodes

    Quadtree(int xmin, int xmax, int ymin, int ymax);
    void generate(Bloc* map);

    int getX();
    int getY();
    bool isLeaf();
    bool isFull();

    void split();
    int searchLeaf(Bloc* obj);
    void insertBloc(Bloc obj);

    std::vector<Bloc> searchBloc(Bloc* obj);

};

#endif