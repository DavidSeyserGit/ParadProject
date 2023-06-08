#include <iostream>
#include "player.h"
#include "world.h"
#include <ctime>
using namespace std;


int main() {
    srand(time(nullptr));
    bool finished = false;

    player actPlayer("Number_1");
    world w1;

    while(!finished){
        finished = w1.menu(actPlayer);
    }

    return 0;
}