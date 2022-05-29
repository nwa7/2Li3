#include <string>
#include <math.h>

#include "player.hh"
#include "map.hh"


void Player::command(int direction){
    this->hasOrder=1;
    switch(direction){
        case RIGHT:
            this->acceleration.x+=1.0;
        break;
        case LEFT:
            this->acceleration.x-=1.0;
        break;
        case UP:
            //this->acceleration.y+=10.0;
            printf("h:%i ", this->hasCollision);

            if (this->hasCollision==1){
                this->speed.y=7.0;

            }
            else 
            {
                this->hasOrder=0;

            }

        break;
    }
}

void Player::move(double dt, Map* map, Player* players){
    //void Player::move(float dt, Map map)
    //Map doit avoir une fonction collide bounding box

    //Définition du mouvement 
    if(this->hasOrder==0){
        this->acceleration= {0,-9.81};
        this->speed.x=this->speed.x/2.;
    }

    this->hasOrder=0;

    Vect futurSpeed = {this->acceleration.x*dt+this->speed.x,this->acceleration.y*dt+this->speed.y };


    Vect futurPos = {this->acceleration.x*dt*dt/2+this->speed.x*dt +this->pos.x,
    this->acceleration.y*dt*dt/2+this->speed.y*dt + this->pos.y};


    if (futurSpeed.x<-10){
        futurSpeed.x=-10;
        this->acceleration.x=0.0;
    }
    if (futurSpeed.x>10){
        futurSpeed.x=10;
        this->acceleration.x=0.0;
    }
    //Détermination des collisions

    //Définition du bounding box 
    //c'est map.collide
    Collision collision, current_collision;
    collision.result = 0;

    BoundingBox mybox = BoundingBox({futurPos.x, futurPos.y + height}, {futurPos.x + width, futurPos.y});

    // Collision avec les autres blocs
    for(auto bloc = std::begin(map->platforms_); bloc != std::end(map->platforms_); ++bloc) {
        BoundingBox bbox = bloc->getBoundingBox();
        current_collision = mybox.collision_side(bbox, 0.0, 0.0);
        if (current_collision.result == NOCOLLISION) continue;
        collision.result = collision.result | current_collision.result;
        if (current_collision.result & COLLISIONLEFT){
            collision.xmin = current_collision.xmin;
        };
        if (current_collision.result & COLLISIONRIGHT){
            collision.xmax = current_collision.xmax;
        };
        if (current_collision.result & COLLISIONUP){
            collision.ymax = current_collision.ymax;
        };
        if (current_collision.result & COLLISIONDOWN){
            collision.ymin = current_collision.ymin;
        };
    };
    //collisions avec les autres players
    for(int i=0; i<=4; i++){
        Player *p = &players[i];
        if (p == this){  // évisons les collisions avec soi-même
            continue;
        };
        BoundingBox bbox = p->getBoundingBox();
        current_collision = mybox.collision_side(bbox, 0.0, 0.0);
        if (current_collision.result == NOCOLLISION) continue;
        collision.result = collision.result | current_collision.result;
        if (current_collision.result & COLLISIONLEFT){
            collision.xmin = current_collision.xmin;
        };
        if (current_collision.result & COLLISIONRIGHT){
            collision.xmax = current_collision.xmax;
        };
        if (current_collision.result & COLLISIONUP){
            collision.ymax = current_collision.ymax;
        };
        if (current_collision.result & COLLISIONDOWN){
            collision.ymin = current_collision.ymin;
        };
    };

    if (collision.result != NOCOLLISION){

        printf("collision %i \n", collision.result);
        this->hasCollision=1;
        if ((collision.result & (COLLISIONLEFT + COLLISIONRIGHT)) == (COLLISIONLEFT + COLLISIONRIGHT)){
            // si on a une double collision droite / gauche, c'est qu'on n'a que le sol ou le plafond
            collision.result -= (COLLISIONLEFT + COLLISIONRIGHT);
            printf("double collision droite / gauche supprimée");
        }
        if ((collision.result & (COLLISIONUP + COLLISIONDOWN))== (COLLISIONUP + COLLISIONDOWN)){
            // pareil entre haut et bas
            collision.result -= (COLLISIONUP + COLLISIONDOWN);
        };
        if ((collision.result & COLLISIONLEFT) == COLLISIONLEFT){
            futurPos.x = collision.xmin;
            futurSpeed.x = 0;
            acceleration.x = 0;
        };
        if ((collision.result & COLLISIONRIGHT) == COLLISIONRIGHT){
            printf("collison à droite %f", collision.xmax);
            futurPos.x = collision.xmax - this->width;
            futurSpeed.x = 0;
            acceleration.x = 0;
        };
        if ((collision.result & COLLISIONUP) == COLLISIONUP){
            futurPos.y = collision.ymax - this->height;
            futurSpeed.y = 0;
            
        };
        if ((collision.result & COLLISIONDOWN) == COLLISIONDOWN){
            printf("collision en bas %f", collision.ymin);
            futurPos.y = collision.ymin;
            futurSpeed.y = 0;

        };

    } else
    {
        this->hasOrder = 0;
        this->hasCollision = 0;
        /* code */
    }

    this->speed.x=futurSpeed.x;
    this->speed.y=futurSpeed.y;

    this->pos.x=futurPos.x;
    this->pos.y=futurPos.y;

}