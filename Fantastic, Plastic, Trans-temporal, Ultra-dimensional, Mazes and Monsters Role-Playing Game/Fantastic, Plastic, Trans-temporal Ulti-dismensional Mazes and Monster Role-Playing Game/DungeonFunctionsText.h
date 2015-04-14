#ifndef DUNGEONFUNCTIONSTEXT_H_INCLUDED
#define DUNGEONFUNCTIONSTEXT_H_INCLUDED

#include "DungeonFunctions.h"

/********************Dungeon Array Layout*********************\
*                  dungeon[iter] is a room                    *
*               dungeon[iter][it] is a row in a room          *
*          dungeon[iter][it][i] is a cell in a row in a room  *
\********************Dungeon Array Layout*********************/

//Objects:
//0 : Unassigned
//1 : Wall
//2 : Door
//3 : Treasure
//4 - 8 : Objects (to be defined later)
//9-14 : Friendly NPC's
//15-20 : Hostile NPC's
//Subject to change. Will be reflected in code

//Commands:
//0 - open
//1 - pick up
//2 - drop
//3 - fight
//4 - use
//5 - speak to

extern std::string objects[22];

using namespace std;


#endif // DUNGEONFUNCTIONSTEXT_H_INCLUDED
