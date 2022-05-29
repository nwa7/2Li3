#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <X11/Xlib.h>
#include <vector>

#include "map.hh"
#include "geometry.hh"
#include "player.hh"
#include "graphics.hh"
#include "quadtree.hh"
#include "fakesdlimage.hh"
#include "game.hh"

Display* disp = XOpenDisplay(NULL);
Screen* screen = XDefaultScreenOfDisplay(disp);
static const unsigned int WINDOW_WIDTH = screen->width;
static const unsigned int WINDOW_HEIGHT = screen->height;

/* Déclaration du type tableau Vertex */
Vect tabvertex[256];
int compteur;
float aspectRatio;

/* Quadtree */
Quadtree qt1(0,0,0,0);
Quadtree qt2(0,0,0,0);

int main(void) 
{  
	/*** INITIALISATION SDL ***/

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("Error initializing : %s\n", SDL_GetError());
		exit(11);
	}
	SDL_Window* window = SDL_CreateWindow("Barbapix", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH , WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_GLContext glcontext = initGraphics(window);

	/* IMAGES */
    GLuint textures[12];
    textures[0] = initTex("images/Ecran_jeu.png");
    textures[1] = initTex("images/Ecran_rules.png");
    textures[2] = initTex("images/Ecran_credits.png");
    textures[3] = initTex("images/start_col.png");
    textures[4] = initTex("images/start.png");
    textures[5] = initTex("images/rules_col.png");
    textures[6] = initTex("images/rules.png");
    textures[7] = initTex("images/credits_col.png");
    textures[8] = initTex("images/credits.png");
    textures[9] = initTex("images/exit_col.png");
    textures[10] = initTex("images/exit.png");
    textures[11] = initTex("images/Ecran_fin.png");

    /* FENETRE */
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    onWindowResized(WINDOW_WIDTH, WINDOW_HEIGHT);

    /*** INITIALISATION BOUCLES ***/

    // Menu du début
    int begin = 1;
    int menu = 0;
    unsigned int compt=0;

    // Boucle de jeu
    int loop = 0;

    // Fin du jeu
    int end = 1;


    /*** MENU DEBUT JEU ***/

    while(begin) {
        // Affichage menu
        chooseMenu(window,textures,menu, compt);

        // Choix menu
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            // Racourcis pour fermer fenetre
            if(e.type == SDL_QUIT){
				begin = 0;
				break;
			}
		
			if(e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_e || e.key.keysym.sym == SDLK_ESCAPE)){
				begin = 0; 
				break;
			}

            switch(e.type) {
                /* EVENTS FENETRE */
                case SDL_WINDOWEVENT:
                    switch (e.window.event) 
                    {
                        // Redimensionnement fenetre
                        case SDL_WINDOWEVENT_RESIZED:
                            onWindowResized(e.window.data1, e.window.data2);                
                            break;

                        default:
                            break; 
                    }
                    break;

                /* SAISIE SOURIS */
                case SDL_MOUSEBUTTONUP:
                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);

                    // Clic sur exit
                    if(e.button.x < 571 && e.button.x > 508 && e.button.y < 535 && e.button.y > 498) {
                        begin = 0;
                    }

                    // Clic sur start
                    else if(e.button.x < 582 && e.button.x > 498 && e.button.y < 318 && e.button.y > 283) {
                        begin = 0;
                        loop = 1;
                    }

                    // Clic sur rules
                    else if(e.button.x < 584 && e.button.x > 497 && e.button.y < 391 && e.button.y > 356) {
                        menu = 2;
                    }
                    // Clic sur credits
                    else if(e.button.x < 601 && e.button.x > 482 && e.button.y < 463 && e.button.y > 426) {
                        menu = 3;
                    }
                    break;
                

                /* SAISIE CLAVIER */
                case SDL_KEYDOWN:
                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);

                    // m pour retourner au menu principal
                    if(e.key.keysym.sym==SDLK_m) {
                        menu = 0;
                    }

                    // Flèche du haut
                    if(e.key.keysym.sym==SDLK_UP) {
                        if(compt > 1) {
                            compt--;
                        }
                    }
                    // Flèche du bas
                    else if(e.key.keysym.sym==SDLK_DOWN) {
                        if(compt < 4) {
                            compt ++;
                        }
                    }

                    // Touche retour à la ligne
                    else if(e.key.keysym.sym==SDLK_RETURN) {

                        //Entrer sur exit
                        if(compt == 4) {
                            begin = 0;
                        }

                         //Entrer sur start
                        else if(compt == 1) {
                            begin = 0;
                            loop = 1;
                        }

                        //Entrer sur rules
                        else if(compt == 2) {
                            menu = 2;
                        }
                        //Entrer sur credits
                        else if(compt == 3) {
                            menu = 3;
                        } 
                    }
                    break;
                    
                default:
                    break;
            }
        
        }
    }

    /* Initialisation du quadtree et de la map */
    Map map1(WINDOW_WIDTH,WINDOW_HEIGHT);
    map1.loadLvl(1);
    qt1.generate(&map1);

    Map map2(WINDOW_WIDTH,WINDOW_HEIGHT);
    map2.loadLvl(2);
    qt2.generate(&map2);

	/*** BOUCLE DE JEU ***/
    int response_game = gameLoop(window, &map1, &map2, &qt1, &qt2);
    
    /*** FIN DU JEU ***/

    if(end==1) {
        endScreen(window, textures);
        
        while(end) {

            SDL_Event e;
            while(SDL_PollEvent(&e)) {
                // Racourcis pour fermer fenetre
                if(e.type == SDL_QUIT){
                    end = 0;
                    break;
                }
            
                if(e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_e || e.key.keysym.sym == SDLK_ESCAPE)){
                    end = 0; 
                    break;
                }
            }
        }
    }

    /* Liberation des ressources associees a la SDL */
    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
