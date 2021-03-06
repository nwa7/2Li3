#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <X11/Xlib.h>

#include "player.hh"
#include "geometry.hh"
#include "quadtree.hh"

Display* d = XOpenDisplay(NULL);
Screen* s = XDefaultScreenOfDisplay(d);
static const unsigned int WINDOW_WIDTH = s->width;
static const unsigned int WINDOW_HEIGHT = s->height;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const int FRAMERATE_MILLISECONDS = 1000/20;

// Boucle de jeu
int gameLoop(SDL_Window* window, Map* map1, Map* map2, Quadtree* qt1, Quadtree* qt2){
    // Boucle de jeu
    Color c = colors::blue;
    Vect posi = {0, 0};
    
    Player players[4] = {
        Player({-2.2,2.0}, 2, 5, colors::pink, 0,'T', posi, posi),
        Player({-6,2.0}, 5, 5, colors::orange, 0,'A', posi, posi),
        Player({90,5}, 2, 2, colors::purple, 0,'B', posi, posi),
        Player({110,5}, 22, 2, colors::blue, 0,'Y', posi, posi)
    };

    Bloc signe({-2.2,2.0}, 1, 1, colors::green, 0);

    Player *current_player = &players[0];
    int current_player_index = 0;  // index du player courant
    float x = 0;
    float y = 0;

    // Entree boucle
    int loop = 1;

    // Niveau
    int niveau = 1;
    int bloc1 = 0;
    int bloc2 = 0;
    int bloc3 = 0;
    int bloc4 = 0;

    // Fin du jeu
    int end = 0;

    Uint32 startTime = SDL_GetTicks();
    int h_player_order = 0;
    int player_jump_order = 0;

    /*** BOUCLE DE JEU ***/

    while(loop) 
    {
        
        /*** SDL ***/
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glPushMatrix();
            glTranslatef(x, y, 0.);
            // Affiche le bon niveau
            if(niveau == 1) {
                map1->displayMap(startTime);
            }
            else if(niveau == 2) {
                map2->displayMap(startTime);
            }
            
            // Affiche les joueurs
            Player * p;
            for (int i = 0; i < 4; i++){
                p = players + i;
                drawSquare(*p);
                p->drawBloc(startTime);
            };
            signe.drawBloc(startTime);
        glPopMatrix();

        /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapWindow(window);
        
        
        /* EVENTS */

        // NIVEAU 1
        if (niveau == 1){
            if((int) current_player->pos.x == 172 && (int) current_player->pos.y == 11 && current_player->name == 'T') {
                bloc1=1;
            }
            if((int) current_player->pos.x ==  30 && (int) current_player->pos.y == -14 && current_player->name == 'A') {
                bloc2=1;
            }

            if((int) current_player->pos.x == 146 && (int) current_player->pos.y == -14 && current_player->name == 'B') {
                bloc3=1;
            }

            if((int) current_player->pos.x == 130 && (int) current_player->pos.y == 2 && current_player->name == 'Y') {
                bloc4=1;
                
            }

            if (bloc1 && bloc2 && bloc3 && bloc4){ 
                loop = 0;
                //niveau = 2;
                end = 1;
            }
        }

        // Niveau 2
        /*
        if (niveau == 2){
            if((int) current_player->pos.x == 15 && (int) current_player->pos.y == 0 && current_player->name == 'T') {
                end = 1;
                loop = 0;
            }
        }
        */
        
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
                        h_player_order = LEFT;
                        printf("position joueur : x:%f y:%f\n", current_player->pos.x, current_player->pos.y);
                        printf("Speed joueur : x:%f y:%f\n", current_player->speed.x, current_player->speed.y);
                    }

                    else if(e.key.keysym.sym == SDLK_RIGHT) {
                        h_player_order = RIGHT;
                        printf("position joueur : x:%f y:%f\n", current_player->pos.x, current_player->pos.y);
                        printf("Speed joueur : x:%f y:%f\n", current_player->speed.x, current_player->speed.y);
                    }

                    else if(e.key.keysym.sym == SDLK_UP) {
                        player_jump_order = UP;
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
        if(niveau==1) {
            p->move((endLoopTime - startTime)/1000., map1, players);
        }
        else if(niveau==2) {
            p->move((endLoopTime - startTime)/1000., map2, players);
        }
        
    }
    
    startTime=endLoopTime;

    //Position d'un signe distinctif

    signe.pos.x=(current_player->pos.x)+(current_player->width)/2;
    signe.pos.y=(current_player->pos.y)+(current_player->height)/2;

    // Position de la cam??ra
    x=-current_player->pos.x;
    y=-current_player->pos.y;
    printf("position joueur : x:%f y:%f\n", current_player->pos.x, current_player->pos.y);
    printf("Speed joueur : x:%f y:%f\n", current_player->speed.x, current_player->speed.y);
    }

    return 0;
}