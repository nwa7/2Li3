#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <X11/Xlib.h>

#include "graphics.hh"
#include "lodepng.hh"
#include "fakesdlimage.hh"

Display* dis= XOpenDisplay(NULL);
Screen* scr = DefaultScreenOfDisplay(dis);
static const float GL_VIEW_SIZE = 40.;

// Fenetre
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

void headTex() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Active texturing & attache texture au point de bind
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void footTex(SDL_Window* window) {
	// Detache texture & desactive texturing
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	// Mise a jour fenetre
	SDL_GL_SwapWindow(window);
}

void fixTexScreen() {
    glBegin(GL_QUADS);
		glTexCoord2f(1.,1.);
		glVertex2f(scr->width/(GL_VIEW_SIZE*1.36),-scr->height/(GL_VIEW_SIZE*1.36));

		glTexCoord2f(0.,1.);
		glVertex2f(-scr->width/(GL_VIEW_SIZE*1.36),-scr->height/(GL_VIEW_SIZE*1.36));

		glTexCoord2f(0.,0.);
		glVertex2f(-scr->width/(GL_VIEW_SIZE*1.36),scr->height/(GL_VIEW_SIZE*1.36));
		
		glTexCoord2f(1.,0.);
		glVertex2f(scr->width/(GL_VIEW_SIZE*1.36),scr->height/(GL_VIEW_SIZE*1.36));
	glEnd();
}

void fixTexWord() {
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

/* MENUS */
void showMenuSelect(int compteur, int option, GLuint tex1, GLuint tex2) {
	// Affichage quand l'option est sélectionnée
	if(compteur==option) {
		glTranslatef(-0.6,0,0);
		glBindTexture(GL_TEXTURE_2D, tex1);
		fixTexWord();
		glTranslatef(0.6,0,0);
	}
	// Si elle n'est pas sélectionnée
	else {
		glBindTexture(GL_TEXTURE_2D, tex2);
		fixTexWord();
	}
}

void chooseMenu(SDL_Window* window, GLuint* textures, int menu, int compt) {
	headTex();
	switch(menu) {
            // Ecran menu principal
            case 0 : 
                // Fond
                glBindTexture(GL_TEXTURE_2D, textures[0]);
                fixTexScreen();

                // Start
                glTranslatef(0,3,0);
                showMenuSelect(compt, 1, textures[4], textures[3]);

                // Rules
                glTranslatef(0,-4,0);
                showMenuSelect(compt, 2, textures[6], textures[5]);

                // Credits
                glTranslatef(0,-4,0);
                showMenuSelect(compt, 3, textures[8], textures[7]);

                // Exit
                glTranslatef(0,-4,0);
                showMenuSelect(compt, 4, textures[10], textures[9]);
            break;

            // Ecran rules
            case 2 :
                glBindTexture(GL_TEXTURE_2D, textures[1]);
                fixTexScreen();
            break;

            // Ecran credits
            case 3 :
                glBindTexture(GL_TEXTURE_2D, textures[2]);
                fixTexScreen();
            break;

    }
	footTex(window);
}

void endScreen(SDL_Window* window, GLuint* textures) {
	headTex();
    glBindTexture(GL_TEXTURE_2D, textures[11]);
    fixTexScreen();
    footTex(window);
}