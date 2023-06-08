//
// Created by david on 07.06.2023.
//

#ifndef PARADPROJEKT_MASTER_CAMEL_H
#define PARADPROJEKT_MASTER_CAMEL_H

#include "entities.h"

class Camel: public entities{
public:
    Camel(int, int);
    virtual ~Camel();
    int getXglo() override {return  xGlo;}
    int getYglo() override {return yGlo;}
    int getAge() {return age;};
    bool playerDetection(int PlayerX, int PlayerY) override;
protected:
    int xGlo;
    int yGlo;
    const int xLoc = 1;
    const int yLoc = 1;
    int age;
};

#endif //PARADPROJEKT_MASTER_CAMEL_H
