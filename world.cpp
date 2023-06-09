//
// Created by rapha on 05.04.2023.
//

#include "world.h"
#include "player.h"
#include "patch.h"
#include "entities.h"
#include "PowerUps.h"
// #include <windows.h>   // WinApi header for output
#include <iostream>
#include <ctime>

using namespace std;
const int world::goal = 30;
//created a fixed PowerUp to test out functions and the program
PUPCoinBoost coinBoostPUP(1,1);

// constructor
// map gen by patch construction 5x5 patches with 3x3 fields so 5x3 = 15x15 playing field -> done in world.h and patch.cpp
// currently all sizes are set and are not made variable (e.g. by using size init var.s)
world::world(){
    gloCamels = 0;
    gloCoins = 0;
    endlessMode = false;
    // count coins and init camelpos
    for(int x = 0; x < 5; x++){
        for(int y = 0; y < 5; y++){
            camelPos[y][x] = false;         //set camel positions to false (no camels present on launch)
            if(! wPatch[y][x].getIsOasis()) gloCoins++;     // since every desert patch gets a coin on init -> glo coins increase
        }
    }
}
// destructor
world::~world(){}
void world::printMap(player& actPlayer){
    cout << endl;
    for(int paY = 0; paY < 5; paY++){           //iter over patch y
        for(int row = 0; row < 3; row++){       //iter over local row
            for(int paX = 0; paX < 5; paX++){   //iter over patch x
                //checks if player pos on curr patch (row -> then passes x|column -pos)
                if(actPlayer.getXglo() == paX && actPlayer.getYglo() == paY && actPlayer.getYloc() == row)
                    wPatch[paY][paX].printRow(row, actPlayer.getXloc(), 0); //passes x pos of player
                else if (camelPos[paY][paX] && row == 1)
                    wPatch[paY][paX].printRow(row, -1, 1);
                else
                    wPatch[paY][paX].printRow(row, -1,-1); //ignore player pos.
            }
            cout << endl; //next line on terminal -> next row from patches of curr y-pos (paY)
        }
    }
}
// -> static (no relation with world:: ) => port to utils:: ?
// delete -> functionality inside constr patch
bool world::dice( int percentage){
    return rand()%100 < percentage;
}
// displays the action menu to the player
//  -> in the future it will have to be a more advanced logic
bool world::menu(player &actPlayer) {
    int choice = -1;

    int inOasis = wPatch[actPlayer.getYglo()][actPlayer.getXglo()].getIsOasis(); //check if player is in oasis
    int gloCamels = CamelVec.size(); //größe des vektors

    printMap(actPlayer);

    if(inOasis && actPlayer.getCoins() >= 2){       // only if player is in an Oasis and has more than 2 coins allow to build
        cout << "[0] move \t\t\t" << "current money: " << actPlayer.getCoins() <<"$" << endl;
        cout << "current position \t\t x | y: "     << actPlayer.getXloc() + 3*actPlayer.getXglo() << " | "
             << actPlayer.getYloc() + 3*actPlayer.getXglo() << endl;
        cout << "[1] build \t\t\t"  << "oasis fields: "
             << wPatch[actPlayer.getXglo()][actPlayer.getYglo()].getFields() << endl; // what does this do again ...
        /*
         * prototype was already changed
         * maybe add fun game design for menu with win.h
         * --------------------------------------------
         * [0] move                 current money: x $
         * [1] build                current paIncome +/- x $ per round -> where to put this function ... and how to calculate
         * position xPa yPa xloc(+1 ?) yloc -> if interesting also calculated global x|y -> "(xPa) * 3 + xloc (if(xPa>0) +1)"
         * --------------------------------------------
        */
        while(choice != 1 && choice != 0){
            string tempChoice = " ";
            cout << "choice:  ";
            cin >> tempChoice;
            choice = static_cast<int>(tempChoice[0]) - 48;  //this is dirty as f*ck (ascii "0" = 48 , "1" = 49)
            //cout << "\t inpu: " << choice << endl; --- debugging
            cin.clear();
            cout << endl;
        }
    } else {	//auto move select on no money or !oasis
        cout << "selected \"[move]\" since player is not in an oasis or has no money\n" << "\t\t current money: " << actPlayer.getCoins() <<"$" << endl;
        cout << "current position \t\t x | y: "     << actPlayer.getXloc()+1 + 3*actPlayer.getXglo() << " | "
             << actPlayer.getYloc()+1 + 3*actPlayer.getYglo() << endl;
        choice = 0;
    }

    //uses int rounding 0 - (max) 24 camels -> 12 -(0 - 12) chance-% => the more camels the lower chance
    int chance = 30 - gloCamels / 2; //could be changed in dependency to difficulty modifier
    if (dice(chance))
        EntitySpawn();

    interact(actPlayer, choice, coinBoostPUP );
    if (gloCoins < 35) coinRegen();       // would like to use "35" -> this->goal / 2 + x (x=10) -> could be changed in dependency to difficulty modifier

    if(!endlessMode){
        if(actPlayer.getCoins() >= goal){
            cout << "You won !" << endl << "Congratulations !" << endl;
            return true;
        }
        if(actPlayer.getCoins() < 0){
            cout << "You lost !" << endl << "Better luck next time !" << endl;
            return true;
        }
    }
    return false; // nothing happens -> game continues
}

// interaction with world menu passes choice -> 0=move 1=build
void world::interact(player &actPlayer, int choice,PUPCoinBoost &coinBoostPUP){
    int static moves = 0;//more or less round counter
    moves++;
    //every sixth move player needs to buy food -> could be changed in dependency to difficulty modifier
    if(!(moves % 6)){
        if( !actPlayer.getSatiatedValue()) actPlayer.incCoins(-2);
        actPlayer.incCoins(actPlayer.getIncome());
    }

    switch(choice){
        default:
            cout << "You should not be in here .... what did you do? \n ERROR world::interact" << endl;
            break;

        case 0:
            actPlayer.move();
            // tells wPatch where player is and asks if player is on a coin -> collects it -> increase player money
            if(wPatch[actPlayer.getYglo()][actPlayer.getXglo()].getCoin(actPlayer.getXloc(),actPlayer.getYloc())){
                //if player picked up a CoinBoostPUP he now gets more money per coin
                actPlayer.incCoins(1 * coinBoostPUP.getBoostAmount());
                gloCoins--;
            }
            //-> check player and camel -> return boolean true = "is on me"
            actPlayer.setSatiatedValue(CamelDetect(actPlayer), moves);
            break;
        case 1:
            char answer;
            do{
                int price = 0;  // to reset last price
                answer = 'n';   // to reset last answer
                patch *actPatch = &wPatch[actPlayer.getYglo()][actPlayer.getXglo()];    //points to patch player is standing on
                price = (*actPatch).build(actPlayer.getCoins());   //opens build menu which returns price for ordered building
                actPlayer.incCoins(price);          //lowers player money
                actPlayer.setIncome(calculateIncome());


                //since build menu returns "0" (false) if no building is build it is assumed, that player does not want to continue building
                while(price){ // --- no user input check implemented
                    cout << "Do you want to build another building? [y/n]:  ";
                    if (std::cin >> answer && (answer == 'y' || answer == 'n'))
                        break;
                    else {
                        cout << "check input !" << endl; //--- this is also not clean
                        std::cin.clear();
                    }
                }
            }while(answer == 'y');
            break;
    }
}

// generates coins on a patch while not causing overflows
void world::coinRegen() {
    bool hasSpace = false; //if 9/9 gloCoins in a patch -> to get loop going and wait on return of addCoin()
    do {
        int rand1 = rand() % 5; // generates values between 0 and 4
        int rand2 = rand() % 5;
        if ( ! wPatch[rand1][rand2].getIsOasis()) // patch pointing to is not an oasis do...
            hasSpace = wPatch[rand1][rand2].addCoin();
    } while (!hasSpace);     // something wrong
    gloCoins++;
}

void world::EntitySpawn(){
    int cnt = 0;
    bool hasEntity = false;

    do{
        cnt++;
        int rand1 = rand() % 5; // generates values between 0 and 4
        int rand2 = rand() % 5;
        if(!(wPatch[rand2][rand1].getIsOasis())){
            for(Camel* camel : CamelVec){
                int CamelPosX = camel->getXglo();
                int CamelPosY = camel->getYglo();

                if (CamelPosX == rand1 && CamelPosY == rand2){
                    hasEntity = true;
                    break;
                }
            }
            if(!hasEntity){
                auto* camel1 = new Camel(rand1, rand2); // Camel(x, y)
                CamelVec.push_back(camel1);             // inserts new camel address into vector
                camelPos[rand2][rand1] = true;         // array pos is alwys arr[y][x]
            }
        }
        if(cnt > 20){
            break;
        }
    }while(hasEntity);
}

bool world::CamelDetect(player& actplayer) {
    for (auto it = CamelVec.begin(); it != CamelVec.end(); ++it) {
        Camel* camel = *it;
        int CamelPosX = camel->getXglo();
        int CamelPosY = camel->getYglo();

        if (CamelPosX == actplayer.getXglo() && CamelPosY == actplayer.getYglo()) { //everytime the player is on the same patch as the camel it gets deleted
            cout << "\n Player ate a camel... Jummy ... saturated for 6 rounds" << endl;    // could later be changed to "rounds" instead of "6"
            delete camel;              //camel delete on current gloX && gloY
            camelPos[CamelPosY][CamelPosX] = false;
            CamelVec.erase(it); //camel pointer deleted
            return true;
        }
    }
    return false;
}

int world::calculateIncome(){
    int sum = 0;
    for(int y = 0; y < 5; y++){
        for(int x = 0; x < 5; x++){
            sum += wPatch[y][x].getIncome();
        }
    }
    return sum;
}

void world::PUPCoinBoostSpawn() { //can be further modified to spawn every possible PowerUp not only CoinBoosts
    bool hasCoinBoost;
    int rand1 = rand() % 5; // generates values between 0 and 4
    int rand2 = rand() % 5;

    if (!(wPatch[rand2][rand1].getIsOasis())) {
        for (PUPCoinBoost *boost: CoinBoostVec) {
            int BoostPosX = boost->getXGlo();
            int BoostPosY = boost->getYGlo();

            if (BoostPosX == rand1 && BoostPosY == rand2) {
                hasCoinBoost = true;
                break;
            }
        }
        if (!hasCoinBoost) {
            auto *coinBoost = new PUPCoinBoost(rand1, rand2);
            CoinBoostVec.push_back(coinBoost);
        }
    }
}

bool world::CoinBoostDetect(player& actplayer){ //can be further modified to detect every possible PowerUp not only CoinBoosts
    for (auto it = CoinBoostVec.begin(); it != CoinBoostVec.end(); ++it) {
        PUPCoinBoost* boost = *it;
        int BoostPosX = boost->getXGlo();
        int BoostPosY = boost->getYGlo();

        if (BoostPosX == actplayer.getXglo() && BoostPosY == actplayer.getYglo()) { //everytime the player is on the same patch as the camel it gets deleted// could later be changed to "rounds" instead of "6"
            delete boost;              //camel delete on current gloX && gloY
            CoinBoostVec.erase(it); //camel pointer deleted
            return true;
        }
    }
    return false;
}