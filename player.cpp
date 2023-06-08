//
// Created by rapha on 05.04.2023.
//

#include "player.h"
#include <iostream>

using namespace std;

void player::init(){
    //cout << "Player Default" << endl; would like to write to "warning"
    xCoord = 0;
    yCoord = 0;
    charNam = "EMPTY";
    xCoordPa = 0;
    yCoordPa = 0;
    myCoins = 10;
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
            cout << "w, a, s, d  :  ";
            if (std::cin >> inp) break;
            else {
                std::cin.clear();
            }
        }
        cout << endl;

        if(inp == 'w') --yCoord;
        if(inp == 'a') --xCoord;
        if(inp == 's') ++yCoord;
        if(inp == 'd') ++xCoord;
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
    if(yCoordPa < 0) yCoordPa = 0;
    if(xCoordPa < 0) xCoordPa = 0;
    if(yCoordPa > 4) yCoordPa = 4;
    if(xCoordPa > 4) xCoordPa = 4;
}
void player::setSatiatedValue(bool satiation, int actRound) { //gets the value from Camel::playerDetection -> Ture : player detected -> player satiated
    static int munchTime = 0; //round in which camel gets feeded to player
    if (satiation) {
        satiated = satiation;
        munchTime = actRound;
    }
    if((actRound - munchTime) >= 6 && satiated){
        satiated = false;
    }

}