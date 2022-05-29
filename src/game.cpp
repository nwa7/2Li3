#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "player.hh"
#include "geometry.hh"

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const int FRAMERATE_MILLISECONDS = 1000/20;


// Boucle de jeu
int gameLoop(SDL_Window* window, Map* map){
    // Boucle de jeu
    Color c = colors::blue;
    Vect posi = {0, 0};
    
    Player players[4] = {
        Player({-2.2,2.0}, 2, 5, c, 0,'T', posi, posi),
        Player({2.5,5}, 5, 5, c, 0,'T', posi, posi),
        Player({3.5,5}, 2, 22, c, 0,'T', posi, posi),
        Player({4.5,5}, 4, 2, c, 0,'T', posi, posi),};


    Player *current_player = &players[0];
    int current_player_index = 0;  // index du player courant
    //position du joueur-largeur-hauteur-couleur-
    float x = 0;
    float y = 0;
    int loop = 1;

    // Fin du jeu
    int end = 0;

    /*** MENU DEBUT JEU ***/

    Uint32 startTime = SDL_GetTicks();
    int h_player_order = 0;
    int player_jump_order = 0;
	/*** BOUCLE DE JEU ***/
    glMatrixMode(GL_MODELVIEW);

    while(loop) 
    {
       glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();
		// Dessins

		// Toute cette structure serait remplacable par un systeme plus vaste qui gererait l affichage des menus
		// SDL_GL_SwapWindow(window);
        /*** SDL ***/

        /* Recuperation du temps au debut de la boucle */
        
        /* Placer ici le code de dessin */

        glPushMatrix();

        glTranslatef(x, y, 0.);
        //glScalef(q.width, q.height, 1.);
        drawOrigin();
        map->displayMap(startTime);
               
        Player * p;
        for (int i=0; i<=4; i++){
            p=&players[i];
            p->drawBloc(startTime);
        };
        glPopMatrix();
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
                        h_player_order = LEFT;
                        
                        //x+=0.5;
                        printf("position joueur : x:%f y:%f\n", current_player->pos.x, current_player->pos.y);
                        printf("Speed joueur : x:%f y:%f\n", current_player->speed.x, current_player->speed.y);
                    }

                    else if(e.key.keysym.sym == SDLK_RIGHT) {
                        //p.pos.x+=0.5;
                        h_player_order = RIGHT;
                        
                        //x+=0.5;
                        printf("position joueur : x:%f y:%f\n", current_player->pos.x, current_player->pos.y);
                        printf("Speed joueur : x:%f y:%f\n", current_player->speed.x, current_player->speed.y);
                    }

                    else if(e.key.keysym.sym == SDLK_UP) {
                        player_jump_order = UP;
                        
                        //x+=0.5;
                        printf("position joueur : x:%f y:%f\n", current_player->pos.x, current_player->pos.y);
                        printf("Speed joueur : x:%f y:%f\n", current_player->speed.x, current_player->speed.y);
                    }
                    else if(e.key.keysym.sym == SDLK_TAB){
                        current_player_index = (current_player_index +1) % 4;
                        current_player = &players[current_player_index];
                    }


                    break;
                case SDL_KEYUP:
                    switch(e.key.keysym.sym){
                        case SDLK_LEFT:
                            if (h_player_order == LEFT){
                                h_player_order = 0;
                            };
                            break;
                        case SDLK_RIGHT:
                            if (h_player_order == RIGHT){
                                h_player_order = 0;
                            };
                            break;
                        case SDLK_UP:
                            player_jump_order = 0;
                            break;
                    }   


                default:
                    
                     
                    break;
            }
        }
        if (h_player_order != 0){
            current_player->command(h_player_order);
        };
        if (player_jump_order != 0){
            current_player->command(UP);
        }

        
        /* Calcul du temps ecoule */
        Uint32 endLoopTime = SDL_GetTicks();

        if(endLoopTime - startTime < FRAMERATE_MILLISECONDS) 
            {
                SDL_Delay(FRAMERATE_MILLISECONDS - endLoopTime + startTime);
            }
    for (int i=0; i<=4; i++){
        p = &players[i];
        p->move((endLoopTime - startTime)/1000., map, players);
    }
    
    startTime=endLoopTime;

    // Position de la caméra
    x=-current_player->pos.x;
    y=-current_player->pos.y;
    printf("position joueur : x:%f y:%f\n", current_player->pos.x, current_player->pos.y);
    printf("Speed joueur : x:%f y:%f\n", current_player->speed.x, current_player->speed.y);
    }
}