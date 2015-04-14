#ifndef RUSTMAP_H_INCLUDED
#define RUSTMAP_H_INCLUDED

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct neighborhood_{
    vector<int> min_bounds; //sets up the sizes of the maps
    vector<int> max_bounds; //and the positions
    vector<string> monsters;
    void init(int x_min, int x_max, int y_min, int y_max){
        min_bounds.push_back(x_min);
        min_bounds.push_back(y_min);
        max_bounds.push_back(x_max);
        max_bounds.push_back(y_max);
    }
}neighborhood;

struct park_{
    vector<int> min_bounds;
    vector<int> max_bounds;
    vector<string> monsters;
    void init(int x_min, int x_max, int y_min, int y_max){
        min_bounds.push_back(x_min);
        min_bounds.push_back(y_min);
        max_bounds.push_back(x_max);
        max_bounds.push_back(y_max);
    }
}park;

struct factory_{
    vector<int> min_bounds;
    vector<int> max_bounds;
    vector<string> monsters;
    void init(int x_min, int x_max, int y_min, int y_max){
        min_bounds.push_back(x_min);
        min_bounds.push_back(y_min);
        max_bounds.push_back(x_max);
        max_bounds.push_back(y_max);
    }
}factory;

struct junkyard_{
    vector<int> min_bounds;
    vector<int> max_bounds;
    vector<string> monsters;
    void init(int x_min, int x_max, int y_min, int y_max){
        min_bounds.push_back(x_min);
        min_bounds.push_back(y_min);
        max_bounds.push_back(x_max);
        max_bounds.push_back(y_max);
    }
}junkyard;

struct obstacles_{
    int x_size; //the size of the object
    int y_size;
    int z_size;
    int x_position; //the position of the object
    int y_position;
    bool breakable; //for objects such as boxes
    void init(int x, int y, int z, int x_pos, int y_pos, bool break_){
        x_size = x;
        y_size = y;
        z_size = z;
        x_position = x_pos;
        y_position = y_pos;
        breakable = break_;
    }
};

void init_map(){
    neighborhood.monsters.push_back("humanoid1");
    neighborhood.monsters.push_back("humanoid2");
    neighborhood.monsters.push_back("burrower");
    neighborhood.init(0, 127, 0, 127);

    park.monsters.push_back("statue");
    park.monsters.push_back("burrower");
    park.init(128, 255, 0, 127);

    factory.monsters.push_back("owner");
    factory.monsters.push_back("dog1");
    factory.monsters.push_back("dog2");
    factory.monsters.push_back("dog3");
    factory.monsters.push_back("burrower");
    factory.init(65, 155, 128, 218);

    junkyard.monsters.push_back("scientist");
    junkyard.init(0, 64, 128, 192);

    obstacles_ box;
    box.init(1, 1, 1, 1, 1, true);
}

#endif // RUSTMAP_H_INCLUDED
