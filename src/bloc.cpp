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


BoundingBox::BoundingBox(Vect upperLeft, Vect downRight)
    : upperLeft(upperLeft), downRight(downRight)
    {};

int BoundingBox::collide(BoundingBox other, float offsetx, float offsety){

    // Défini s'il y a une collision ou non 

    if (this->upperLeft.x>other.downRight.x + offsetx){
        return NOCOLLISION;
    }
    if (this->upperLeft.y<other.downRight.y + offsety){
        return NOCOLLISION;
    }
    if (this->downRight.x<other.upperLeft.x + offsetx){
        return NOCOLLISION;
    }
    if (this->downRight.y>other.upperLeft.y + offsety){
        return NOCOLLISION;
    }

    return COLLISION;
};



// Détermine quelle type de collision il peut y avoir. offsetx et offsety permettent de calculer la collision lorsque
// le bounding box other est dans une position relative par rapport à this.
Collision BoundingBox::collision_side(BoundingBox other, float offsetx, float offsety){
    // Y a-t-il une collision ?
    Collision collision;
    if (this->collide(other, offsetx, offsety) == NOCOLLISION){
        collision.result = NOCOLLISION;
        return collision;
    };
    // Pour déterminer de quel côté la ou les collisions se trouvent,
    // on coupe la box en 4 et on regarde qui touche
    BoundingBox subBox = BoundingBox(this->upperLeft, {(this->upperLeft.x + this->downRight.x)/2., this->downRight.y});
    if (subBox.collide(other , offsetx, offsety) == COLLISION){
        collision.result += COLLISIONLEFT;
        collision.xmin = other.downRight.x;
    };
    subBox = BoundingBox(this->upperLeft, {this->upperLeft.x,  (this->upperLeft.y +this->downRight.y)/2.});
    if (subBox.collide(other, offsetx, offsety) == COLLISION){
        collision.result += COLLISIONUP;
        collision.ymax = other.downRight.y;
    };
    subBox = BoundingBox({(this->upperLeft.x + this->downRight.x)/2., this->upperLeft.y}, this->downRight);
    if (subBox.collide(other, offsetx, offsety) == COLLISION){
        collision.result += COLLISIONRIGHT;
        collision.xmax = other.upperLeft.x;
    };
    subBox = BoundingBox({this->upperLeft.x, (this->upperLeft.y + this->downRight.y) / 2.}, this->downRight);
    if (subBox.collide(other, offsetx, offsety) == COLLISION){
        collision.result += COLLISIONDOWN;
        collision.ymin = other.upperLeft.y;
    };



}