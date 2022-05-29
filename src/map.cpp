#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include "map.hh"
#include "bloc.hh"

/** Floor = (0, *) 
Lower Floor = -15**/


Map::Map(int width, int height, int level, std::vector<Bloc> data)
    :  width_(width), height_(height), level_(level), platforms_(data)
{}


void Map::displayMap(int time)
{
    for(auto& bloc: this->platforms_)
    {
        bloc.drawBloc(time);
    }
}
// accès + simple aux blocs dans la map, il suffit d'écrire map[n] pour accéder au bloc n
Bloc Map::operator[](int n)
{
    return this->platforms_[n];
}

BoundingBox* Map::collide(BoundingBox box){
    return nullptr;
}