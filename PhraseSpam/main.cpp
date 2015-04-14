#define WINVER 0x0500
#include <iostream>
#include <windows.h>
#include <winable.h>
#include <map>

using namespace std;

void GenerateKey(int vk, BOOL bExtended, bool two_for_one = FALSE, int vk2 = 0) { //for sending the Q-Q

    KEYBDINPUT  kb = {0};
    INPUT       Input = {0};

    /* Generate a "key down" */
    if (bExtended) { kb.dwFlags  = KEYEVENTF_EXTENDEDKEY; }
    kb.wVk  = vk;
    Input.type  = INPUT_KEYBOARD;
    Input.ki  = kb;
    SendInput(1, &Input, sizeof(Input));

    KEYBDINPUT  kb2 = {0};
    INPUT       Input2 = {0};

    if(two_for_one){
        kb2.wVk  = vk2;
        Input2.type  = INPUT_KEYBOARD;
        Input2.ki  = kb2;
        SendInput(1, &Input2, sizeof(Input2));
    }

    if(two_for_one){
        /* Generate a "key up" */
        ZeroMemory(&kb2, sizeof(KEYBDINPUT));
        ZeroMemory(&Input2, sizeof(INPUT));
        kb2.dwFlags  =  KEYEVENTF_KEYUP;
        kb2.wVk = vk2;
        Input2.type = INPUT_KEYBOARD;
        Input2.ki = kb2;
        SendInput(1, &Input2, sizeof(Input2));
    }

    /* Generate a "key up" */
    ZeroMemory(&kb, sizeof(KEYBDINPUT));
    ZeroMemory(&Input, sizeof(INPUT));
    kb.dwFlags  =  KEYEVENTF_KEYUP;
    if (bExtended) { kb.dwFlags |= KEYEVENTF_EXTENDEDKEY; }
    kb.wVk = vk;
    Input.type = INPUT_KEYBOARD;
    Input.ki = kb;
    SendInput(1, &Input, sizeof(Input));
}

int main()
{
    /*cout << "Hit \'end\' to quit." << endl;
    map<char, int> keycodes;
    map<char, int> keycodesCaps;
    map<char, int> keycodesMisc;
    keycodes.insert(make_pair('a', 0x41));
    keycodes.insert(make_pair('b', 0x42));
    keycodes.insert(make_pair('c', 0x43));
    keycodes.insert(make_pair('d', 0x44));
    keycodes.insert(make_pair('e', 0x45));
    keycodes.insert(make_pair('f', 0x46));
    keycodes.insert(make_pair('g', 0x47));
    keycodes.insert(make_pair('h', 0x48));
    keycodes.insert(make_pair('i', 0x49));
    keycodes.insert(make_pair('j', 0x4A));
    keycodes.insert(make_pair('k', 0x4B));
    keycodes.insert(make_pair('l', 0x4C));
    keycodes.insert(make_pair('m', 0x4D));
    keycodes.insert(make_pair('n', 0x4E));
    keycodes.insert(make_pair('o', 0x4F));
    keycodes.insert(make_pair('p', 0x50));
    keycodes.insert(make_pair('q', 0x51));
    keycodes.insert(make_pair('r', 0x52));
    keycodes.insert(make_pair('s', 0x53));
    keycodes.insert(make_pair('t', 0x54));
    keycodes.insert(make_pair('u', 0x55));
    keycodes.insert(make_pair('v', 0x56));
    keycodes.insert(make_pair('w', 0x57));
    keycodes.insert(make_pair('x', 0x58));
    keycodes.insert(make_pair('y', 0x59));
    keycodes.insert(make_pair('z', 0x5A));

    keycodesCaps.insert(make_pair('A', 0x41));
    keycodesCaps.insert(make_pair('B', 0x42));
    keycodesCaps.insert(make_pair('C', 0x43));
    keycodesCaps.insert(make_pair('D', 0x44));
    keycodesCaps.insert(make_pair('E', 0x45));
    keycodesCaps.insert(make_pair('F', 0x46));
    keycodesCaps.insert(make_pair('G', 0x47));
    keycodesCaps.insert(make_pair('H', 0x48));
    keycodesCaps.insert(make_pair('I', 0x49));
    keycodesCaps.insert(make_pair('J', 0x4A));
    keycodesCaps.insert(make_pair('K', 0x4B));
    keycodesCaps.insert(make_pair('L', 0x4C));
    keycodesCaps.insert(make_pair('M', 0x4D));
    keycodesCaps.insert(make_pair('N', 0x4E));
    keycodesCaps.insert(make_pair('O', 0x4F));
    keycodesCaps.insert(make_pair('P', 0x50));
    keycodesCaps.insert(make_pair('Q', 0x51));
    keycodesCaps.insert(make_pair('R', 0x52));
    keycodesCaps.insert(make_pair('S', 0x53));
    keycodesCaps.insert(make_pair('T', 0x54));
    keycodesCaps.insert(make_pair('U', 0x55));
    keycodesCaps.insert(make_pair('V', 0x56));
    keycodesCaps.insert(make_pair('W', 0x57));
    keycodesCaps.insert(make_pair('X', 0x58));
    keycodesCaps.insert(make_pair('Y', 0x59));
    keycodesCaps.insert(make_pair('Z', 0x5A));

    keycodesMisc.insert(make_pair('/', 0xBF));
    keycodesMisc.insert(make_pair('\\',0xDC));
    keycodesMisc.insert(make_pair('1', 0x31));
    keycodesMisc.insert(make_pair('2', 0x32));
    keycodesMisc.insert(make_pair('3', 0x33));
    keycodesMisc.insert(make_pair('4', 0x34));
    keycodesMisc.insert(make_pair('5', 0x35));
    keycodesMisc.insert(make_pair('6', 0x36));
    keycodesMisc.insert(make_pair('7', 0x37));
    keycodesMisc.insert(make_pair('8', 0x38));
    keycodesMisc.insert(make_pair('9', 0x39));
    keycodesMisc.insert(make_pair('0', 0x30));
    keycodesMisc.insert(make_pair(' ', VK_SPACE));

    string key;
    unsigned int key_int = -1;
    cout << "Enter the phrase you wish to send: ";
    getline(cin, key);
    int speed;
    cout << "Enter the wait time (in miliseconds) between each send: ";
    cin >> speed;
    if(speed <= 0){
        speed = 1;
    }
    bool active = true;
    while(true){
        while(active){
            for(unsigned int iter = 0; iter < key.size(); iter++){
                if(keycodes.find(key[iter]) != keycodes.end()){
                    key_int = keycodes.find(key[iter])->second;
                    GenerateKey(key_int, FALSE);
                }
                else if(keycodesCaps.find(key[iter]) != keycodesCaps.end()){
                    key_int = keycodesCaps.find(key[iter])->second;
                    GenerateKey(VK_SHIFT, FALSE, TRUE, key_int);
                }
                else if(keycodesMisc.find(key[iter]) != keycodesMisc.end()){
                    key_int = keycodesMisc.find(key[iter])->second;
                    GenerateKey(key_int, FALSE);
                }
                Sleep(10);
                GenerateKey(VK_RETURN, FALSE);
                if(GetKeyState(VK_END) & 0x80){
                    active = false;
                }
            }
        }
        if(GetKeyState(VK_HOME) & 0x80){
            active = true;
        }
    }*/
    while((GetKeyState(0x51) & 0x80) == 0){
        continue;
        Sleep(1);
    }
    for(int iter = 0x41; iter < 0x5A; iter++){
        GenerateKey(iter, FALSE);
        Sleep(1);
    }
}
