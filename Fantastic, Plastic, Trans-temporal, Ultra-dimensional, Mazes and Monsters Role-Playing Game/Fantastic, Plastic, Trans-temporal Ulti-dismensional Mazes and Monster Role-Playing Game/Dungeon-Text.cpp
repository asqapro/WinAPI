#include "Headers.h"
#include "DungeonFunctionsText.h"

using namespace std;

string objects[] = {"", "wall", "door", "chest",
                    "desk", "book", "sword", "dagger", "torch", "shield",
                    "bouncing blob", "human", "lobster", "elephant", "dwarf", "pixie",
                    "chest", "ooze", "bat", "dwarf", "spider", "goblin"};

map< vector<int>, vector<int> > createConnections(vector< vector< vector<int> > > dungeonTemp){
    vector< vector<int> > doors;
    //doors holds all 3D values that correspond to dungeon doors
    for(unsigned int iter = 0; iter < dungeonTemp.size(); iter++){ //loop through each room
        for(unsigned int it = 0; it < dungeonTemp[iter].size(); it++){ //loop through rows
            for(unsigned int i = 0; i < dungeonTemp[iter][it].size(); i++){ //loop through cells
                if(dungeonTemp[iter][it][i] == 2){ //if space is a door
                    vector<int> temp;
                    temp.push_back(iter);
                    temp.push_back(it);
                    temp.push_back(i);
                    temp.push_back(-1);
                    doors.push_back(temp); //save that spot in doors, add -1 to signify no connection
                }
            }
        }
    }
    map< vector<int>, vector<int> > connections; //map of vectors because door positions saved as (room, row, cell)
    for(unsigned int iter = 0; iter < doors.size(); iter++){ //loop through each door
        if(doors[iter][3] == -1){ //no connection yet
            int randDoor = rand() % doors.size() + 0;
            //create a pair of two doors in connections
            doors[iter][3] = 1; //mark door as connected
            doors[randDoor][3] = 1; //mark door as connected
            connections[doors[iter]] = doors[randDoor];
            connections[doors[randDoor]] = doors[iter];
        }
    }
    return connections;
}

vector< vector< vector< int> > > createDoors(vector< vector< vector<int> > > dungeonTemp){
    for(unsigned int iter = 0; iter < dungeonTemp.size(); iter++){ //loop through each room
        for(unsigned int it = 1; it < dungeonTemp[iter][0].size()-1; it++){ //first row
            if(rand() % dungeonTemp[iter][0].size() + 1 == 1){ //random chance
                dungeonTemp[iter][0][it] = 2; //label as door
                break;
            }
            if(it+1 == dungeonTemp[iter][0].size()-1){ //failsafe
                dungeonTemp[iter][0][it] = 2; //label as door
            }
        }
        for(unsigned int it = 1; it < dungeonTemp[iter][0].size()-1; it++){ //last row (note: each row same size)
            if(rand() % dungeonTemp[iter][0].size() + 1 == 1){ //random chance
                dungeonTemp[iter][dungeonTemp[iter].size()-1][it] = 2; //label as door (uses last row)
                break;
            }
            if(it+1 == dungeonTemp[iter][0].size()-1){ //failsafe
                dungeonTemp[iter][dungeonTemp[iter].size()-1][it] = 2; //label as door (uses last row)
            }
        }
        for(unsigned int it = 1; it < dungeonTemp[iter].size(); it++){
            if(rand() % dungeonTemp[iter].size() + 1 == 1){ //random chance
                dungeonTemp[iter][it][0] = 2; //label as door
                break;
                //note: it is row, only checks first wall in row, so use 0 for cell
            }
            if(it+1 == dungeonTemp[iter].size()-1){ //failsafe
                dungeonTemp[iter][it][0] = 2; //label as door
            }
        }
        for(unsigned int it = 1; it < dungeonTemp[iter].size(); it++){
            if(rand() % dungeonTemp[iter][0].size() + 1 == 1){ //random chance
                dungeonTemp[iter][it][dungeonTemp[iter][0].size()-1] = 2; //label as door
                break;
                //note: it is row, only checks last wall in row, so use max value for cell
            }
            if(it+1 == dungeonTemp[iter][0].size()-1){
                dungeonTemp[iter][it][dungeonTemp[iter][0].size()-1] = 2; //label as door
            }
        }
    }
    return dungeonTemp;
}

vector< vector< vector< int> > > createNPCS(vector< vector< vector<int> > > dungeonTemp){ //create non-player characters
    for(unsigned int iter = 0; iter < dungeonTemp.size(); iter++){ //loop through each room
        int chanceCeiling = dungeonTemp[iter].size()/1.5; //chance based on room size
        for(unsigned int it = 0; it < dungeonTemp[iter].size(); it++){ //loop through each row
            for(unsigned int i = 0; i < dungeonTemp[iter][it].size(); i++){ //loop through each cell
                if(rand() % chanceCeiling + 1 == 1){ //if random chance occurs
                    if(dungeonTemp[iter][it][i] == 0){ //if cell unassigned
                        dungeonTemp[iter][it][i] = (rand() % 12 + 9); //spot in room becomes random NPC (9-20)
                    }
                }
            }
        }
    }
    return dungeonTemp;
}

vector< vector< vector< int> > > createObjects(vector< vector< vector<int> > > dungeonTemp){
    for(unsigned int iter = 0; iter < dungeonTemp.size(); iter++){ //loop through each room
        int chanceCeiling = dungeonTemp[iter].size()/1.2; //chance based on room size
        for(unsigned int it = 0; it < dungeonTemp[iter].size(); it++){ //loop through each row
            for(unsigned int i = 0; i < dungeonTemp[iter][it].size(); i++){ //loop through each cell
                if(rand() % chanceCeiling + 1 == 1){ //if random chance occurs
                    if(dungeonTemp[iter][it][i] == 0){ //if cell unassigned
                        dungeonTemp[iter][it][i] = (rand() % 5 + 4); //spot in room becomes random object (4-8)
                    }
                }
            }
        }
    }
    return dungeonTemp;
}

vector< vector< vector< int> > > createTreasure(vector< vector< vector<int> > > dungeonTemp){
    for(unsigned int iter = 0; iter < dungeonTemp.size(); iter++){ //loop through each room
        int chanceCeiling = dungeonTemp[iter].size()/1.5; //chance based on room size
        for(unsigned int it = 0; it < dungeonTemp[iter].size(); it++){ //loop through each row
            for(unsigned int i = 0; i < dungeonTemp[iter][it].size(); i++){ //loop through each cell
                if(rand() % chanceCeiling + 1 == 1){ //if random chance occurs
                    if(dungeonTemp[iter][it][i] == 0){ //if cell unassigned
                        dungeonTemp[iter][it][i] = 3; //spot in room becomes treasure
                    }
                }
            }
        }
    }
    return dungeonTemp;
}

vector< vector< vector<int> > > createDungeon(){
    vector< vector< vector<int> > > dungeonTemp(rand() % 50 + 250); //create random number of rooms (250-300)
    for(unsigned int iter = 0; iter < dungeonTemp.size(); iter++){
        int roomPotentialSizes[] = {24, 28, 32, 36};
        int choice = rand() % 3 + 0;
        int roomSize = roomPotentialSizes[choice]; //create random size for each room
        dungeonTemp[iter].resize(roomSize);
        for(unsigned int it = 0; it < dungeonTemp[iter].size(); it++){ //loop through all rows in room
            dungeonTemp[iter][it].resize(roomSize); //resize
            for(unsigned int i = 0; i < dungeonTemp[iter][it].size(); i++){ //loop through all cells in room
                dungeonTemp[iter][it][i] = 0; //label as unassigned
                if(it == 0 || it == dungeonTemp[iter].size()-1){ //if row is top or bottom of room
                    dungeonTemp[iter][it][i] = 1; //label as wall
                }
                if(i == 0 || i == dungeonTemp[iter][it].size()-1){ //if cell is first or last in row
                    dungeonTemp[iter][it][i] = 1; //label as wall
                }
            }
        }
    }
    dungeonTemp = createDoors(dungeonTemp); //make doors in walls
    dungeonTemp = createObjects(dungeonTemp);
    dungeonTemp = createNPCS(dungeonTemp); //note: this breaks formatted printing of dungeon
    dungeonTemp = createTreasure(dungeonTemp);
    return dungeonTemp;
}
