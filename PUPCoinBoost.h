//
// Created by david on 09.06.2023.
//

#ifndef PARADPROJEKT_MASTER_PUPCOINBOOST_H
#define PARADPROJEKT_MASTER_PUPCOINBOOST_H

#include "PowerUps.h"
#include "Player.h"

class PUPCoinBoost: public PowerUps {
public:
    PUPCoinBoost(int);
    virtual ~PUPCoinBoost();
    void setBoostAmount(int, int);
    void setDuration(int) override;
    int getActive();
    int getBoostAmount();
protected:
    void givePlayerCoins(player &actPlayer);
    void generateRandomBlessing();

    int boostDuration;
    int boostAmount;
    int blessing;

};


#endif //PARADPROJEKT_MASTER_PUPCOINBOOST_H
