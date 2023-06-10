//
// Created by rapha on 05.04.2023.
// last edit: 11.06.2023

#ifndef PARADProjekt_PLAYER_H
#define PARADProjekt_PLAYER_H

#include <iostream>
using namespace std;

class player{
public:
    player();    //trying to not use this -> want charname to be instance name
    player(string);
    virtual ~player();
    void incCoins(int); // add coins from income or picking up coins to "wallet"
    void move();       //lets player move on map

    void setSatiatedValue(bool, int);               //setter for satiation when player kills camel
    bool getSatiatedValue() const {return satiated;}//getter for satiation

    void setIncome(int passedIncome){income = passedIncome;}
    int getIncome()const {return income;}
    int getCoins() const{return myCoins;}
    void incRounds() { ++rounds; }
    int getRounds(){return rounds;}

    int getXloc() const{return xCoord;}
    int getYloc() const{return yCoord;}
    int getXglo() const{return xCoordPa;}
    int getYglo() const{return yCoordPa;}
protected:
    void init(); // initializes variables to make contructor smaller
    string charNam;

    int myCoins;
    int income;
    bool satiated;
    int rounds;
    int latMeal;

    int xCoord;
    int yCoord;
    int xCoordPa;
    int yCoordPa;
};

#endif //PARADProjekt_PLAYER_H
