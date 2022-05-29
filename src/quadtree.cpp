#include "quadtree.hh"

void Quadtree::generate(Bloc* map){

    int subWidth = (int) (map->width/2);
    int subHeight = (int) (map->height/2);
    int x = (int) map->pos.x;
    int y = (int) map->pos.y;
    
    // Initialisation racine
    this->xmin=-subWidth;
    this->xmax=subWidth;
    this->ymin=-subHeight;
    this->ymax=subHeight;
    this->platforms[0]=map;
    this->ind++;

    // Initialisation upleft
    this->upleft->xmin=x-subWidth;
    this->upleft->xmax=x;
    this->upleft->ymin=y;
    this->upleft->ymax=y+subHeight;

    // Initialisation downleft
    this->downleft->xmin=x-subWidth;
    this->downleft->xmax=x;
    this->downleft->ymin=y-subHeight;
    this->downleft->ymax=y;

    // Initialisation upright
    this->upright->xmin=x;
    this->upright->xmax=x+subWidth;
    this->upright->ymin=y;
    this->upright->ymax=y+subHeight;
    
    // Initialisation downright
    this->downright->xmin=x;
    this->downright->xmax=x+subWidth;
    this->downright->ymin=y-subHeight;
    this->downright->ymax=y;

}

void Quadtree::split() {
    int subWidth = (int) ((this->xmax - this->xmin)/2);
    int subHeight = (int) ((this->ymax - this->ymin)/2);
    int x = (int) ((this->xmax + this->xmin)/2);
    int y = (int) ((this->ymax + this->ymin)/2);

    // Upleft
    this->upleft->xmin=x-subWidth;
    this->upleft->xmax=x;
    this->upleft->ymin=y;
    this->upleft->ymax=y+subHeight;

    // Downleft
    this->downleft->xmin=x-subWidth;
    this->downleft->xmax=x;
    this->downleft->ymin=y-subHeight;
    this->downleft->ymax=y;

    // Upright
    this->upright->xmin=x;
    this->upright->xmax=x+subWidth;
    this->upright->ymin=y;
    this->upright->ymax=y+subHeight;
    
    // Downright
    this->downright->xmin=x;
    this->downright->xmax=x+subWidth;
    this->downright->ymin=y-subHeight;
    this->downright->ymax=y;
}

int Quadtree::searchLeaf(Bloc* obj){
    int pos_x = (int) ((this->xmax + this->xmin)/2);
    int pos_y = (int) ((this->ymax + this->ymin)/2);

    int index = -1; // Si objet appartient au parent
    bool up = false;
    bool down = false;

    // Test si objet est entièrement dans cadran du haut
    if(obj->getPosY() > pos_y &&  obj->getPosY() + obj->getHeight()/2 > pos_y) {
        up = true;
    }
    
    // Test si objet est entièrement dans cadran du bas
    else if(obj->getPosY() < pos_y &&  obj->getPosY() + obj->getHeight()/2 < pos_y) {
        down = true;
    }

    // Test si objet est entièrement dans cadran de gauche
    if(obj->getPosX() < pos_x &&  obj->getPosX() + obj->getWidth()/2 < pos_x) {
        
        // En haut
        if(up) {
            index = 1;
        }
        
        // En bas
        else if(down) {
            index = 3;
        }
    }

    // Test si objet est entièrement dans cadran de droite
    else if(obj->getPosX() > pos_x &&  obj->getPosX() + obj->getWidth()/2 > pos_x) {
        
        // En haut
        if(up) {
            index = 2;
        }
        
        // En bas
        else if(down) {
            index = 4;
        }
    }
    return index;
}

void Quadtree::insertBloc(Bloc* obj) {
    if(this->downleft !=nullptr) {
        int index = this->searchLeaf(obj);

        // L'objet appartient à un enfant
        if(index != -1) {

            // Haut-gauche
            if(index==1) {
                this->upleft->insertBloc(obj);
                return;
            }
            // Haut-doite
            else if(index==2) {
                this->upright->insertBloc(obj);
                return;
            }
            // Bas-gauche
            else if(index==3) {
                this->downleft->insertBloc(obj);
                return;
            }
            // Bas-droite
            else if(index==4) {
                this->downright->insertBloc(obj);
                return;
            }   
        }
    }

    // S'il n'y a plus de place dans platforms
    if(this->ind<=4 && this->downleft == nullptr) {
        this->split();
    }

    // Et si ça ne loge pas dans le nouveau split Et qu'a plus de place avant ?

    // Sinon ajout
    else {
        this->platforms[this->ind]=obj;
        this->ind++;
    }
}

Bloc* Quadtree::collision(Bloc* returnObjets[], Bloc* bloc) {
    int index = this->searchLeaf(bloc);
    if(index != -1 && this->downleft != nullptr) {
        // Haut-gauche
        if(index==1) {
            this->upleft->collision(returnObjets,bloc);
        }
        // Haut-doite
        else if(index==2) {
            this->upright->collision(returnObjets,bloc);
        }
        // Bas-gauche
        else if(index==3) {
            this->downleft->collision(returnObjets,bloc);
        }
        // Bas-droite
        else if(index==4) {
            this->downright->collision(returnObjets,bloc);
        }
    }

    for(int i=0; i< this->ind; i++) {
        returnObjets[i]=this->platforms[i];
    }

    return returnObjets[0];
}
