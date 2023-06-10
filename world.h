//
// Created by rapha on 05.04.2023.
// last edit: 11.06.2023

#ifndef PARADProjekt_WORLD_H
#define PARADProjekt_WORLD_H

#include <iostream>
#include "patch.h"
#include "player.h"
#include "entities.h"
#include "PowerUps.h"
#include <vector>
using namespace std;

class world {
public:
    world();
    virtual ~world();

    void printMap(player& actPlayer);
    bool dice(int);             // dice on isOasis and hasCoin and ...
    bool menu(player &actPlayer);           // with function pointer ? ->to move interact etc.
    void interact(player &actPlayer, int, PUPCoinBoost& coinBoostPUP);    // for interacting with a patch
    void coinRegen();           // gets global value and
    void EntitySpawn();
    bool CamelDetect(player& actplayer);
    void PUPCoinBoostSpawn();
    bool CoinBoostDetect(player& actplayer);
    int calculateIncome();
    void setEndlessMode(){endlessMode = true;}
    static const int goal; //player coin goal -> could be changed in dependency to difficulty modifier
protected:

    patch wPatch[5][5];
    vector<Camel*> CamelVec;
    vector<PUPCoinBoost*> CoinBoostVec;//
    int gloCoins;           //global gloCoins
    int gloCamels;
    bool camelPos[5][5];    //shows true on global map if camel is present
    bool endlessMode;
};

#endif //PARADProjekt_WORLD_H