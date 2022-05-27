#include <GL/gl.h>
#include "bloc.hh"

Bloc::Bloc(Vect p, int w, int h, Color c, int a)
    : pos(p), width(w), height(h), color(c), animated(a)
{} 

void Bloc::drawBloc() const
{
    glBegin(GL_TRIANGLE_FAN);

    glColor3f(this->color.r, this->color.g, this->color.b);

    glVertex2f( this->pos.x, this->pos.y);
    glVertex2f( this->width + this->pos.x, this->pos.y);
    glVertex2f( this->width + this->pos.x, this->height+ this->pos.y);
    glVertex2f( this->pos.x, this->height+ this->pos.y);

    glEnd();
    
    /*** centré sur le centre du bloc perso

    glBegin(GL_TRIANGLE_FAN);


    glVertex2f( this->width/2 + this->pos.x, this->height/2 + this->pos.y);
    glVertex2f( this->width/2 + this->pos.x, -this->height/2+ this->pos.y);
    glVertex2f( -this->width/2 + this->pos.x, -this->height/2+ this->pos.y);
    glVertex2f( -this->width/2 + this->pos.x, this->height/2+ this->pos.y);

    glEnd();
    ***/
}


void Bloc::setX(float x){
    this->pos.x = x;
}

void Bloc::setY(float y){
    this->pos.y = y;
}

float Bloc::getPosX(){
    return this->pos.x;
}

float Bloc::getPosY(){
    return this->pos.y;
}

float Bloc::getWidth(){
    return this->width;
}

float Bloc::getHeight(){
    return this->height;
}
