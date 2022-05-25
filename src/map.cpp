#include "map.h"
#include "bloc.h"


Map::Map(int width, int height)
    :  width_(width), height_(height), platforms_(std::vector<Bloc>())
{ // conditions s'il y en a 
    platforms_.push_back(Bloc({-5,0}, 5,8, {155, 0,155})); 
}

void Map::displayMap()
{
    for(const auto& bloc: this->platforms_)
    {
        bloc.drawBloc(1);
    }
}