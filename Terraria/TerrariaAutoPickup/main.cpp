#define WINVER 0x0500
#include <windows.h>
#include <winable.h>
#include <time.h>
#include <iostream>

using namespace std;

void Generate_Key_down(int key){
    keybd_event(key, 0, 0, 0);
    Sleep(1);
}

void Generate_Key_up(int key){
    keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
    Sleep(1);
}




int main()
{
    Sleep(5000);
    int walk_direction = 0x41;
    bool key_downed = false;
    while((GetKeyState(VK_END) & 0x80) == 0){
        if(!key_downed){
            Generate_Key_down(walk_direction);
            key_downed = true;
        }
        Sleep(3000);
        Generate_Key_up(walk_direction);
        if(walk_direction == 0x41){
            walk_direction = 0x44;
        }
        else if(walk_direction == 0x44){
            walk_direction = 0x41;
        }
        key_downed = false;
    }
    Generate_Key_up(walk_direction);
    return 0;
}
