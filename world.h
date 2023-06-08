//
// Created by rapha on 05.04.2023.
// contains player related class and con-/ destructor
//

#ifndef PARADProjekt_WORLD_H
#define PARADProjekt_WORLD_H

#include <iostream>
#include "patch.h"
#include "player.h"
#include "Camel.h"
#include <vector>
using namespace std;

class world {
public:
    world();
    virtual ~world();

    void printMap(player& actPlayer);
    bool dice(int);             // dice on isOasis and hasCoin and ...
    bool menu(player &actPlayer);           // with function pointer ? ->to move interact etc.
    void interact(player &actPlayer, int);    // for interacting with a patch
    void coinRegen();           // gets global value and
    void EntitySpawn();
    bool CamelDetect(player& actplayer);
    int calculateIncome();
    void setEndlessMode(){endlessMode = true;}
protected:
    static const int goal;      //player coin goal -> could be changed in dependency to difficulty modifier
    patch wPatch[5][5];
    vector<Camel*> CamelVec;//
    int gloCoins;           //global gloCoins
    int gloCamels;
    bool camelPos[5][5];    //shows true on global map if camel is present
    bool endlessMode;
};


#endif //PARADProjekt_WORLD_H
