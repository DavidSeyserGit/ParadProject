#include <iostream>
#include "player.h"
#include "world.h"
#include <ctime>
using namespace std;


int main() {
    srand(time(nullptr));
    bool finished = false;

    player actPlayer1("Number_1");
    //player actPlayer2("Number_2");
    world actWorld;

    while (!finished) {
        //finished = (actWorld.menu(actPlayer1) || actWorld.menu(actPlayer2)) ;
        finished = actWorld.menu(actPlayer1);

        while (finished) {
            char answer;
            cout << "Do you want to continue to endless mode ?  y/n :";
            if (std::cin >> answer && (answer == 'y' || answer == 'n')) {
                if (answer == 'y') {
                    actWorld.setEndlessMode();
                    finished = false;
                }
                break;
            }
            else {
                cout << "check input !" << endl; //--- this is also not clean
                std::cin.clear();
            }
        }
    }

    return 0;
}