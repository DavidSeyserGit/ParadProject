//
// Created by david on 07.06.2023.
//

#include "Camel.h"

Camel::Camel(int gloX, int gloY) {
    xGlo = gloX;
    yGlo = gloY;
    age = 0;
}

bool Camel::playerDetection(int PlayerX, int PlayerY){
    if(xGlo == PlayerX && yGlo == PlayerY){
        return true;
    } else return false;

}