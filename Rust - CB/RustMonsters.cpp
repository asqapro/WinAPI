#ifndef RUSTMONSTERS_H_INCLUDED
#define RUSTMONSTERS_H_INCLUDED
#ifndef RUSTPLAYER_H_INCLUDED
#define RUSTPLAYER_H_INCLUDED

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "RustPlayer.h"
#include "RustMonsters.h"

using namespace std;

void monster_turn(){
    //check if the player is in view of any monsters
    humanoid1.check_sight();
    humanoid2.check_sight();
    burrower.check_sight();
    statue.check_sight();
    owner.check_sight();
    dog1.check_sight();
    dog2.check_sight();
    dog3.check_sight();

    humanoid1.move();
    humanoid2.move();
    burrower.move();
    dog1.move();
    dog2.move();
    dog3.move();
}

void message(){ //write and send message
    info.player(player.position, 1, pattern_of_escape, pattern_of_sighting);
    info.self(position);
    burrower.recieve(info);
}

#endif // RUSTMONSTERS_H_INCLUDED
#endif // RUSTPLAYER_H_INCLUDED
