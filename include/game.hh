#ifndef GAME_H
#define GAME_H
#include "map.hh"

#include <SDL2/SDL.h>

// Boucle de jeu
int gameLoop(SDL_Window* window, Map* map, int &niveau);

#endif