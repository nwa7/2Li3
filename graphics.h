#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <string>

void initSDL();

SDL_Window* initWindow(int width, int height);

SDL_GLContext contextInit(SDL_Window* window);

GLuint initializeTexure(std::string chemin);

#endif