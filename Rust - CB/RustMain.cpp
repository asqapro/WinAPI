#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "RustMap.h"
#include "RustMonsters.h"
#include "RustPlayer.h"

using namespace std;

struct easter_eggs{
    string h_sqaure;
    void hatch_eggs(){
        h_sqaure = "a sqaure";
    }
};

int main(){
    srand(time(NULL)); //Seed the random number generator
    init_monsters(); //set up the values for the monsters
    init_player();  //set up the values for the player

    while(player.alive){ //main loop
        player_turn(); //player actions
        monster_turn(); //monster actions
    }
    player_dead();
    return 0; //Program ends
}

