#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <string>
#include <GL/glu.h>


SDL_GLContext initGraphics(SDL_Window* window);

void onWindowResized(unsigned int width, unsigned int height);

GLuint initTex(std::string chemin);

void fixeTexMot();

void fixeTexEcran();

void affichageMenu(int compteur, int option, GLuint tex1, GLuint tex2);

#endif