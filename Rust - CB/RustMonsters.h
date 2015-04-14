#ifndef RUSTMONSTERS_H_INCLUDED
#define RUSTMONSTERS_H_INCLUDED

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "RustPlayer.h"

using namespace std;

struct message_{
    //possible player values
    vector<int> player_position; //where the player was spotted
    int direction_escaped; //direction the player escaped
    vector<int> pattern_of_escape;
    vector<int> pattern_of_sighting;
    void player(vector<int> pos, int dir_escp, vector<int> pat_escp, vector<int> pat_spot){ //information concerning the player
        player_position = pos;
        direction_escaped = dir_escp;
        pattern_of_escape = pat_escp;
        pattern_of_sighting = pat_spot;
    }
    //monster values
    vector<int> position;
    void self(vector<int> pos){ //information about the sender
        position = pos;
    }
};

struct humanoid_{
    //create the variables *variables organized in order thought of*
    vector<int> min_bounds; //how far the monster can roam
    vector<int> max_bounds; //restricts them to maps
    int speed; //how much the monster can move every turn, counted in spaces
    int sight_range; //from how far the monster can spot the player, counted in spaces of movement
    vector<int> position; //2D position of the monster
    int player_distance; //the distance between the monster and the player
    bool player_sighted;
    int player_position; //where the player was last sighted
    int move_direction; //where the monster is moving next
    message_ info; //the monster's messageboard; modified as the game progresses
    vector<int> pattern_of_escape; //is there a certain way the player escapes?
    vector<int> pattern_of_sighting; //is there certain places the player appears?

    //set the variables
    void init(int x_min, int x_max, int y_min, int y_max, int s, int s_r, int pos_x, int pos_y){
        min_bounds.push_back(x_min);
        min_bounds.push_back(y_min);
        max_bounds.push_back(x_max);
        max_bounds.push_back(y_max);
        speed = s;
        sight_range = s_r;
        position.push_back(pos_x);
        position.push_back(pos_y);
    }
    void move(){
        move_direction = rand() % 4 + 1; //a random cardinal direction
        switch(move_direction){
            case 1: //move north
                position[2] += speed;
            case 2: //move east
                position[1] += speed;
            case 3: //move south
                position[2] -= speed;
            case 4: //move west
                position[1] -= speed;
        }
    }
    void check_sight(){
        //calculate the distances between the monsters and the player
        player_distance = abs(position[1] - player.position[1]);
        player_distance += abs(position[2] - player.position[2]);
        if(player_distance < sight_range){ //if the player is in range, they are seen
            player_sighted = true;
            player_position = player.position[1];
            player_position = player.position[2];
        }
    }

}humanoid1, humanoid2;

struct burrower_{
    //*burrower can travel into/ out of any map, and underground
    //*so no limits
    int speed;
    int sight_range;
    vector<int> position; //burrower can travel underground 1 space, does not affect sight
    int player_distance;
    bool player_sighted;
    int move_direction;
    message_ info;

    void init(int s, int s_r, int pos_x, int pos_y, int pos_z){
        speed = s;
        sight_range = s_r;
        position.push_back(pos_x);
        position.push_back(pos_y);
        position.push_back(pos_z);
    }
    void move(){
        move_direction = rand() % 5 + 1; //a random cardinal direction, z axis added for the burrower
        switch(move_direction){
            case 1: //move north
                position[2] += speed;
            case 2: //move east
                position[1] += speed;
            case 3: //move south
                position[2] -= speed;
            case 4: //move west
                position[1] -= speed;
            case 5: //move up/ down
                if(position[3] < 0){ //0 being ground level
                    position[3] += 1;
                }
                else{
                    position[3] -= 1;
                }
        }
    }
    void check_sight(){
        //calculate the distances between the monsters and the player
        player_distance = abs(position[1] - player.position[1]);
        player_distance += abs(position[2] - player.position[2]);
        if(player_distance < sight_range){ //if the player is in range, they are seen
            player_sighted = true;
        }
    }
    void message(){

    }
    void recieve(message_ newInfo){
        info = newInfo;
    }
}burrower;

struct statue_{
    vector<int> min_bounds;
    vector<int> max_bounds;
    int speed;
    int sight_range;
    vector<int> position;
    int player_distance;
    bool player_sighted;
    int move_direction;

    void init(int x_min, int x_max, int y_min, int y_max, int s, int s_r, int pos_x, int pos_y){
        min_bounds.push_back(x_min);
        min_bounds.push_back(y_min);
        max_bounds.push_back(x_max);
        max_bounds.push_back(y_max);
        speed = s;
        sight_range = s_r;
        position.push_back(pos_x);
        position.push_back(pos_y);
    }
    void move(){
        move_direction = rand() % 4 + 1; //a random cardinal direction
        switch(move_direction){
            case 1: //move north
                position[2] += speed;
            case 2: //move east
                position[1] += speed;
            case 3: //move south
                position[2] -= speed;
            case 4: //move west
                position[1] -= speed;
        }
    }
    void check_sight(){
        //calculate the distances between the monsters and the player
        player_distance = abs(position[1] - player.position[1]);
        player_distance += abs(position[2] - player.position[2]);
        if(player_distance < sight_range){ //if the player is in range, they are seen
            player_sighted = true;
        }
    }
}statue;

struct factory_owner{
    //the factory owner does not move, no need to set bounds or speed
    int sight_range;
    vector<int> position;
    int player_distance;
    bool player_sighted;

    void init(int s_r, int pos_x, int pos_y){
        sight_range = s_r;
        position.push_back(pos_x);
        position.push_back(pos_y);
    }
    void check_sight(){
        //calculate the distances between the monsters and the player
        player_distance = abs(position[1] - player.position[1]);
        player_distance += abs(position[2] - player.position[2]);
        if(player_distance < sight_range){ //if the player is in range, they are seen
            player_sighted = true;
        }
    }
}owner;

struct dog_{
    vector<int> min_bounds;
    vector<int> max_bounds;
    int speed;
    int sight_range;
    vector<int> position;
    int player_distance;
    bool player_sighted;
    int move_direction;

    void init(int x_min, int x_max, int y_min, int y_max, int s, int s_r, int pos_x, int pos_y){
        min_bounds.push_back(x_min);
        min_bounds.push_back(y_min);
        max_bounds.push_back(x_max);
        max_bounds.push_back(y_max);
        speed = s;
        sight_range = s_r;
        position.push_back(pos_x);
        position.push_back(pos_y);
    }
    void move(){
        move_direction = rand() % 4 + 1; //a random cardinal direction
        switch(move_direction){
            case 1: //move north
                position[2] += speed;
            case 2: //move east
                position[1] += speed;
            case 3: //move south
                position[2] -= speed;
            case 4: //move west
                position[1] -= speed;
        }
    }
    void check_sight(){
        //calculate the distances between the monsters and the player
        player_distance = abs(position[1] - player.position[1]);
        player_distance += abs(position[2] - player.position[2]);
        if(player_distance < sight_range){ //if the player is in range, they are seen
            player_sighted = true;
        }
    }
}dog1, dog2, dog3;

void init_monsters(){
    //create humanoids
    humanoid1.init(0, 127, 0, 127, 1, 5, 68, 22);
    humanoid2.init(0, 127, 0, 127, 1, 5, 20, 75);

    //create burrower
    burrower.init(1, 5, 1, 15, 129);

    //create statue
    statue.init(128, 255, 0, 127, 1, 5, 182, 63);

    //create factory owner
    owner.init(5, 97, 192);

    //create dogs
    dog1.init(65, 155, 128, 218, 1, 5, 85, 170);
    dog2.init(65, 155, 128, 218, 1, 5, 81, 207);
    dog3.init(65, 155, 128, 218, 1, 5, 126, 202);
}

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

#endif // RUSTMONSTERS_H_INCLUDED
