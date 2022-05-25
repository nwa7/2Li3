#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>

#include "graphics.h"

// REFAIRE LES 3 PREMIERES EN UNE SEULE FONCTION POUR CACHER LE COPIER COLLER

/*
void initSDL(){
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("Error initializing : %s\n", SDL_GetError());
		exit(11);
	}
}

SDL_Window* initWindow(int width, int height){
	SDL_Window* w;

	w = SDL_CreateWindow("Rectangle and Collision", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (w==NULL){
		printf("Error creating window : %s\n", SDL_GetError());
		exit(12);
	}
	return w;
}

SDL_GLContext contextInit(SDL_Window* window){
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GLContext context = SDL_GL_CreateContext(window);

	if(context == NULL){
		printf("Error creating OpenGL context : %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		exit(16);
	}

	return context;
}

// Possibilite de mettre un rectangle en parametre pour afficher la texture directement dedans
// Sinon possibilite de mettre des coordonnees
void drawRect(GLuint texture, ...){
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
		
		// Remplir comme dans les TPs

	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

GLuint initializeTexure(std::string chemin){

	SDL_Surface* img= IMG_Load(chemin.c_str());
	if(img==NULL){
		exit(-1);
	}


	GLuint texture;


	glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);

	SDL_FreeSurface(img);


	return texture;
}
*/