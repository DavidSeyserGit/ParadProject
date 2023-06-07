//
// Created by rapha on 06.04.2023.
//

#include "patch.h"
#include <iostream>
#include <windows.h>   // WinApi header
using namespace std;
HANDLE  hConsole;
int patch::gloOasis = 0;

void patch::init(){
    this->isOasis = false;
    this->hasCity = false;
    this->mills = 0;
    this->fields = 0;
    this->paCoins = 0;
}
// world generates and calls this consructor for 25 times
// it is decided if it is an "oasis" or "desert + coin"
patch::patch() { //default
    init();

    if(rand()%100 < 20 && gloOasis < 5){
        isOasis = true;
        // default: filled with ' ' PLAIN
        patchMap[1][1] = OASIS;
        gloOasis += 1;
    }
    else{
        for(int y = 0; y < 3; y++){
            for(int x = 0; x < 3; x++) {
                patchMap[x][y] = DESERT;
            }
        }
        addCoin();
    }
}

//prints the current row of a patch ... is used by world::interaction
//pl.Column to print player in this row
void patch::printRow(int row, int playerColumn){
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //init console

    for(int column = 0; column < 3; column++){ //iterate over columns
        int currField = patchMap[column][row];
        if(column == playerColumn) {      //exception if column = player Position
            SetConsoleTextAttribute(hConsole, colors[PLAYER]);  // !!
            cout << symbols[PLAYER] << " ";
        }else{
            SetConsoleTextAttribute(hConsole, colors[currField]);
            cout << symbols[currField] << " ";
        }
    }
    SetConsoleTextAttribute(hConsole, 7); // reset to std-out
}


bool patch::addCoin(){
    if(paCoins == 9) return false; // has no more space (is full !!)

    int rand1, rand2;
    do{
        rand1 = rand() % 3; // should generate 0-2
        rand2 = rand() % 3;
        if(!coinMap[rand1][rand2]){           //checks for old coin pos if (this->gloCoins > 2)
            ++paCoins;
            coinMap[rand1][rand2] = true;     //save coin-pos in bool-arr
            patchMap[rand1][rand2] = COIN;    //new coin is placed on the map     !!
            return true; // is "has Space"
        }
    }while(true);
}

void patch::build(int buildtype){
    int fieldPos[5] = {0,2,0,1,2};
	switch(buildtype){
		case 1:
			hasCity = true;
            patchMap[0][0] = CITY;
			break;
		case 2:
			++mills;
            patchMap[0][mills] = MILL;
			break;
		case 3:
            if(fields < 2)
                patchMap[1][fieldPos[fields]] = FIELD;
            else
                patchMap[2][fieldPos[fields]] = FIELD;
            ++fields;
            //patchMap[0][fields] = MILL;
			break;
		default:
			cout << "Something went terribly wrong! \t you should not be here ! \n ERROR UwU patch::build" << endl;
			return;
	}
	income = hasCity * 4 + (mills * mills + 1) * fields; // difficulty modifier could be implemented here
}
