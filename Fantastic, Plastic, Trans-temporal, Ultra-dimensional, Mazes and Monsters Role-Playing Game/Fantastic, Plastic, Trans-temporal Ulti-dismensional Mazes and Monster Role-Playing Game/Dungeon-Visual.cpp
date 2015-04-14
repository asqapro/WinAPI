#include "Headers.h"
#include "DungeonFunctionsVisual.h"

using namespace std;

string objectsSymbols[] = {" ", "\xDB", "\xB0", "\xDC",
                            "\xCB", "\xD2", "\x18", "\xF4", "\x8C", "\x0F",
                            "\xF8", "\x8E", "\x9D", "\x"}
string bouncingBlob[] = {"\x6F"};

//{"", "wall", "door", "chest",
//"desk", "book", "sword", "dagger", "torch", "shield",
//"bouncing blob", "human", "lobster", "elephant", "dwarf", "pixie",
//"chest", "ooze", "bat", "dwarf", "spider", "goblin"};

int displayDungeon(vector< vector< vector<int> > > dungeonTemp){
    for(unsigned int iter = 0; iter < dungeonTemp.size(); iter++){
        for(unsigned int it = 0; it < dungeonTemp[iter].size(); it++){
            for(unsigned int i = 0; i < dungeonTemp[iter][it].size(); i++){
                cout << dungeonTemp[iter][it][i];
            }
            cout << endl;
        }
        cout << "\n\n";
    }
    return 1;
}
