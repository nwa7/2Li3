
#include <GL/gl.h>
#include "bloc.h"

Bloc::Bloc(Vect p, int w, int h, Color c)
    : pos(p), width(w), height(h), color(c)
{}
 

void Bloc::drawBloc(int filled) const
{
    if(filled) 
    {
        glBegin(GL_TRIANGLE_FAN);
    }
    else 
    {
        glBegin(GL_LINE_STRIP);
    }

    glVertex2f( this->width/2 + this->pos.x, this->height/2 + this->pos.y);
    glVertex2f( this->width/2 + this->pos.x, -this->height/2+ this->pos.y);
    glVertex2f( -this->width/2 + this->pos.x, -this->height/2+ this->pos.y);
    glVertex2f( -this->width/2 + this->pos.x, this->height/2+ this->pos.y);

    glEnd();
}

/***
void Bloc::setX(float x){
    this->x = x;
}

void Quad::setY(float y){
    this->y = y;
}

float Bloc::getPosX(){
    return this->x;
}

float Bloc::getPosY(){
    return this->y;
}

float Bloc::getSizeX(){
    return this->sizeX;
}

float Bloc::getSizeY(){
    return this->sizeY;
}

***/