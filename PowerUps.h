//
// Created by david on 09.06.2023.
// last edit: 11.06.2023

#ifndef PARADPROJEKT_MASTER_POWERUPS_H
#define PARADPROJEKT_MASTER_POWERUPS_H
#include "Player.h"

class PowerUps {
public:
    virtual ~PowerUps(){};
    void setActive();


protected://duration of the PowerUp
    virtual void setDuration(int) = 0;

    int duration;
    bool active;
};


class PUPCoinBoost: public PowerUps {
public:
    PUPCoinBoost(int , int);
    virtual ~PUPCoinBoost();
    void setBoostAmount(int, int);
    void setDuration(int) override;


    int getActive();
    int getBoostAmount();
    int getXGlo();
    int getYGlo();

protected:
    void givePlayerCoins(player &actPlayer);
    void generateRandomBlessing();

    int boostDuration;
    int boostAmount;
    int blessing;
    int xPos;
    int yPos;

};

#endif //PARADPROJEKT_MASTER_POWERUPS_H
