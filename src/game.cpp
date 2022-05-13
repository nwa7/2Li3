#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h> 

/* Dimensions de la fenetre SDL_WINDOW_RESIZABLE */
static const unsigned int WINDOW_WIDTH = 1920;
static const unsigned int WINDOW_HEIGHT = 1080;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

/* Espace fenêtre virtuelle */
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

// Structures
typedef struct {
    float x;
    float y;
} Vertex;

typedef struct{
    int r;
    int g;
    int b;
} Color;

// Fonctions des tructures
Vertex ini_vertex (float x, float y){
    Vertex new_v;
    new_v.x=x;
    new_v.y=y;
    return new_v;
};

Color ini_color( int r, int g, int b){
    Color new_c;
    new_c.r = r;
    new_c.g = g;
    new_c.b = b;
    return new_c;
};

// Classes
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

class Map
{
    public:
    Quad q1;
    Quad q2;
    int width;
    int height;
};

class Player
{
    public:
    Player(Quad q, char c, int s)
        : player(q), name(c), speed(s)
    {}

    Quad player;
    char name;
    int speed;
};

// test 

Vertex posi = ini_vertex(0,0);
Color c = ini_color(0,150,150);
Quad q = Quad(posi, 10,10, c);

Player p = Player(q, 'T', 1);

int compteur;
float aspectRatio;

void drawOrigin() 
{
    float currentColor[4];
    glGetFloatv(GL_CURRENT_COLOR,currentColor);

    glBegin(GL_LINES);

    glColor3f(1., 0., 0.);
    glVertex2f( p.player.pos.x , p.player.pos.y);
    glVertex2f( p.player.pos.x+1.0 , p.player.pos.y);

    glColor3f(0., 1., 0.);
    glVertex2f( p.player.pos.x , p.player.pos.y);
    glVertex2f( p.player.pos.x , p.player.pos.y+1.0);

    glEnd();

    glColor3fv(currentColor);
}

void drawSquare(int filled) 
{
    if(filled) 
    {
        glBegin(GL_TRIANGLE_FAN);
    }
    else 
    {
        glBegin(GL_LINE_STRIP);
    }

    glVertex2f( 0.5 , 0.5);
    glVertex2f( 0.5 , -0.5);
    glVertex2f( -0.5 , -0.5);
    glVertex2f( -0.5 , 0.5);
    

    glEnd();
}

void drawQuad(Quad q, int filled) 
{
    if(filled) 
    {
        glBegin(GL_TRIANGLE_FAN);
    }
    else 
    {
        glBegin(GL_LINE_STRIP);
    }

    glVertex2f( q.width/2 + q.pos.x, q.height/2 + q.pos.y);
    glVertex2f( q.width/2 + q.pos.x, -q.height/2+ q.pos.y);
    glVertex2f( -q.width/2 + q.pos.x, -q.height/2+ q.pos.y);
    glVertex2f( -q.width/2 + q.pos.x, q.height/2+ q.pos.y);

    glEnd();
}

int main(int argc, char** argv) 
{
    /*** INITIALIZATION ***/

    /* Déclaration du type tableau Vertex */
    Vertex tabvertex[256];

    /* Initialisation de la SDL */

    if(SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        const char* error = SDL_GetError();
        fprintf(stderr, "Erreur lors de l'intialisation de la SDL : %s\n", error);

        SDL_Quit();
        return EXIT_FAILURE;
    }
	
    /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
    SDL_Window* window;
    {
        window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        SDL_SetWindowTitle(window, "TMWA");

        if(NULL == window) 
        {
            const char* error = SDL_GetError();
            fprintf(stderr, "Erreur lors de la creation de la fenetre : %s\n", error);

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
            fprintf(stderr, "Erreur lors de la creation du contexte OpenGL : %s\n", error);

            SDL_DestroyWindow(window);
            SDL_Quit();
            return EXIT_FAILURE;
        }
    }


    onWindowResized(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    /*** BOUCLE DE JEU ***/

    int loop = 1;
    while(loop) 
    {
        /*** SDL ***/

        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glColor3f(p.player.color.r, p.player.color.g, p.player.color.b);
        glPushMatrix();
            //glTranslatef(p.player.pos.x, p.player.pos.y, 0.);
            //glScalef(q.width, q.height, 1.);

            drawQuad(p.player, 1);
            drawOrigin();
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
                    
                    if(e.key.keysym.sym == SDLK_LEFT) {
                        p.player.pos.x--;
                        printf("position joueur : x:%f y:%f\n", p.player.pos.x, p.player.pos.y);

                        glTranslatef(-1.,0,0);

                        
                    }

                    else if(e.key.keysym.sym == SDLK_RIGHT) {
                        p.player.pos.x++;
                        printf("position joueur : x:%f y:%f\n", p.player.pos.x, p.player.pos.y);
                        
                        glTranslatef(1.,0,0);
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

    /*** FIN DU JEU ***/


    /* Liberation des ressources associees a la SDL */
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
