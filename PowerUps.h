//
// Created by david on 09.06.2023.
//

#ifndef PARADPROJEKT_MASTER_POWERUPS_H
#define PARADPROJEKT_MASTER_POWERUPS_H


class PowerUps {
public:
    virtual ~PowerUps(){};
    void setActive();


protected://duration of the PowerUp
    virtual void setDuration(int) = 0;

    int duration;
    bool active;
};


#endif //PARADPROJEKT_MASTER_POWERUPS_H
