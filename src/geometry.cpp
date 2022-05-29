#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "geometry.hh"

void drawOrigin() 
{
    float currentColor[4];
    glGetFloatv(GL_CURRENT_COLOR,currentColor);

    glBegin(GL_LINES);

    glColor3f(1., 0., 0.);
    glVertex2f( 0 , 0);
    glVertex2f( 0 , 1);

    glColor3f(0., 1., 0.);
    glVertex2f( 0, 0);
    glVertex2f( 1 , 0);

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


// Old Bloc.h
// Utilisable pour afficher des textures par exemple
// Utilisable comme plateformes

/**
    float x;
    float y;
    float sizeX;
    float sizeY;

    // Methods

    //lit les donnees
    float getPosX();
    float getPosY();
    float getSizeX();
    float getSizeY();

    //definir les donnees
    void setX(float x);
    void setY(float y);

} Vect;
**/

// Classes