#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h> 

// Pour relancer vite, Dans TD02 make ex01 puis bin/td02_ex01.out

/* Dimensions de la fenetre SDL_WINDOW_RESIZABLE */
static const unsigned int WINDOW_WIDTH = 1920;
static const unsigned int WINDOW_HEIGHT = 1080;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

/* Espace fenêtre virtuelle */
static const float GL_VIEW_SIZE = 2.;
static const int polycercle = 300;
static const float pi = 3.14159;

typedef struct {
    float x;
    float y;
} Vertex;

typedef struct{
    int r;
    int g;
    int b;
} Color;

class Quad
{
    public:
    Quad(Vertex p, int w, int h, Color c)
        : pos(p), width(w), height(h), color(c)
    {}
 
    Vertex pos;
    int width;
    int height;
    Color color;
};

Vertex ini_vertex (float x, float y){
    Vertex new_v;
    new_v.x=x;
    new_v.y=y;
    return new_v;
}

Color ini_color( int r, int g, int b){
    Color new_c;
    new_c.r = r;
    new_c.g = g;
    new_c.b = b;
    return new_c;
}


Vertex posi = ini_vertex(0,0);
Color c = ini_color(0,255,0);
Quad q = Quad(posi, 500,300, c);

int compteur;
float aspectRatio;


void drawSquare(int filled) 
{
    if(filled) 
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
    }
    else 
    {
        glBegin(GL_LINE_STRIP);
    }

    glVertex2f( 0.5 , -0.5);
    glVertex2f( 0.5 , 0.5);
    glVertex2f( -0.5 , 0.5);
    glVertex2f( -0.5 , -0.5);
    glVertex2f( 0.5 , -0.5);

    glEnd();
    glBegin(GL_LINE_LOOP);
    //    eventuellement d’autres points ...
    //    aspectRatio = WINDOW_WIDTH / (float) WINDOW_HEIGHT;
    //    Vertex tabvertex[256];
    //    for(int j=0;j<compteur; j++){
    //        glColor3f(1, 0, 1);
    //        glVertex2f(tabvertex[j].x, tabvertex[j].y);
    //        GL_LINE_LOOP;
    //    }
        glEnd();
} 

int main(int argc, char** argv) 
{
    Vertex tabvertex[256];
    /* Initialisation de la SDL */

    if(SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        const char* error = SDL_GetError();
        fprintf(
            stderr, 
            "Erreur lors de l'intialisation de la SDL : %s\n", error);

        SDL_Quit();
        return EXIT_FAILURE;
    }
	
    /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
    SDL_Window* window;
    {
        window = SDL_CreateWindow(
        "",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        SDL_SetWindowTitle(window, "TWA");

        if(NULL == window) 
        {
            const char* error = SDL_GetError();
            fprintf(
                stderr,
                "Erreur lors de la creation de la fenetre : %s\n", error);

            SDL_Quit();
            return EXIT_FAILURE;
        }
    }
   
    SDL_GLContext context;
    {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        context = SDL_GL_CreateContext(window);
    
        if(NULL == context) 
        {
            const char* error = SDL_GetError();
            fprintf(
                stderr,
                "Erreur lors de la creation du contexte OpenGL : %s\n", error);

            SDL_DestroyWindow(window);
            SDL_Quit();
            return EXIT_FAILURE;
        }
    }
/* Déclaration du type tableau Vertex */

    /* Boucle principale */
    int loop = 1;
    while(loop) 
    {
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();
        /* Placer ici le code de dessin */

        

        glColor3f(c.r, c.g, c.b);
        drawSquare(1);
        
        /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapWindow(window);
        
        /* Boucle traitant les evenements */
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
                    Vertex vertex;
                    aspectRatio = WINDOW_WIDTH / (float) WINDOW_HEIGHT;
                if (aspectRatio > 1){   
                    vertex.x=(-1 + 2. * e.button.x / (float) WINDOW_WIDTH) * (GL_VIEW_SIZE / 2)*aspectRatio;
                    vertex.y=-(-1 + 2. * e.button.y / (float) WINDOW_HEIGHT) * (GL_VIEW_SIZE / 2);
                    tabvertex[compteur]=vertex;
                    compteur++;
                }
                else {
                    vertex.x=(-1 + 2. * e.button.x / (float) WINDOW_WIDTH) * (GL_VIEW_SIZE / 2);
                    vertex.y=-(-1 + 2. * e.button.y / (float) WINDOW_HEIGHT) * (GL_VIEW_SIZE / 2)/aspectRatio;
                    tabvertex[compteur]=vertex;
                    compteur++;
                    }

                    break;

                
                /* Touche clavier */
                case SDL_KEYDOWN:
                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);
                    if(e.key.keysym.sym == SDLK_a) {
                        glMatrixMode(GL_MODELVIEW);
                        glLoadIdentity();
                        glScalef(5.,5.,5.);
                    }
                    break;
                default:
                    break;
            }
        }

        /* Calcul du temps ecoule */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        /* Si trop peu de temps s'est ecoule, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) 
        {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }

    /* Liberation des ressources associees a la SDL */
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
