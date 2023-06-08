//
// Created by rapha on 05.04.2023.
//

#ifndef PARADProjekt_PLAYER_H
#define PARADProjekt_PLAYER_H

#include <iostream>
using namespace std;


class player{
public:
    player();    //trying to not use this -> want charname to be instance name
    player(string);
    virtual ~player();
    void incCoins(int);
    void move();

    void setSatiatedValue(bool, int);               //setter for satiation when player kills camel
    bool getSatiatedValue() const {return satiated;}//getter for satiation

    void setIncome(int passedIncome){income = passedIncome;}
    int getIncome(){return income;}

    int getXloc() const{return xCoord;}
    int getYloc() const{return yCoord;}
    int getXglo() const{return xCoordPa;}
    int getYglo() const{return yCoordPa;}
    int getCoins() const{return myCoins;}
protected:
    void init();
    string charNam;

    int myCoins;
    int income;
    bool satiated;

    int xCoord;
    int yCoord;
    int xCoordPa;
    int yCoordPa;
};


#endif //PARADProjekt_PLAYER_H
