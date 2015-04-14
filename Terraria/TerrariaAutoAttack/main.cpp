#define WINVER 0x0500
#include <windows.h>
#include <winable.h>
#include <time.h>
#include <iostream>

using namespace std;

void click(){
    INPUT    input={0};
    // left down
    input.type      = INPUT_MOUSE;
    input.mi.dwFlags  = MOUSEEVENTF_LEFTDOWN;
    SendInput(1,&input,sizeof(INPUT));

    Sleep(1);

    // left up
    ZeroMemory(&input,sizeof(INPUT));
    input.type      = INPUT_MOUSE;
    input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;
    SendInput(1,&input,sizeof(INPUT));
}

int main()
{
    Sleep(4000);
    while((GetKeyState(VK_END) & 0x80) == 0){
        click();
        Sleep(500);
    }
    return 0;
}
