#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "map.h"
#include "geometry.h"
#include "player.h"
#include "graphics.h"


static const unsigned int WINDOW_WIDTH = 1920;
static const unsigned int WINDOW_HEIGHT = 1080;

// tests 

Vect posi = {0, 0};
Color c = {0, 150, 150};

Player p = Player(posi, 5, 5, c, 'T', posi, posi);


/* Déclaration du type tableau Vertex */
Vect tabvertex[256];
int compteur;
float aspectRatio;
Map map(WINDOW_WIDTH, WINDOW_HEIGHT);

int main(int argc, char** argv) 
{   
    initSDL();
	SDL_Window* window = initWindow(1920, 1080);
	SDL_GLContext glcontext = contextInit(window);

	// Exemple de chargement de texture
	// GLuint id = initializeTexure("lkdn.png");

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);


    onWindowResized(WINDOW_WIDTH, WINDOW_HEIGHT);
	/*** BOUCLE DE JEU ***/

    int loop = 1;
    while(loop) 
    {
        glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Dessins

		// Toute cette structure serait remplacable par un systeme plus vaste qui gererait l affichage des menus

		SDL_GL_SwapWindow(window);
        /*** SDL ***/

        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glColor3f(p.color.r, p.color.g, p.color.b);
        glPushMatrix();
            //glTranslatef(p.player.pos.x, p.player.pos.y, 0.);
            //glScalef(q.width, q.height, 1.);

        p.drawBloc(1);
        drawOrigin(p);
        glPopMatrix();
        map.displayMap();

        /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapWindow(window);
        
        
        /* EVENTS */

        SDL_Event e;
        while(SDL_PollEvent(&e)) 
        {
            /* L'utilisateur ferme la fenetre : */
           if(e.type == SDL_QUIT||e.key.keysym.sym == SDLK_q) 
            {
                loop = 0;
                break;
            }

            /* Quelques exemples de traitement d'evenements : */
            switch(e.type) 
            {
                /* Clic souris */
                case SDL_MOUSEBUTTONUP:
                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);

                /* Touche clavier */
                case SDL_KEYDOWN:
                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);
                    
                    if(e.key.keysym.sym == SDLK_LEFT) {
                        p.pos.x-=0.1;
                        printf("position joueur : x:%f y:%f\n", p.pos.x, p.pos.y);
                    }

                    else if(e.key.keysym.sym == SDLK_RIGHT) {
                        p.pos.x+=0.1;
                        printf("position joueur : x:%f y:%f\n", p.pos.x, p.pos.y);  
                    }

                    else if(e.key.keysym.sym == SDLK_SPACE) {
                        p.pos.y+=0.1;
                    }

                    break;

                default:
                    break;
            }
        }
    }
    /*** FIN DU JEU ***/


    /* Liberation des ressources associees a la SDL */
   // SDL_DestroyWindow(window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
