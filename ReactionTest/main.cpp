#define WINVER 0x500
#include <windows.h>
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
    POINT p;
    COLORREF color;
    HDC dc = GetDC(NULL);
    int red;
    int green;
    int blue;
    while(true){
        GetCursorPos(&p);
        color = GetPixel(dc, p.x, p.y);
        red = GetRValue(color);
        green = GetGValue(color);
        blue = GetBValue(color);
        if(red == 75 && green == 219 && blue == 106){
            Sleep(15);
            click();
            Sleep(500);
        }
        Sleep(1);
    }
    ReleaseDC(NULL, dc);
    cout << "done" << endl;
    while(true){
        Sleep(1);
    }
    return 0;
}
