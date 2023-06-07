//
// Created by david on 07.06.2023.
//

#ifndef PARADPROJEKT_MASTER_CAMEL_H
#define PARADPROJEKT_MASTER_CAMEL_H

#include "entities.h"

class Camel: public entities{
public:
    int getXglo() override {return  xGlo;}
    int getYglo() override {return yGlo;}
    bool playerDetection(int PlayerX, int PlayerY);
private:
    int xGlo = 0;
    int yGlo = 0;
    int xLoc = 1;
    int yLoc = 1;
};

#endif //PARADPROJEKT_MASTER_CAMEL_H
