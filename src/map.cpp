#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <vector>
#include "map.hh"
#include "bloc.hh"

/** Floor = (0, *) 
Lower Floor = -15**/

Map::Map(int width, int height, std::vector<Bloc> data)
    :  width_(width), height_(height), platforms_(data)
{ // conditions s'il y en a
}



void Map::displayMap()
{
    for(auto& bloc: this->platforms_)
    {
        bloc.drawBloc();
    }
}
// accès + simple aux blocs dans la map, il suffit d'écrire map[n] pour accéder au bloc n
Bloc Map::operator[](int n)
{
    return this->platforms_[n];
}

BoundingBox* Map::collide(BoundingBox box){
return nullptr; // ligne à changerS
}