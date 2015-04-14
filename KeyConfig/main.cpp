#include <iostream>
#include <vector>
#include <map>
#include <windows.h>
#include <winable.h>
#include <algorithm>

using namespace std;

map<string, int> keycodes; //a map for keys to keycodes. Incomplete because I need shorter names for some keys

void setup(){
    keycodes.insert(make_pair("a", 0x41));
    keycodes.insert(make_pair("b", 0x42));
    keycodes.insert(make_pair("c", 0x43));
    keycodes.insert(make_pair("d", 0x44));
    keycodes.insert(make_pair("e", 0x45));
    keycodes.insert(make_pair("f", 0x46));
    keycodes.insert(make_pair("g", 0x47));
    keycodes.insert(make_pair("h", 0x48));
    keycodes.insert(make_pair("i", 0x49));
    keycodes.insert(make_pair("j", 0x4A));
    keycodes.insert(make_pair("k", 0x4B));
    keycodes.insert(make_pair("l", 0x4C));
    keycodes.insert(make_pair("m", 0x4D));
    keycodes.insert(make_pair("n", 0x4E));
    keycodes.insert(make_pair("o", 0x4F));
    keycodes.insert(make_pair("p", 0x50));
    keycodes.insert(make_pair("q", 0x51));
    keycodes.insert(make_pair("r", 0x52));
    keycodes.insert(make_pair("s", 0x53));
    keycodes.insert(make_pair("t", 0x54));
    keycodes.insert(make_pair("u", 0x55));
    keycodes.insert(make_pair("v", 0x56));
    keycodes.insert(make_pair("w", 0x57));
    keycodes.insert(make_pair("x", 0x58));
    keycodes.insert(make_pair("y", 0x59));
    keycodes.insert(make_pair("z", 0x5A));
    keycodes.insert(make_pair("0", 0x30));
    keycodes.insert(make_pair("1", 0x31));
    keycodes.insert(make_pair("2", 0x32));
    keycodes.insert(make_pair("3", 0x33));
    keycodes.insert(make_pair("4", 0x34));
    keycodes.insert(make_pair("5", 0x35));
    keycodes.insert(make_pair("6", 0x36));
    keycodes.insert(make_pair("7", 0x37));
    keycodes.insert(make_pair("8", 0x38));
    keycodes.insert(make_pair("9", 0x39));
    keycodes.insert(make_pair("left", 0x25));
    keycodes.insert(make_pair("up", 0x26));
    keycodes.insert(make_pair("right", 0x27));
    keycodes.insert(make_pair("down", 0x28));
    keycodes.insert(make_pair("left click", 0x01));
    keycodes.insert(make_pair("right click", 0x02));
    keycodes.insert(make_pair("middle click", 0x04));
}

vector<int> to_swap_keycodes; //make it global so the hook can access it
vector<int> swap_to_keycodes; //holds the int versions of the letters the user is looking to swap

void GenerateKey(int vk, bool event){ //generates keys
    KEYBDINPUT kb = {0};
    INPUT Input = {0};
    if(!event){
        /* Generate a "key down" */
        kb.wVk  = vk;
        Input.type = INPUT_KEYBOARD;
        Input.ki  = kb;
        SendInput(1, &Input, sizeof(Input));
    }
    else{
        /* Generate a "key up" */
        ZeroMemory(&kb, sizeof(KEYBDINPUT));
        ZeroMemory(&Input, sizeof(INPUT));
        kb.dwFlags = KEYEVENTF_KEYUP;
        kb.wVk = vk;
        Input.type = INPUT_KEYBOARD;
        Input.ki = kb;
        SendInput(1, &Input, sizeof(Input));
    }
}

void GenerateClick(int vk, bool event){
    INPUT input={0};
    if(!event){
        //down
        input.type = INPUT_MOUSE;
        if(vk == 0){
            input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        }
        else if(vk == 1){
            input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
        }
        else if(vk == 2){
            input.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
        }
        SendInput(1,&input,sizeof(INPUT));
    }
    else{
        //up
        ZeroMemory(&input,sizeof(INPUT));
        input.type = INPUT_MOUSE;
        if(vk == 0){
            input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
        }
        else if(vk == 1){
            input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
        }
        else if(vk == 2){
            input.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
        }
        SendInput(1,&input,sizeof(INPUT));
    }
}

HHOOK kHook;
HHOOK mHook;

LRESULT CALLBACK KybHk(int nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT* pkbhs = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam); //convert lParam to something usable
    unsigned int index = find(to_swap_keycodes.begin(), to_swap_keycodes.end(), pkbhs->vkCode) - to_swap_keycodes.begin(); //find where the pressed key is in the vector
    if(index < to_swap_keycodes.size()){ //if the keycode is one to be swapped
        if(wParam == WM_KEYDOWN){ //if the key was pressed
            if(swap_to_keycodes[index] == 1 || swap_to_keycodes[index] == 2 || swap_to_keycodes[index] == 4){
                GenerateClick(0, false); //generate a mouse press
            }
            else{
                GenerateKey(swap_to_keycodes[index], false); //generate a key press
            }
        }
        else if(wParam == WM_KEYUP){ //if it was released
            if(swap_to_keycodes[index] == 1 || swap_to_keycodes[index] == 2 || swap_to_keycodes[index] == 4){
                GenerateClick(0, true); //generate a mouse release
            }
            else{
                GenerateKey(swap_to_keycodes[index], true); //generate a key release
            }
        }
        return 1; //don't call the next hook, stopping the original key from being sent
    }
    return CallNextHookEx(kHook, nCode, wParam, lParam); //otherwise, call the next hook in the chain
}

LRESULT CALLBACK MseHk(int nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT* pkbhs = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam); //convert lParam to something usable
    unsigned int index = find(to_swap_keycodes.begin(), to_swap_keycodes.end(), pkbhs->vkCode) - to_swap_keycodes.begin(); //find where the pressed key is in the vector
    if(index < to_swap_keycodes.size()){ //if the keycode is one to be swapped
        if(wParam == WM_LBUTTONDOWN){ //if the key was pressed
            if(swap_to_keycodes[index] == 1 || swap_to_keycodes[index] == 2 || swap_to_keycodes[index] == 4){
                GenerateClick(0, false); //generate a mouse press
            }
            else{
                GenerateKey(swap_to_keycodes[index], false); //generate a key press
            }
        }
        else if(wParam == WM_LBUTTONUP){ //if it was released
            if(swap_to_keycodes[index] == 1 || swap_to_keycodes[index] == 2 || swap_to_keycodes[index] == 4){
                GenerateClick(0, true); //generate a mouse release
            }
            else{
                GenerateKey(swap_to_keycodes[index], true); //generate a key release
            }
        }
        else if(wParam == WM_RBUTTONDOWN){ //if it was released
            if(swap_to_keycodes[index] == 1 || swap_to_keycodes[index] == 2 || swap_to_keycodes[index] == 4){
                GenerateClick(0, false); //generate a mouse press
            }
            else{
                GenerateKey(swap_to_keycodes[index], false); //generate a key press
            }
        }
        else if(wParam == WM_RBUTTONUP){ //if it was released
            if(swap_to_keycodes[index] == 1 || swap_to_keycodes[index] == 2 || swap_to_keycodes[index] == 4){
                GenerateClick(0, true); //generate a mouse release
            }
            else{
                GenerateKey(swap_to_keycodes[index], true); //generate a key release
            }
        }
        else if(wParam == WM_MBUTTONDOWN){ //if it was released
            if(swap_to_keycodes[index] == 1 || swap_to_keycodes[index] == 2 || swap_to_keycodes[index] == 4){
                GenerateClick(0, false); //generate a mouse press
            }
            else{
                GenerateKey(swap_to_keycodes[index], false); //generate a key press
            }
        }
        else if(wParam == WM_MBUTTONUP){ //if it was released
            if(swap_to_keycodes[index] == 1 || swap_to_keycodes[index] == 2 || swap_to_keycodes[index] == 4){
                GenerateClick(0, true); //generate a mouse release
            }
            else{
                GenerateKey(swap_to_keycodes[index], true); //generate a key release
            }
        }
        return 1; //don't call the next hook, stopping the original key from being sent
    }
    return CallNextHookEx(mHook, nCode, wParam, lParam); //otherwise, call the next hook in the chain
}

void key_swap(vector<string> to_swap, vector<string> swap_to){ //holds the hook loop and key swap code
    for(unsigned int iter = 0; iter < to_swap.size(); iter++){ //generate the keycode vectors
        to_swap_keycodes.push_back(keycodes.find(to_swap[iter])->second);
        swap_to_keycodes.push_back(keycodes.find(swap_to[iter])->second);
    }
    while(true){ //hook loop
        MSG kMsg;
        MSG mMsg;
        kHook = SetWindowsHookEx(WH_KEYBOARD_LL, KybHk, NULL, NULL);
        mHook = SetWindowsHookEx(WH_MOUSE_LL, MseHk, NULL, NULL);
        while(true){
            if(GetMessage(&kMsg, NULL, NULL, NULL)){
                TranslateMessage(&kMsg);
                DispatchMessage(&kMsg);
            }
            if(GetMessage(&mMsg, NULL, NULL, NULL)){
                TranslateMessage(&mMsg);
                DispatchMessage(&mMsg);
            }
        }

        UnhookWindowsHookEx(kHook);
        UnhookWindowsHookEx(mHook);
    }
}

struct RemoveDelimiter //removes whitespace from strings. Allows for more flexible input-handling
{
  bool operator()(char c)
  {
    return (c =='\r' || c =='\t' || c == ' ' || c == '\n');
  }
};

map<string, int>::iterator iter;

int main()
{
    setup();
    cout << "For a list of supported keys, enter \'help\'." << endl;
    cout << "Format is \'Normal Key : Swapped Key\'" << endl;
    cout << "Enter \'end\' to finish." << endl;
    string entry;
    vector<string> temp_to_swap;
    vector<string> temp_swap_to;
    while(true){
        cout << "Entry: ";
        getline(cin, entry); //get the two keys to be swapped
        entry.erase(remove_if(entry.begin(), entry.end(), RemoveDelimiter()), entry.end()); //clean the input
        temp_to_swap.push_back(entry.substr(0, entry.find(":"))); //get the to-be-swapped
        temp_swap_to.push_back(entry.substr(entry.find(":")+1)); //get the swap-to
        if(entry == "end" || entry == "End" || entry == "END"){ //if the user is done entering
            key_swap(temp_to_swap, temp_swap_to); //create the hook and swap keys
            break;
        }
        if(entry == "help" || entry == "Help" || entry == "HELP"){
            for(iter = keycodes.begin(); iter != keycodes.end(); iter++){
                cout << (*iter).first << endl;
            }
        }
        cin.clear(); cin.sync();
    }
    return 0;
}
