#include <iostream>
#include "player.h"
#include "world.h"
#include <ctime>
using namespace std;
player actPlayer("Number_1");
world w1;
int main() {
    srand(time(nullptr));
    bool finished = false;

    //w1.temp_PrintMap(actPlayer);

    for(int i = 0; i < 10; i++){
        w1.menu(actPlayer);
    }

    //while(!finished){
    //    finished = w1.menu(actPlayer);
    //}

    return 0;
}