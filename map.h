#ifndef MAP_H
#define MAP_H

#include "player.h"

class Map
{
    public:
    // Methods
    Map(int id, int width, int height, Quad* platforms, Player* players)
    	: id_(id), width_(width), height_(height), platforms_(platforms), players_(players)
    	{ // conditions s'il y en a 
        }
    	
    
    private:
	
    int id_;
    int width_;
    int height_;
    Quad * platforms_;
    Player * players_;
    
};



#endif
