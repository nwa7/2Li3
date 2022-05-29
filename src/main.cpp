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
#include "quadtree.hh"
#include "fakesdlimage.hh"


static const unsigned int WINDOW_WIDTH = 1080;
static const unsigned int WINDOW_HEIGHT = 720;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const int FRAMERATE_MILLISECONDS = 1000/20;

// TESTS

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

/* Quadtree */
Quadtree quad;


int main(int argc, char** argv) 
{   
	/*** INITIALISATION SDL ***/

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("Error initializing : %s\n", SDL_GetError());
		exit(11);
	}
	SDL_Window* window = SDL_CreateWindow("Barbapix", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH , WINDOW_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_GLContext glcontext = initGraphics(WINDOW_WIDTH , WINDOW_HEIGHT, window);

	/* TEXTURES */
	GLuint ecran_debut = initTex("images/Ecran_jeu.png");
    GLuint start_c = initTex("images/start_col.png");
    GLuint start = initTex("images/start.png");
    GLuint rules_c = initTex("images/rules_col.png");
    GLuint rules = initTex("images/rules.png");
    GLuint credits_c = initTex("images/credits_col.png");
    GLuint credits = initTex("images/credits.png");
    GLuint exit_c = initTex("images/exit_col.png");
    GLuint exit = initTex("images/exit.png");
    GLuint ecran_fin = initTex("images/Ecran_fin.png");

    /* FENETRE */
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    onWindowResized(WINDOW_WIDTH, WINDOW_HEIGHT);

    /*** INITIALISATION BOUCLES ***/

    // Menu du début
    int begin = 1;
    unsigned int compt=0;

    // Boucle de jeu
    int loop = 0;

    // Fin du jeu
    int end = 0;

    /*** MENU DEBUT JEU ***/

    while(begin) {
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Active texturing & attache texture au point de bind
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Fond d'écran
        glBindTexture(GL_TEXTURE_2D, ecran_debut);
        fixeTexEcran();

        // Start
        glTranslatef(0,3,0);
        affichageMenu(compt, 1, start, start_c);

        // Rules
        glTranslatef(0,-4,0);
        affichageMenu(compt, 2, rules, rules_c);

        // Credits
        glTranslatef(0,-4,0);
        affichageMenu(compt, 3, credits, credits_c);

        // Exit
        glTranslatef(0,-4,0);
        affichageMenu(compt, 4, exit, exit_c);

        // Detache texture & desactive texturing
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);

        // Mise a jour fenetre
        SDL_GL_SwapWindow(window);

        /* EVENTS */
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

                    /*// Clic sur rules
                    else if(e.button.x < 584 && e.button.x > 497 && e.button.y < 391 && e.button.y > 356) {
                        ...;
                    }*/

                    // Clic sur credits
                    else if(e.button.x < 601 && e.button.x > 482 && e.button.y < 463 && e.button.y > 426) {
                        begin = 0;
                        loop = 0;
                        end = 1;
                    }
                    break;
                

                /* SAISIE CLAVIER */
                case SDL_KEYDOWN:
                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);

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

                        /*//Entrer sur rules
                        else if(compteur == 2) {
                            ...;
                        }*/

                        //Entrer sur credits
                        else if(compt == 3) {
                            begin = 0;
                            loop = 0;
                            end = 1;
                        }
                    }
                    break;
                    
                default:
                    break;
            }
        
        }
    }

	/*** BOUCLE DE JEU ***/

    while(loop) 
    {
       /* Recuperation du temps au debut de la boucle */
        int startTime = SDL_GetTicks();
        
        /* Calcul du temps ecoule */
        int elapsedTime = SDL_GetTicks() - startTime;
        
        /*** SDL ***/

        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Active texturing & attache texture au point de bind
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Code de dessin 

        glPushMatrix();
            glTranslatef(x, y, 0.);
            drawOrigin(p);
            map.displayMap(elapsedTime);
            p.drawBloc(elapsedTime);
        glPopMatrix();       
        glColor3f(p.color.r, p.color.g, p.color.b); 

        // Detache texture & desactive texturing
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);

        /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapWindow(window);
        
        
        /* EVENTS */

        if((int) p.pos.x == 21 && (int) p.pos.y == 1) {
            loop = 0;
            end = 1;
        }

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
        
        if(elapsedTime < FRAMERATE_MILLISECONDS) 
        {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }

        startTime=elapsedTime;

        p.move(FRAMERATE_MILLISECONDS/1000.);
        x=-p.pos.x;
        y=-p.pos.y;

        /*
        printf("position joueur : x:%f y:%f\n", p.pos.x, p.pos.y);
        printf("Speed joueur : x:%f y:%f\n", p.speed.x, p.speed.y);
        */
    }

    
    /*** FIN DU JEU ***/

    if(end==1) {
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        // Active texturing & attache texture au point de bind
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Fond d'écran
        glBindTexture(GL_TEXTURE_2D, ecran_fin);
        fixeTexEcran();

        // Detache texture & desactive texturing
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);

        // Mise a jour fenetre
        SDL_GL_SwapWindow(window);
        
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
