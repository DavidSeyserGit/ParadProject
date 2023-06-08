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

        void temp_PrintMap(player actPlayer);
        bool dice(int);             // dice on isOasis and hasCoin and ...
        bool menu(player &actPlayer);           // with function pointer ? ->to move interact etc.
        void interact(player &actPlayer, int);    // for interacting with a patch
        void coinRegen();           // gets global value and
        void EntitySpawn();
        bool CamelDetect(player& actplayer);


        //bool checkPos(player actPlayer); --- lost thought
    protected:
    private:
        static const int goal;      // gloCoins to finish game
        patch wPatch[5][5];
        vector<Camel*> CamelVec;//
        int gloCoins;           //global gloCoins
        int gloCamels;
        bool camelPos[5][5];    //shows true on global map if camel is present
};


#endif //PARADProjekt_WORLD_H
