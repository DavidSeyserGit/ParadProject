//
// Created by david on 07.06.2023.
//

#include "Camel.h"
#include "CamelAdult.h"
Camel::Camel(int gloX, int gloY) {
    xGlo = gloX;
    yGlo = gloY;
    age = 0;
}
bool entities::playerDetection(int PlayerX, int PlayerY){
    if(getXglo() == PlayerX && getYglo() == PlayerY){
        return true;
    } else return false;

}
