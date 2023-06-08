//
// Created by david on 08.06.2023.
//

#ifndef PARADPROJEKT_MASTER_CAMELADULT_H
#define PARADPROJEKT_MASTER_CAMELADULT_H
#include "Camel.h"

class CamelAdult:public Camel {
public:
    CamelAdult() : Camel(xGlo, yGlo){}
    int age = 50;
};


#endif //PARADPROJEKT_MASTER_CAMELADULT_H
