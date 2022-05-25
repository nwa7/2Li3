#ifndef MAP_H
#define MAP_H

#include "player.h"

class Map
{
    public:
    // Methods
    Map(int id, int width, int height, Bloc* platforms, Player* players)
    	: id_(id), width_(width), height_(height), platforms_(platforms), players_(players)
    	{ // conditions s'il y en a 
        }
	
    int id_;
    int width_;
    int height_;
    Bloc * platforms_;
    Player * players_;
    
};



#endif
