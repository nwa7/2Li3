
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

int BoundingBox::collide(BoundingBox other){

    // Défini s'il y a une collision ou non 

    if (this->upperLeft.x>other.downRight.x){
        return NOCOLLISION;
    }
    if (this->upperLeft.y<other.downRight.x){
        return NOCOLLISION;
    }
    if (this->downRight.x<other.upperLeft.x){
        return NOCOLLISION;
    }
    if (this->downRight.y>other.upperLeft.y){
        return NOCOLLISION;
    }

    return COLLISION;
} 