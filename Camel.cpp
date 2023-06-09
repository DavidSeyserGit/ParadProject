//
// Created by david on 07.06.2023.
//

#include "Camel.h"


void Camel::init (){
    age = 0;
}

Camel::Camel(int gloX, int gloY) {
    init();
    xGlo = gloX;
    yGlo = gloY;
}
Camel::~Camel(){
}



bool Camel::playerDetection(int PlayerX, int PlayerY){
    if(getXglo() == PlayerX && getYglo() == PlayerY)
        return true;
    else
        return false;
}
