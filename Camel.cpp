//
// Created by david on 07.06.2023.
//

#include "Camel.h"

bool Camel::playerDetection(int PlayerX, int PlayerY){
    if(xGlo == PlayerX && yGlo == PlayerY){
        return true;
    } else return false;

}