#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <X11/Xlib.h>
#include "map.hh"
#include "geometry.hh"
#include "player.hh"
#include "graphics.hh"
#include "quadtree.hh"
#include "fakesdlimage.hh"

Display* disp= XOpenDisplay(NULL);
Screen* screen = DefaultScreenOfDisplay(disp);
static const unsigned int WINDOW_WIDTH = screen->width;
static const unsigned int WINDOW_HEIGHT = screen->height;

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

    /* FENETRE */
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    onWindowResized(WINDOW_WIDTH, WINDOW_HEIGHT);

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

    /*** INITIALISATION BOUCLES ***/

    // Menu du début
    int begin = 1;
    int menu = 0;
    unsigned int compt=0;

    // Boucle de jeu
    int loop = 0;
    int niveau = 1;

    // Fin du jeu
    int end = 0;


    /*** MENU DEBUT JEU ***/

    while(begin) {
        // Affichage choix menu
        chooseMenu(window,textures,menu, compt);

        // Choix du menu
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

	/*** BOUCLE DE JEU ***/

    /* Initialisation du quadtree et de la map */
    Map map1(WINDOW_WIDTH,WINDOW_HEIGHT);
    map1.loadLvl(1);
    qt1.generate(&map1);

    Map map2(WINDOW_WIDTH,WINDOW_HEIGHT);
    map2.loadLvl(2);
    qt2.generate(&map2);
        
    while(loop) 
    {
       /* Recuperation du temps au debut de la boucle */
        int startTime = SDL_GetTicks();
        
        /* Calcul du temps ecoule */
        int elapsedTime = SDL_GetTicks() - startTime;

        /* // Test quadtree searchBloc
        std::vector<Bloc> coll = qt.searchBloc(&p);
        for(Bloc bloc : coll) {
            printf("Peut entrer en collision avec : %d", bloc.width);
        }*/
        
        /*** SDL ***/

        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Code de dessin 

        glPushMatrix();
            glTranslatef(x, y, 0.);
            drawOrigin();
            if(niveau == 1) {
                map1.displayMap();
            }
            else if(niveau == 2) {
                map2.displayMap();
            }   
            p.drawBloc();
        glPopMatrix();       
        glColor3f(p.color.r, p.color.g, p.color.b); 

        /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapWindow(window);
        
        
        /* EVENTS */
        
        // Niveau 1 terminé, passage au niveau 2
        if(niveau==1 && (int) p.pos.x == 21 && (int) p.pos.y == 1) {
            niveau = 2;
        }

        // Niveau 2 terminé, fin du jeu
        else if(niveau == 2 && (int) p.pos.x == 41 && (int) p.pos.y == 1) {
            loop = 0;
            end = 1;
        }
        

        SDL_Event e;
        while(SDL_PollEvent(&e)) 
        {
            /* L'utilisateur ferme la fenetre : */
           if(e.type == SDL_QUIT||e.key.keysym.sym == SDLK_e) 
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
                break;

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

    }

    
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
