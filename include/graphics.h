#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <string>
#include <GL/glu.h>

void initSDL();

SDL_Window* initWindow(int width, int height);

SDL_GLContext contextInit(SDL_Window* window);

void onWindowResized(unsigned int width, unsigned int height);

GLuint initializeTexure(std::string chemin);

#endif