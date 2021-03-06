#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <vector>
#include "map.hh"
#include "bloc.hh"

Map::Map(int width, int height)
    :  width_(width), height_(height)
{}

void Map::displayMap(int time)
{
    for(auto& bloc: this->platforms_)
    {
        bloc.drawBloc(time);
    }
}

void Map::loadLvl(int lvl) {
    this->level_=lvl;
    if(lvl==1) {
        platforms_.push_back(Bloc({-30,-15}, 45,15, colors::green,0)); 
        platforms_.push_back(Bloc({15,-15}, 5,10, colors::purple,0)); 
        platforms_.push_back(Bloc({20,-15}, 5,5, colors::orange,0)); 
        platforms_.push_back(Bloc({25,-15}, 10,1, colors::yellow,0)); 
        platforms_.push_back(Bloc({35,-15}, 50,10, colors::blue,0)); 
        platforms_.push_back(Bloc({75,-2}, 10,3, colors::purple,1));
        platforms_.push_back(Bloc({53,-5}, 20,5, colors::orange,0));  
        platforms_.push_back(Bloc({85,-15}, 5,5, colors::yellow,0));
        platforms_.push_back(Bloc({90,-15}, 60,1, colors::green,0));  
        platforms_.push_back(Bloc({90,10}, 10,3, colors::red,0));  
        platforms_.push_back(Bloc({105,14}, 10,3, colors::green,0));  
        platforms_.push_back(Bloc({115,-12}, 15,14, colors::orange,0));  
        platforms_.push_back(Bloc({130,-12}, 18,2, colors::orange,0));
        platforms_.push_back(Bloc({148,-14}, 2,4, colors::orange,0));
        platforms_.push_back(Bloc({150,-15}, 7,17, colors::blue,0));
        platforms_.push_back(Bloc({157,-15}, 7,20, colors::red,0));
        platforms_.push_back(Bloc({164,-15}, 7,23, colors::blue,0));
        platforms_.push_back(Bloc({171,-15}, 4,26, colors::purple,0));
        platforms_.push_back(Bloc({174,11}, 1,5, colors::orange,0));
    }
    else if(lvl==2) {
        platforms_.push_back(Bloc({-30,-15}, 45,15, colors::blue,0)); 
        platforms_.push_back(Bloc({15,-15}, 5,10, colors::orange,0)); 
        platforms_.push_back(Bloc({20,-15}, 5,5, colors::purple,0)); 
        platforms_.push_back(Bloc({25,-15}, 10,1, colors::yellow,0)); 
        platforms_.push_back(Bloc({35,-15}, 50,10, colors::blue,0)); 
        platforms_.push_back(Bloc({53,-5}, 20,5, colors::orange,0));  
        platforms_.push_back(Bloc({85,-15}, 5,5, colors::yellow,0));
        platforms_.push_back(Bloc({90,-15}, 60,1, colors::green,0));  
        platforms_.push_back(Bloc({90,10}, 10,3, colors::red,0));
    }
}

// map[n] : bloc n
Bloc Map::operator[](int n) {
    return this->platforms_[n];
}

BoundingBox* Map::collide(BoundingBox box){
    return nullptr; // ligne ?? changerS
}