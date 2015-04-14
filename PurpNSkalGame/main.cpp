#include <iostream>
#include <windows.h>
#include <time.h>

/*
I'm gonna write a bunch of misc. notes and thoughts about the game logic up here when
it doesn't belong in the code itself

I decided to make men and women mechanics work different (jumping, etc) because
I wanted men and women to be represented realistically, which I believe is more
fair than making them operate equally. This will give male characters some
advantages, and will do the same for female characters. I will not be adding
trans-gender characters, nor anything of that sort because I do not feel the players
will feel it is appropriate.

*/

#define block 5 //set one block to 5x5 --->inches<----
#define male_jump_height 4 //4 block jump height
#define female_jump_height 3 //3 block jump height
#define male_weight 196 //males weigh 196lbs
#define female_weight 156 //femakes weigh 156
#define player_height 3 //player height
#define player_width 3 //player width

#define all_items 100 //how many total ITEMS (player, mob, block, etc) will be in the game

#define PLAYER 0 //the player object index at everything[0]
#define PLAYER_TYPE 0 //player type index at everything[0][0]
#define PLAYER_HEALTH 1 //player health index at everything[0][1]
#define PLAYER_X_POS 2 //player x position index at everything[0][2]
#define PLAYER_Y_POS 3 //player y position index at everything[0][3]

using namespace std;

int player_jump(int jump_height);
int player_fall();
int update(int index, int attribute, int amount);

int everything[all_items][4]; //100 objects, assuming each object has a max of 4 properties
//first 10 objects (0-9) are player-related, object 0 is the player itself
//objects 10-19 are mob-related
//objects 20-99 are world-related (array starts at 0, so index 100 is out-of-bounds)
//note: THIS ARRAY WILL BE EXPANDED, A LOT

int update(int index, int attribute, int amount){
    if(index > 100 || index < 0){
        return -1;
    }
    if(attribute > 4 || attribute < 0){
        return -2;
    }
    everything[index][attribute] += amount;
    return 0;
}

int player_jump(int jump_height){ //jump UP only
    int jumped = 0; //how far the player has jumped so far
    while(jumped < jump_height){
        int curr_x = everything[PLAYER][PLAYER_X_POS]; //player's current x position
        int next_y = everything[PLAYER][PLAYER_Y_POS]+1; //y position player will enter
        if(everything[curr_x][next_y] > 0){ //blocks in the world are referenced by [x_pos][y_pos]
            player_fall(); //if the block is greater than 0, it is not a background piece, so the player stops
        }
        else{ //else if the space is empty
            if(update(PLAYER, PLAYER_Y_POS, 1)){ //the player jumps 1 space
                jumped++;
                Sleep(0.001); //I'm not yet sure how fast to make the player jump
                //acceleration mechanic:
                //this sleep time will increase as player reaches max jump height
            }
            else{
                return -1; //I'll worry about error code checking later, just setting them up
            }
        }
    }
    return 0;
}

int player_fall(){ //fall DOWN only
    int fallen = 0; //how far the player has fallen so far
    while(true){ //with nothing to stop the player, they will fall forever
        int curr_x = everything[PLAYER][PLAYER_X_POS]; //player's current x position
        int next_y = everything[PLAYER][PLAYER_Y_POS]-1; //y position player will enter
        if(everything[curr_x][next_y] > 0){ //blocks in the world are referenced by [x_pos][y_pos]
            //calc_fall_damage(); //if the block is greater than 0, it is not a background piece, so the player lands
            //to be made
        }
        else{ //else if the space is empty
            if(update(PLAYER, PLAYER_Y_POS, -1)){ //the player falls 1 space
                fallen++;
                Sleep(0.001); //I'm not yet sure how fast to make the player fall
                //acceleration mechanic:
                //this sleep time will decrease as player falls further
            }
            else{
                return -1; //I'll worry about error code checking later, just setting them up
            }
       }
    }
    return 0;
}

void fill(){
    for(int x = 0; x < all_items; x++){
        if(x < 10){ //player-related
            if(x == PLAYER){ //player itself
                everything[PLAYER][PLAYER_TYPE] = 1; //type: player - male
                everything[PLAYER][PLAYER_HEALTH] = 100; //health
                everything[PLAYER][PLAYER_X_POS] = 0; //x position
                everything[PLAYER][PLAYER_Y_POS] = 0; //y position
                //following Terraria mechanics, with no weapon, you deal no damage, so no base damage
            }
            else{
                switch(x){
                    case 1: everything[x][0] = 2; //type: currently held item
                    case 2: everything[x][0] = 3; //type: armor - feet
                    case 3: everything[x][0] = 4; //type: armor - legs
                    case 4: everything[x][0] = 5; //type: armor - chest
                    case 5: everything[x][0] = 6; //type: armor - head
                    case 6: everything[x][0] = 7; //type: accesory
                    case 7: everything[x][0] = 8; //type: accesory
                    case 8: everything[x][0] = 9; //type: accesory
                    case 9: everything[x][0] = 10; //type: accesory
                }
                everything[x][1] = 100; //durability (keep this?)
                everything[x][2] = 3; //item range
                everything[x][3] = 10; //item damage
            }
        }
        else if(x < 20){ //mob-related

        }
        else{ //object-related

        }
    }
}

bool game_done = false;

int loop(){
    clock_t start = clock();
    float duration;
    while(!game_done){
        duration = (clock() - start ) / (float) CLOCKS_PER_SEC;
        if(duration >= 0.06){ //make sure each frame runs at least .06 seconds (60 times per second)
            Sleep(1);
            continue;
        }
        if((GetKeyState(VK_LEFT) & 0x80) != 0){
            if(!update(PLAYER, PLAYER_X_POS, -1)){ //update player object 1 space to the left
                cout << "Error." << endl;
            }
        }
        if((GetKeyState(VK_RIGHT) & 0x80) != 0){
            if(!update(PLAYER, PLAYER_X_POS, 1)){ //update player object 1 space to the right
                cout << "Error." << endl;
            }
        }
        if((GetKeyState(VK_SPACE) & 0x80) != 0){
            if(everything[PLAYER][PLAYER_TYPE] == 1){ //if player is MALE
                player_jump(male_jump_height); //jumps 20 inches (close to average male jump height)
            }
            else{
                player_jump(female_jump_height); //jumps 15 inches (close to average female jump height)
            }
        }

    }
    return 0;
}

int main()
{
    fill();
    loop();
    Sleep(10000);
    return 0;
}
