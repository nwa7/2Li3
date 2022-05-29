#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

// Boucle de jeu
int gameLoop(SDL_Window* window, Map* map1, Map* map2, Quadtree* qt1, Quadtree* qt2);

#endif