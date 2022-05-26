#include <GL/gl.h>
#include <GL/glu.h>
#include "map.h"
#include "bloc.h"

/** Floor = (0, *) 
Lower Floor = -15**/


Map::Map(int width, int height)
    :  width_(width), height_(height), platforms_(std::vector<Bloc>())
{ // conditions s'il y en a 
    platforms_.push_back(Bloc({-30,-15}, 45,15, {155, 0,155})); 
    platforms_.push_back(Bloc({15,-15}, 5,10, {155, 0,155})); 
    platforms_.push_back(Bloc({20,-15}, 5,5, {155, 0,155})); 
    platforms_.push_back(Bloc({25,-15}, 10,1, {155, 0,155})); 
}


void Map::displayMap()
{
    for(const auto& bloc: this->platforms_)
    {
        glColor3f(bloc.color.r, bloc.color.g, bloc.color.b);
        bloc.drawBloc();
    }
}
// accès + simple aux blocs dans la map, il suffit d'écrire map[n] pour accéder au bloc n
Bloc Map::operator[](int n)
{
    return this->platforms_[n];
}