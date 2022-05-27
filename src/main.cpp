#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "map.hh"
#include "geometry.hh"
#include "player.hh"
#include "graphics.hh"


static const unsigned int WINDOW_WIDTH = 1920;
static const unsigned int WINDOW_HEIGHT = 1080;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000/15;

// tests 

Vect posi = {0, 0};

Color c = colors::blue;

Player p = Player({0,5}, 1, 1, c, 0,'T', posi, posi);
//position du joueur-largeur-hauteur-couleur-
float x = 0;
float y = 0;

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

        glPushMatrix();

        glTranslatef(x, y, 0.);
        //glScalef(q.width, q.height, 1.);
        drawOrigin(p);
        map.displayMap();
        glPopMatrix();       
        glColor3f(p.color.r, p.color.g, p.color.b); 
        p.drawBloc();

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
                        //p.pos.x-=0.5;
                        p.command(LEFT);
                        
                        //x+=0.5;
                        printf("position joueur : x:%f y:%f\n", p.pos.x, p.pos.y);
                        printf("Speed joueur : x:%f y:%f\n", p.speed.x, p.speed.y);
                    }

                    else if(e.key.keysym.sym == SDLK_RIGHT) {
                        //p.pos.x+=0.5;
                       p.command(RIGHT);
                        
                        //x+=0.5;
                        printf("position joueur : x:%f y:%f\n", p.pos.x, p.pos.y);
                        printf("Speed joueur : x:%f y:%f\n", p.speed.x, p.speed.y);
                    }

                    else if(e.key.keysym.sym == SDLK_UP) {
                        p.command(UP);
                        
                        //x+=0.5;
                        printf("position joueur : x:%f y:%f\n", p.pos.x, p.pos.y);
                        printf("Speed joueur : x:%f y:%f\n", p.speed.x, p.speed.y);
                    }


                    break;

                default:
                    
                     
                    break;
            }
        }
        
        /* Calcul du temps ecoule */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;

        if(elapsedTime < FRAMERATE_MILLISECONDS) 
            {
                SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
            }
    startTime=elapsedTime;

    p.move(FRAMERATE_MILLISECONDS/1000.);
    x=-p.pos.x;
    y=-p.pos.y;
    printf("position joueur : x:%f y:%f\n", p.pos.x, p.pos.y);
    printf("Speed joueur : x:%f y:%f\n", p.speed.x, p.speed.y);
    }

    
    /*** FIN DU JEU ***/


    /* Liberation des ressources associees a la SDL */
   // SDL_DestroyWindow(window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
