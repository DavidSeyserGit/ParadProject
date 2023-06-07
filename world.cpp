//
// Created by rapha on 05.04.2023.
//

#include "world.h"
#include "player.h"
#include "patch.h"
#include "camel.h"
// #include <windows.h>   // WinApi header for output
#include <iostream>
#include <ctime>

using namespace std;
const int world::goal = 50;
// constructor
// map gen by patch construction 5x5 patches with 3x3 fields so 5x3 = 15x15 playing field -> done in world.h and patch.cpp
// currently all sizes are set and are not made variable (e.g. by using size init var.s)
world::world(){
    gloCoins = 0;
    // loop and count coins (loc -> glo)
    for(int x = 0; x < 5; x++){
        for(int y = 0; y < 5; y++){
            if(! wPatch[y][x].getIsOasis()) gloCoins++;
        }
    }
    CamelVec.push_back(new Camel);
}
// destructor
world::~world(){}
void world::temp_PrintMap(player actPlayer){
    cout << endl;
    for(int paY = 0; paY < 5; paY++){           //iter over patch y
        for(int row = 0; row < 3; row++){       //iter over local row
            for(int paX = 0; paX < 5; paX++){   //iter over patch x
                //checks if player pos on curr patch (row -> then passes x|column -pos)
                if(actPlayer.getXglo() == paX && actPlayer.getYglo() == paY && actPlayer.getYloc() == row)
                    wPatch[paY][paX].printRow(row, actPlayer.getXloc()); //passes x pos of player
                else wPatch[paY][paX].printRow(row, -1); //ignore player pos.
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
bool world::menu(player &actPlayer, Camel camel) {
    int choice = 0;
    int inOasis = wPatch[actPlayer.getYglo()][actPlayer.getXglo()].getIsOasis();
    cout << inOasis << endl;
	if(inOasis && actPlayer.getCoins() >= 2){       // 2 = price of one field
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
		 * [1] build                current income +/- x $ per round -> where to put this function ... and how to calculate
		 * position xPa yPa xloc(+1 ?) yloc -> if interesting also calculated global x|y -> "(xPa) * 3 + xloc (if(xPa>0) +1)"
		 * --------------------------------------------
		*/
		// https://stackoverflow.com/questions/17928865/correct-way-to-use-cin-fail
		while(true){
			cout << "choice:  ";
			if (std::cin >> choice) break;
			else {
				std::cin.clear();
			}
			cout << endl;
		}
	} else {	//auto move select on no money or !oasis
		cout << "selected \"[move]\" since player is not in an oasis or has no money\n" << "\t\t current money: " << actPlayer.getCoins() <<"$" << endl;
		cout << "current position \t\t x | y: "     << actPlayer.getXloc()+1 + 3*actPlayer.getXglo() << " | "
													<< actPlayer.getYloc()+1 + 3*actPlayer.getYglo() << endl;
		choice = 0;
	}
	
    interact(actPlayer, choice, camel);
    if (gloCoins < 35) coinRegen();       // would like to use "35" -> this->goal / 2 + x (x=10) -> later controlled by difficulty modifier
    if(actPlayer.getCoins() >= goal){
        cout << "You won !" << endl << "Congratulations !" << endl;
        return true;
    }
    if(actPlayer.getCoins() < 0){
        cout << "You lost !" << endl << "Better luck next time !" << endl;
        return true;
    }
    return false; // nothing happens -> game continues
}

// interaction with world menu passes choice -> 0=move 1=build
void world::interact(player &actPlayer, int choice, Camel camel){
    int static moves = 0;
    moves++;
    //hunger_removed
    if(!(moves % 6) && !actPlayer.getSatiatedValue()) actPlayer.incCoins(-3);  //every sixth move player needs to buy food -> later controlled by difficulty modifier
    // && !actPlayer.getSatiated()

    switch(choice){
        case 0:
            actPlayer.move();
            actPlayer.setSatiatedValue(camel.playerDetection(camel ,actPlayer.getXglo(), actPlayer.getYglo()));
            // bool actPlayer.setSatiated() = camel.detect(actPlayer.getXglo(), actPlayer.getYglo());  -> check player and camel -> return boolean true = "is on me"
            //if() check coin pos in current patch and collect it ... reduce in patch memory and in global coin
            for(int paY = 0; paY < 5; paY++){           //iter over patch y
                for(int row = 0; row < 3; row++){       //iter over local row
                    for(int paX = 0; paX < 5; paX++){   //iter over patch x
                        //checks if player pos on curr patch (row -> then passes x|column -pos)
                        if(actPlayer.getXglo() == paX && actPlayer.getYglo() == paY && actPlayer.getYloc() == row)
                            wPatch[paY][paX].printRow(row, actPlayer.getXloc()); //passes x pos of player
                        else wPatch[paY][paX].printRow(row, -1); //ignore player pos.
                    }	// --- implement coin gathering !!! actPlayer.incCoins() ...
                    cout << endl; //next line on terminal -> next row from patches of curr y-pos (paY)
                }
            }
            break;
        case 1:
			/* whole while loop could be moved to "patch".build() -> is calles by pointer originating from player position
			 *-> all requests are internal 
			 * and receives as parameters player data (money ...)
			 */
			/* this is a submenu ... hooray
            * ... request player money and present menu for building like:
            * checks if enough money is available for option and prints options accordingly
            * there is potential to move or reduce this "function"
            *
            */
			int answer = -1;

            // something wrong money / bulid _> can build with not all requirements true
			while(answer){
                temp_PrintMap(actPlayer);
                bool optionIsAvailable[4] = {false,false,false,false}; 		//this exists to limit player choices depending on requirements
				int money = actPlayer.getCoins();

				patch *actPatch = &wPatch[actPlayer.getYglo()][actPlayer.getXglo()];        //--- how to write a pointer to this patch in world class

                if(!((*actPatch).getHasCity() || money < 8 || (*actPatch).getFields() < 2)) {      // option to build city is red
					cout << "[1] city \t" << "cost: 8 $ \t" << "requires min. 2 fields" << endl; // 8 $ | 2 fields -> variable instead?
					optionIsAvailable[1] = true;
				}
				if(!((*actPatch).getMills() == 2 || money < 4 || !(*actPatch).getFields())){   // option to build mills is red
					cout << "[2] mill \t" << "cost: 4 $ \t" << "requires min. 1 field" << endl;
					optionIsAvailable[2] = true;
				}
				if(!((*actPatch).getFields() == 5 || money < 2)){  // it seemed easyier to make positive logic and negating it
					cout << "[3] field \t" << "cost: 2 $ \t" << endl;
					optionIsAvailable[3] = true;
				}
				cout << "[0] nevermind (exit) \t"  << endl;
                while(true){
                    cout << "Answere:  ";
                    if (std::cin >> answer) break;
                    else {
                        std::cin.clear();
                    }
                    cout << endl;
                }
				cout << endl;
				if(optionIsAvailable[answer]){
                    (*actPatch).build(answer);
				} else if(!optionIsAvailable[1] && !optionIsAvailable[2] && !optionIsAvailable[3]) //auto exit
                    break;
                else
                    cout  << endl << "Wrong input! \t"  << endl; // --- maybe delete this -> does not fit design
			}
			
			//actPlayer. lost thought

            /* [1] city  8 $ requires min. 2 fields
            * [2] mill  4 $ requires min. 1 field
            * [3] field 2 $
            * [0] nevermind (exit) --> move instead ? so put it in loop in this func(large) or in "menu"(return value needed)
            * building menu in a loop (user input)
            * do not forget to lower player money
            * access patch and build structure
            *   func needed   --> (patch) for adding buildings
            *                 --> (patch) for checking if building is present (or just use a variable... easier)
            *                 --> (player) for player money (... already written)
            */
             break;
        /*default: // --- dows not want to work
            cout << "You should not be in here .... what did you do? \n ERROR world::interact" << endl;
            break;*/
    }
}

// generates coins on a patch while not causing overflows
//
void world::coinRegen() {
    bool hasSpace = false; //if 9/9 gloCoins in a patch -> to get loop going and wait on return of addCoin()
    do {
        int rand1 = rand() % 5; // generates values between 0 and 4
        int rand2 = rand() % 5;
        if ( ! wPatch[rand1][rand2].getIsOasis()) // patch pointing to is not an oasis do...
            hasSpace = wPatch[rand1][rand2].addCoin();
    } while (!hasSpace);     // something wrong
    this->gloCoins++;
}

//void camelSpawn()