#include <GL/gl.h>
#include <GL/glu.h>
#include "map.hh"
#include "bloc.hh"

/** Floor = (0, *) 
Lower Floor = -15**/


Map::Map(int width, int height)
    :  width_(width), height_(height), platforms_(std::vector<Bloc>())
{ // conditions s'il y en a
    platforms_.push_back(Bloc({-30,-15}, 45,15, colors::pink,0)); 
    platforms_.push_back(Bloc({15,-15}, 5,10, colors::purple,0)); 
    platforms_.push_back(Bloc({20,-15}, 5,5, colors::orange,0)); 
    platforms_.push_back(Bloc({25,-15}, 10,1, colors::yellow,0)); 
    platforms_.push_back(Bloc({35,-15}, 10,15, colors::red,0)); 
    platforms_.push_back(Bloc({20,-15}, 5,5, colors::blue,0)); 
    platforms_.push_back(Bloc({25,-15}, 10,1, colors::green,0)); 
}


void Map::displayMap()
{
    for(const auto& bloc: this->platforms_)
    {
        bloc.drawBloc();
    }
}
// accès + simple aux blocs dans la map, il suffit d'écrire map[n] pour accéder au bloc n
Bloc Map::operator[](int n)
{
    return this->platforms_[n];
}