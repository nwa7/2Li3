#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "graphics.hh"
#include "lodepng.hh"
#include "fakesdlimage.hh"


SDL_GLContext initGraphics(SDL_Window* window) {

	if (window==NULL){
		printf("Error creating window : %s\n", SDL_GetError());
		exit(12);
	}

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

static const float GL_VIEW_SIZE = 40.;

void onWindowResized(unsigned int width, unsigned int height)
{ 
    float aspectRatio = width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if( aspectRatio > 1) 
    {
        gluOrtho2D(
        -GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio, 
        -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
    }
    else
    {
        gluOrtho2D(
        -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
        -GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio);
    }
}

void fixeTexEcran() {
    glBegin(GL_QUADS);
		glTexCoord2f(1.,1.);
		glVertex2f(32,-20);

		glTexCoord2f(0.,1.);
		glVertex2f(-32,-20);

		glTexCoord2f(0.,0.);
		glVertex2f(-32,20);
		
		glTexCoord2f(1.,0.);
		glVertex2f(32,20);
	glEnd();
}

void fixeTexMot() {
    glBegin(GL_QUADS);
            glTexCoord2f(1.,1.);
            glVertex2f(5,-1.9);

            glTexCoord2f(0.,1.);
            glVertex2f(-5,-1.9);

            glTexCoord2f(0.,0.);
            glVertex2f(-5,1.9);
            
            glTexCoord2f(1.,0.);
            glVertex2f(5,1.9);
        glEnd();
}

void affichageMenu(int compteur, int option, GLuint tex1, GLuint tex2) {
	// Affichage quand l'option est sélectionnée
	if(compteur==option) {
		glTranslatef(-0.6,0,0);
		glBindTexture(GL_TEXTURE_2D, tex1);
		fixeTexMot();
		glTranslatef(0.6,0,0);
	}
	// Si elle n'est pas sélectionnée
	else {
		glBindTexture(GL_TEXTURE_2D, tex2);
		fixeTexMot();
	}
}

GLuint initTex(std::string chemin){

	// Chargement de l'image
	SDL_Surface* img= IMG_Load(chemin.c_str());
	if(img==NULL){
		exit(-1);
	}

	// Initialisation texture
	GLuint texture;
	glGenTextures(1,&texture);

	// Fixation texture
    glBindTexture(GL_TEXTURE_2D,texture);

	// Modifs texture
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	// Envoi données sur GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);

	// Libération
	SDL_FreeSurface(img);


	return texture;
}