#include "pattern.hh"


void parseFile(){
    std::ifstream file("map.data");
    std::string str;
    printf("Debut du chargement des données\n");
    while (std::getline(file, str)){
        printf("%s", str.c_str());
    }
}