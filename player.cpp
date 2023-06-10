//
// Created by rapha on 05.04.2023.
// last edit: 11.06.2023

#include "player.h"
#include <iostream>

using namespace std;

void player::init(){
    //cout << "Player Default" << endl; would like to write to "warning"
    xCoord = rand() % 3;
    yCoord = rand() % 3;
    charNam = "EMPTY";
    xCoordPa = rand() % 3 + 1;
    yCoordPa = rand() % 3 + 1;
    myCoins = 10;   //could be changed in dependency to difficulty modifier
    income = 0;
    rounds = 0;
    latMeal = 0;
}

player::player(){
    init();
}
player::player(string charNam_ini)
{
    init();
    charNam = charNam_ini;
}

player::~player(){}

// spending or getting coins
void player::incCoins(int addition){
    myCoins += addition;
}

// moving around ... has a separate system to "world" and "patch" ... sigh
void player::move(){
    char inp;
    int checksum = xCoord + yCoord;         // shortest way for upcoming loop
    while(checksum == (xCoord + yCoord)){
        // asking for user input ...
        while(true){
            cout << "w, a, s, d  or i, j, k, l :  ";
            if (std::cin >> inp) break;
            else {
                std::cin.clear();
            }
        }
        cout << endl;

        if(inp == 'w' || inp == 'i') --yCoord;
        if(inp == 'a' || inp == 'j') --xCoord;
        if(inp == 's' || inp == 'k') ++yCoord;
        if(inp == 'd' || inp == 'l') ++xCoord;
    }
    if(yCoord > 2){
        ++yCoordPa;
        yCoord = 0;
    }
    if(xCoord > 2) {
        ++xCoordPa;
        xCoord = 0;
    }
    if(yCoord < 0) {
        --yCoordPa;
        yCoord = 2;
    }
    if(xCoord < 0) {
        --xCoordPa;
        xCoord = 2;
    }
    if(yCoordPa < 0){
        yCoordPa = 0;
        yCoord = 0;
    }
    if(xCoordPa < 0){
        xCoordPa = 0;
        xCoord = 0;
    }
    if(yCoordPa > 4){
        yCoordPa = 4;
        yCoordPa = 2;
    }
    if(xCoordPa > 4){
        xCoordPa = 4;
        xCoord = 2;
    }
}
void player::setSatiatedValue(bool satiation, int actRound) { //gets the value from Camel::playerDetection -> Ture : player detected -> player satiated
    //round in which camel gets fed to player
    if (satiation) {
        satiated = satiation;
        latMeal = actRound;
    }
    if((actRound - latMeal) >= 6 && satiated){
        satiated = false;
    }
}