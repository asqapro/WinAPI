#include "Headers.h"
#include "PlayerFunctions.h"
#include "DungeonFunctionsText.h"
#include "DungeonFunctionsVisual.h"

#include <sstream>

//Player rotation:
//1 - north (up)
//2 - east (right)
//3 - south (down)
//4 - west (left)

using namespace std;

string commandDescription = "(open/ pick up/ drop/ fight/ use/ speak to) X";
string commands[] = {"open", "pick up", "drop", "fight", "use", "speak to"};

string descriptions[] = {"An empty space", "a wall", "a door", "a chest full of treasure",
                        "a desk with a book resting on it", "a sword", "a dagger", "a torch", "a shield",
                        "a bouncing blob", "a fellow human", "a smiling lobster", "a white elephant", "a frowning dwarf",
                        "a floating pixie",
                        "a sinister looking chest", "a pile of ooze on the floor", "a screeching bat hovering at face level",
                        "a grinning dwarf", "a spider dangling from the ceiling", "a grimy goblin"};

string cardinalDirections[] = {"north", "east", "south", "west"};

void help(){
    cout << "Commands: " << commandDescription << "." << endl;
    cout << "Movement: arrow keys." << endl;
}

vector< vector< vector<int> > > dungeon;
map< vector<int>, vector<int> > connections;


int keysUpper[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' '};
int keysLower[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' '};


int keypress(){
    for(int iter = 0; iter < 27; iter++){
        if((GetKeyState(keysUpper[iter]) & 0x80) != 0){
            cout << (char)keysLower[iter];
            return iter;
        }
    }
    return -1;
}

int searchArray(string searchFor, string searchIn[], int size){
    for(int iter = 0; iter < size; iter++){
        if(searchIn[iter] == searchFor){
            return iter;
        }
    }
    return -1;
}

vector<int> openDoor(vector<int> playerPosition, map< vector<int>, vector<int> > connections){
    switch(playerPosition[3]){
        case 1:
            playerPosition[1]--;
            break;
        case 2:
            playerPosition[2]++;
            break;
        case 3:
            playerPosition[1]++;
            break;
        case 4:
            playerPosition[2]--;
            break;
    }
    int rotation = playerPosition[3]; //preserver rotation
    playerPosition[3] = 1; //match connection vector
    vector<int> connectedDoor = connections.find(playerPosition)->second;
    playerPosition = connectedDoor;
    cout << "You emerge on the other side of the door into a new room." << endl;
    playerPosition[3] = rotation; //restore rotation
    if(playerPosition[1] == 0){ //top of room
        playerPosition[1]++;
        playerPosition[3] = 3; //player walks out of door and points south
        cout << "You are now facing south." << endl;
    }
    else if((unsigned)playerPosition[1] == dungeon[playerPosition[0]].size()-1){ //bottom of room
        playerPosition[1]--;
        playerPosition[3] = 1; //player points north
        cout << "You are now facing north." << endl;
    }
    else if(playerPosition[2] == 0){ //far left of room
        playerPosition[2]++;
        playerPosition[3] = 2; //player points east
        cout << "You are now facing east." << endl;
    }
    else if((unsigned)playerPosition[2] == dungeon[playerPosition[0]][playerPosition[1]].size()-1){ //far right of room
        playerPosition[2]--;
        playerPosition[3] = 4; //player points west
        cout << "You are now facing west." << endl;
    }
    else{
        cout << "Moving between doors broked" << endl;
        Sleep(1000);
    }
    return playerPosition;
}

vector<int> act(vector<int> playerPosition, int command, map< vector<int>, vector<int> > connections){
    int object = 0;
    vector<int> objectPosition;
    switch(playerPosition[3]){
        case 1:
            object = dungeon[playerPosition[0]][playerPosition[1]-1][playerPosition[2]];
            objectPosition.push_back(playerPosition[0]);
            objectPosition.push_back(playerPosition[1]-1);
            objectPosition.push_back(playerPosition[2]);
            break;
        case 2:
            object = dungeon[playerPosition[0]][playerPosition[1]][playerPosition[2]+1];
            objectPosition.push_back(playerPosition[0]);
            objectPosition.push_back(playerPosition[1]);
            objectPosition.push_back(playerPosition[2]+1);
            break;
        case 3:
            object = dungeon[playerPosition[0]][playerPosition[1]+1][playerPosition[2]];
            objectPosition.push_back(playerPosition[0]);
            objectPosition.push_back(playerPosition[1]+1);
            objectPosition.push_back(playerPosition[2]);
            break;
        case 4:
            object = dungeon[playerPosition[0]][playerPosition[1]][playerPosition[2]-1];
            objectPosition.push_back(playerPosition[0]);
            objectPosition.push_back(playerPosition[1]);
            objectPosition.push_back(playerPosition[2]-1);
            break;
        default:
            object = 0;
            cout << "Object error." << endl;
            Sleep(1000);
    }
    if(object == 2){ //door
        if(command == 0){ //open
            cout << "You " << commands[command] << " " << descriptions[object] << "." << endl;
            openDoor(playerPosition, connections);
        }
        else{
            cout << "You cannot " << commands[command] << " " << descriptions[object] << "." << endl;
        }
    }
    else if(object == 3){ //treasure
        if(command == 0){ //open
            cout << "The chest is locked with a key. You can pick it up to open it with keys you find later." << endl;
            //cout << "You " << commands[command] << " " << descriptions[object] << "." << endl;
            //cout << "What you find inside will be revealed in later versions of the game." << endl;
        }
        else if(command == 1){ //pick up
            cout << "You " << commands[command] << " " << descriptions[object] << "." << endl;
            dungeon[objectPosition[0]][objectPosition[1]][objectPosition[2]] = 0;
            cout << "Note that the object is removed from the room, but not given to you. Will be given in later versions." << endl;
        }
        else{
            cout << "You cannot " << commands[command] << " " << descriptions[object] << "." << endl;
        }
    }
    else if(object >= 4 && object <= 8){ //objects
        if(command == 1){
            cout << "You " << commands[command] << " " << descriptions[object] << "." << endl;
            dungeon[objectPosition[0]][objectPosition[1]][objectPosition[2]] = 0;
            cout << "Note that the object is removed from the room, but not given to you. Will be given in later versions." << endl;

        }
        else{
            cout << "You cannot " << commands[command] << " " << descriptions[object] << "." << endl;
        }
    }
    else if(object >= 9 && object <= 14){ //friendly NPC's
        if(command == 3){

        }
        if(command == 5){
            cout << "You " << commands[command] << " " << descriptions[object] << "." << endl;
            cout << "They say nothing. They will in later versions." << endl;
        }
        else{
            cout << "You cannot " << commands[command] << " " << descriptions[object] << "." << endl;
        }
    }
    else if(object >= 15 && object <= 20){ //hostile NPC's
        if(command == 3 || command == 5){
            cout << "You " << commands[command] << " " << descriptions[object] << "." << endl;
        }
        else{
            cout << "You cannot " << commands[command] << " " << descriptions[object] << "." << endl;
        }
    }
    else{
        cout << descriptions[object] << " is not something you can interact with." << endl;
    }
    return playerPosition;
}

vector<int> rotatePlayer(vector<int> playerPosition, int direction){
    playerPosition[3]+=direction;
    if(playerPosition[3] < 1){
        playerPosition[3] = 4;
    }
    if(playerPosition[3] > 4){
        playerPosition[3] = 1;
    }
    return playerPosition;
}

int rightCallback = 0;
int leftCallback = 0;
int upCallback = 0;
int downCallback = 0;
//note: playerPosition[0] is room, playerPosition[1] is Y in room, playerPosition[2] is X in room
vector<int> move(vector<int> playerPosition){
    if((GetKeyState(VK_UP) & 0x80) != 0 && upCallback == 0){ //if up arrow is pressed and callback is not set
        upCallback = 1; //set the callback to true
        switch(playerPosition[3]){
            case 1:
                playerPosition[1]--; //move north
                break;
            case 2:
                playerPosition[2]++; //move east
                break;
            case 3:
                playerPosition[1]++; //move south
                break;
            case 4:
                playerPosition[2]--; //move west
                break;
        }
        if(dungeon[playerPosition[0]][playerPosition[1]][playerPosition[2]] == 0){ //if the spot the player will move to is unassigned
            cout << "You take one step forward." << endl;
        }
        else{
            string blocking = descriptions[dungeon[playerPosition[0]][playerPosition[1]][playerPosition[2]]];
            cout << "Your path is blocked by " << blocking << "." << endl;
            switch(playerPosition[3]){
                case 1:
                    playerPosition[1]++; //undo move
                    break;
                case 2:
                    playerPosition[2]--; //undo move
                    break;
                case 3:
                    playerPosition[1]--; //undo move
                    break;
                case 4:
                    playerPosition[2]++; //undo move
                    break;
            }
        }
    }
    else if((GetKeyState(VK_UP) & 0x80) == 0 && upCallback == 1){ //if up arrow is not pressed and callback is set
        upCallback = 0; //set the callback to false
    }
    if((GetKeyState(VK_DOWN) & 0x80) != 0 && downCallback == 0){ //if down arrow is pressed and callback is not set
        downCallback = 1; //set the callback to true
        switch(playerPosition[3]){
            case 1:
                playerPosition[1]++; //move south
                break;
            case 2:
                playerPosition[2]--; //move west
                break;
            case 3:
                playerPosition[1]--; //move north
                break;
            case 4:
                playerPosition[2]++; //move east
                break;
        }
        if(dungeon[playerPosition[0]][playerPosition[1]][playerPosition[2]] == 0){ //if the spot the player will move to is unassigned
            cout << "You take one step backward." << endl;
        }
        else{
            string blocking = descriptions[dungeon[playerPosition[0]][playerPosition[1]][playerPosition[2]]];
            cout << "Your path is blocked by " << blocking << "." << endl;
            switch(playerPosition[3]){
                case 1:
                    playerPosition[1]--; //undo move
                    break;
                case 2:
                    playerPosition[2]++; //undo move
                    break;
                case 3:
                    playerPosition[1]++; //undo move
                    break;
                case 4:
                    playerPosition[2]--; //undo move
                    break;
            }
        }
    }
    else if((GetKeyState(VK_DOWN) & 0x80) == 0 && downCallback == 1){ //if down arrow is not pressed and callback is set
        downCallback = 0; //set the callback to false
    }
    if((GetKeyState(VK_LEFT) & 0x80) != 0 && leftCallback == 0){ //if left arrow is pressed and callback is not set
        leftCallback = 1; //set the callback to true
        playerPosition = rotatePlayer(playerPosition, -1);
        cout << "You turn to the left. " << "You now face " << cardinalDirections[playerPosition[3]-1] << "." << endl;
    }
    else if((GetKeyState(VK_LEFT) & 0x80) == 0 && leftCallback == 1){ //if left arrow is not pressed and callback is set
        leftCallback = 0; //set the callback to false
    }
    if((GetKeyState(VK_RIGHT) & 0x80) != 0 && rightCallback == 0){ //if right arrow is pressed and callback is not set
        rightCallback = 1; //set the callback to true
        playerPosition = rotatePlayer(playerPosition, 1);
        cout << "You turn to the right. " << "You now face " << cardinalDirections[playerPosition[3]-1] << "." << endl;
    }
    else if((GetKeyState(VK_RIGHT) & 0x80) == 0 && rightCallback == 1){ //if right arrow is not pressed and callback is set
        rightCallback = 0; //set the callback to false
    }
    return playerPosition;
}

int main()
{
    srand(time(NULL));
    int arena[10][10];
    int maxLat = 10;
    int maxLong = 10;
    int mines = 0;
    for(int lat = 0; lat < maxLat; lat++){
        for(int longi = 0; longi < maxLong; longi++){
            if(rand() % ((maxLong * maxLat)/2) > 25){
                arena[lat][longi] = 1;
                mines++;
            }
            else{
                arena[lat][longi] = 0;
            }
        }
    }
    cout << mines << endl;
    return 0;
    //cout << "\xCB" << " " << "\xD2" << " " << "\x18";
    for(int iter = 0; iter < 255; iter++){
        cout << iter << " " << (char)iter << "    ";
    }
    return 0;
    srand(time(NULL));
    vector<int> playerPosition;
    playerPosition.push_back(0); //room
    playerPosition.push_back(1); //row
    for(unsigned int i = 0; i < dungeon[0][0].size(); i++){ //loop through cells in Room 0, Row 0
        if(dungeon[0][0][i] == 2){ //if space is a door
            dungeon[0][1][i] = 21; //set space "in front of" door to player
            playerPosition.push_back(i); //cell
            break;
        }
    }
    playerPosition.push_back(1); //rotation, north
    cout << "Type \"help\" for a list of commands." << endl;
    cout << "You stand before an imposing set of doors." << endl;
    vector<int> keysPressed;
    int key = -1;
    int keyCallback = 0;
    int enterCallback = 0;
    int backspaceCallback = 0;
    while(true){
        if(!keyCallback){
            key = keypress();
            if(key != -1){
                keyCallback = 1;
                keysPressed.push_back(keysLower[key]);
            }
        }
        else if(keyCallback){
            if(key != -1){
                if((GetKeyState(keysUpper[key]) & 0x80) == 0){
                    keyCallback = 0;
                }
            }
        }
        if((GetKeyState(VK_BACK) & 0x80) != 0 && !backspaceCallback){
            cout << "\b \b";
            keysPressed.pop_back();
            backspaceCallback = 1;
        }
        else if((GetKeyState(VK_BACK) & 0x80) == 0 && backspaceCallback){
            backspaceCallback = 0;
        }
        if((GetKeyState(VK_RETURN) & 0x80) != 0 && !enterCallback){
            enterCallback = 1;
            cout << "\n";
            string action = string(keysPressed.begin(), keysPressed.end());
            for(int iter = 0; iter < 22; iter++){
                size_t found = action.find(objects[iter]); //find the object being acted on
                if(found != string::npos){
                    action = action.substr(0, found-1); //the action is everything before that object
                }
            }
            if(action == "help"){
                help();
            }
            else{
                int command = searchArray(action, commands, 6);
                playerPosition = act(playerPosition, command, connections);
            }
            keysPressed.clear();
        }
        else if((GetKeyState(VK_RETURN) & 0x80) == 0 && enterCallback){
            enterCallback = 0;
        }
        dungeon[playerPosition[0]][playerPosition[1]][playerPosition[2]] = 0;
        playerPosition = move(playerPosition);
        dungeon[playerPosition[0]][playerPosition[1]][playerPosition[2]] = 21;
        Sleep(1);
    }
    return 0;
}
