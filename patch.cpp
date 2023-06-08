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
    isOasis = false;
    hasCity = false;
    mills = 0;
    fields = 0;
    paCoins = 0;
    paIncome = 0;
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
                patchMap[y][x] = DESERT;
            }
        }
        addCoin();
    }
}

//prints the current row of a patch ... is used by world::interaction
//pl.Column to print player in this row
// entity: 0 = player, 1 = camel
void patch::printRow(int row, int playerColumn, int entity){
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //init console

    for(int column = 0; column < 3; column++){      //iterate over columns
        int currField = patchMap[row][column];
        if(column == playerColumn && entity == 0) {     //exception if column = player Position... also checks entity
            SetConsoleTextAttribute(hConsole, colors[PLAYER]);  // !!
            cout << symbols[PLAYER] << " ";
        } else if (column == 1 && entity == 1){          //if other entities exist -> change if else clauses to "=="
            SetConsoleTextAttribute(hConsole, colors[CAMEL]);  // !!
            cout << symbols[CAMEL] << " ";
        }else{                                      //if no entity -> pull field info from patchmap
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

bool patch::getCoin(int x, int y){
    if(coinMap[y][x]){
        --paCoins;
        coinMap[y][x] = false;
        patchMap[y][x] = DESERT;
        return true;
    } else
        return false;
}

//-> all requests are internal
//and receives as parameters player data (money ...)
// checks if enough money is available for option and prints options accordingly
/*            [1] city  8 $ requires min. 2 fields
            * [2] mill  4 $ requires min. 1 field
            * [3] field 2 $
            * [0] nevermind (exit)
            */
int patch::build(int playerCoins){
    int answer = -1;
    bool optionIsAvailable[4] = {true,false,false,false}; 		//this exists to limit player choices depending on requirements
    int fieldPos[5] = {0,2,0,1,2};  //helps to place buildings

    if(!(hasCity || playerCoins < prices[1] || fields < 2)){     // option to build city
        cout << "[1] city \t" << "cost: " << prices[1] << "$ \t" << "requires min. 2 fields" << endl;
        optionIsAvailable[1] = true;
    }
    if(!(mills == 2 || playerCoins < prices[2] || !fields)){      // option to build mills
        cout << "[2] mill \t" << "cost: " << prices[2] << "$ \t" << "requires min. 1 field" << endl;
        optionIsAvailable[2] = true;
    }
    if(!(fields == 5 || playerCoins < prices[3])){               // it seemed easyier to make positive logic and negating it
        cout << "[3] field \t" << "cost: " << prices[3] << "$ \t" << endl;
        optionIsAvailable[3] = true;
    }
    cout << "[0] nevermind (exit) \t"  << endl;

    if(playerCoins < 2)
        answer = 0;

    while(!((answer < 4 && answer > -1) && optionIsAvailable[answer])){
        cout << "Answer:  ";
        string temp;
        cin >> temp;
        answer = static_cast<int>(temp[0]) - 48;
        cin.clear();
        cout << endl;
    }

    switch(answer){
        case 0:     //did not use default on "0" since it s a valid answer
            break;
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
            break;
        default:
            cout << "You should not be in here .... what did you do? \n ERROR patch::build" << endl;
            break;
    }
    paIncome = hasCity * 4 + (mills * mills + 1) * fields; //could be changed in dependency to difficulty modifier
    return prices[answer];
}