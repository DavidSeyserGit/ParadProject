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
        if(finished){
            int answer;
            cout << "Do you want to continue to endless mode ? ";
            cin >> answer;
            if(answer == static_cast<int>('Y') || answer == static_cast<int>('y') || answer == 1){
                w1.setEndlessMode();
                finished = false;
            }
        }
    }

    return 0;
}