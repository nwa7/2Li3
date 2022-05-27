#include <string>

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

void Player::move(double dt){
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
        this->acceleration.x=0;
    }
    if (futurSpeed.x>10){
        futurSpeed.x=10;
        this->acceleration.x=0;
    }
    //Détermination des collisions
    //Définition du bounding box 
    //c'est map.collide
   


    if (futurPos.y<0){
        this->hasCollision=1;
        futurSpeed.y=0;
        futurPos.y=0;
    }
    else{
        this->hasCollision=0;
    }

    this->speed.x=futurSpeed.x;
    this->speed.y=futurSpeed.y;

    this->pos.x=futurPos.x;
    this->pos.y=futurPos.y;

}


/*

Player newPlayer(float x, float y){
    Player player;
    player.acceleration = {0, -9.81};
    player.speed = {0,0};
    player.position = {x,y};
    return player;
}

void Player::setAccX(float x){
    this->acceleration.x = x;
}

void Player::moveAndCollide(){

    float dt = 1/60;

    this->speed += this->acceleration*dt;

    this->position += this->speed*dt;

    // Travail sur les collisions
    // RECOPIER SANS SCRUPULES MA FOCNTION

}

int Player::collision(Rectangle r){
    // Remplir

}
*/