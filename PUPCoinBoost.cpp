//
// Created by david on 09.06.2023.
//

#include "PUPCoinBoost.h"
#include "world.h"
#include "cstdlib"

PUPCoinBoost::PUPCoinBoost(int duration) {
    boostDuration = duration;
}

PUPCoinBoost::~PUPCoinBoost() {
}


//calculate the amount of Coinboost a player gets
void PUPCoinBoost::setBoostAmount(int round, int currentCoins) { //not my proudest function but it works might want to find a function for that
    boostAmount = 1;
    if(active) {
        boostAmount = (round / currentCoins);
        if (boostAmount < 1){
            boostAmount = 1;
        } else if (boostAmount > 3) {
            boostAmount = 3;
        } else boostAmount = 1;
    }
}

int PUPCoinBoost::getActive() {
    return active;
}

int PUPCoinBoost::getBoostAmount() {
    return boostAmount;
}

void PUPCoinBoost::setDuration(int duration) {
    boostDuration = duration;
}

void PUPCoinBoost::givePlayerCoins(player &actPlayer) { //call when player picks up PUP, gives set amount of coins instantly
    if(actPlayer.getCoins() + blessing != world::goal) {
        actPlayer.incCoins(blessing);
    }
}

void PUPCoinBoost::generateRandomBlessing() {
    int blessingAmount = (rand() & 3) + 1;
    blessing = blessingAmount;
}


