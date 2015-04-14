#ifndef RUSTPLAYER_H_INCLUDED
#define RUSTPLAYER_H_INCLUDED

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct player_{
    vector<string> inventory;
    bool alive;
    int sight_range; //from how far away the player can spot monsters
    //counter in spaces of movement
    int speed; //how many spaces the player can move per round
    vector<int> position; //2D position of the player

    void init(int s_r, int s, int pos_x, int pos_y){
        alive = true;
        sight_range = s_r;
        speed = s;
        position.push_back(pos_x);
        position.push_back(pos_y);
    }
}player;

void init_player(){
    player.init(1, 1, 1, 1);
}

void player_turn(){
    cout << "Basic game so far. Working on monster and map setup." << endl;
    cout << "To be added: Monster AI, player choices." << endl;
    player.alive = false;
}

void player_dead(){
    cout << "Working on dead function." << endl;
}

#endif // RUSTPLAYER_H_INCLUDED
