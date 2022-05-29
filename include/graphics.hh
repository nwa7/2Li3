#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <string>
#include <GL/glu.h>

// Fenetre
SDL_GLContext initGraphics(SDL_Window* window);

void onWindowResized(unsigned int width, unsigned int height);

// Textures
GLuint initTex(std::string chemin);

void headTex();
void footTex(SDL_Window* window);

void fixTexWord();
void fixTexScreen();

void showMenuSelect(int compteur, int option, GLuint tex1, GLuint tex2);
void chooseMenu(SDL_Window* window, GLuint* textures, int menu, int compt);

void endScreen(SDL_Window* window, GLuint* textures);

#endif