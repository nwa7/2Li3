#include <vector>
#include "quadtree.hh"

Quadtree::Quadtree(int xmin, int xmax, int ymin, int ymax) :
    xmin(xmin), xmax(xmax), ymin(ymin), ymax(ymax) 
{}

void Quadtree::generate(Map* map){

    int subWidth = (int) (map->width_/2);
    int subHeight = (int) (map->height_/2);
    
    // Initialisation racine
    this->xmin=-subWidth;
    this->xmax=subWidth;
    this->ymin=-subHeight;
    this->ymax=subHeight;

    // Ajout blocs
    for(Bloc bloc : map->platforms_) {
            this->insertBloc(bloc);
        }
}

/* Recup infos */
int Quadtree::getX() {
    return (this->xmin+this->xmax)/2;
}
int Quadtree::getY() {
    return (this->ymin+this->ymax)/2;
}
bool Quadtree::isLeaf() {
    return (this->upleft==nullptr && this->upright==nullptr && this->downleft==nullptr && this->downright==nullptr);
}
bool Quadtree::isFull() {
    return (this->blocs.size()>4);
}

void Quadtree::split() {
    // Upleft
    this->upleft = new Quadtree(this->xmin, this->getX(), this->getY(), this->ymax);
    // Downleft
    this->downleft = new Quadtree(this->xmin, this->getX(),this->ymin, this->getY());
    // Upright
    this->upright = new Quadtree(this->getX(), this->xmax, this->getY(), this->ymax);
    // Downright
    this->downright = new Quadtree(this->getX(), this->xmax, this->ymin, this->getY());
}

/* Recherche de la partie du quadtree dans laquelle va etre range le bloc */
int Quadtree::searchLeaf(Bloc* obj){
    int index;
    if(!this->isLeaf()) {
        // Teste si objet dans cadran du haut
        if(obj->getPosY() > this->getY()) {
            // A gauche
            if (obj->getPosX() < this->getX()) {
                index = 1;
            }
            //A droite
            else {
                index = 2;
            }
        }
        
        // Test si objet dans cadran du bas
        else {
            // A gauche
            if (obj->getPosX() < this->getX()) {
                index = 3;
            }
            //A droite
            else {
                index = 4;
            }
        }
    }
    return index;
}

void Quadtree::insertBloc(Bloc obj) {
    int index = this->searchLeaf(&obj);

    // Si l'objet appartient à un enfant
    if(!this->isLeaf()) {
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

    else {
        // S'il n'y a plus de place
        if(this->isFull()) {
            this->split();
            for(Bloc bloc : this->blocs) {
                this->insertBloc(bloc);
            }
            this->blocs.clear();
            this->insertBloc(obj);
        }
        else {
            this->blocs.push_back(obj);
        }
    }
}

/* Recherche blocs dans quadtree la ou se trouve obj */
std::vector<Bloc> Quadtree::searchBloc(Bloc* obj){

    if(!this->isLeaf()) {
        // Teste si objet dans cadran du haut
        if(obj->getPosY() > this->getY()) {

            // A gauche
            if(obj->getPosX() < this->getX()) {
                return this->upleft->searchBloc(obj);
            }

            // A droite
            else {
                return this->upright->searchBloc(obj);
            }
        }
        
        // Test si objet dans cadran du bas
        else {
            // A gauche
            if(obj->getPosX() < this->getX()) {
                return this->downleft->searchBloc(obj);
            }

            // A droite
            else {
                return this->downright->searchBloc(obj);
            }
        }
    }
    return this->blocs;
}

/* Collisions */
