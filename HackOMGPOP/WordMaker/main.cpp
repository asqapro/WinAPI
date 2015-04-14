#define WINVER 0x0500
#include <iostream>
#include <windows.h>
#include <sstream>
#include <winable.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

void GenerateKey(int vk, BOOL bExtended) { //Copied I found, sends a keypress

    KEYBDINPUT  kb = {0};
    INPUT       Input = {0};

    /* Generate a "key down" */
    if (bExtended) { kb.dwFlags  = KEYEVENTF_EXTENDEDKEY; }
    kb.wVk  = vk;
    Input.type  = INPUT_KEYBOARD;
    Input.ki  = kb;
    SendInput(1, &Input, sizeof(Input));

    Sleep(1);

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
    map<string, int> keycodes; //a map matching letters to virtual letters; used in sending keys
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

    vector<string> used_words; //list of words already found
    vector<string> letters; //letters to use; entered by user
    string word; //collection of random letters; used to check if the word is original
    srand(time(NULL));
    string first; //first letter
    string second; //etc
    string third;
    string fourth;
    string fifth;
    string sixth;
    cout << "Enter your first letter: ";
    cin >> first;
    cout << "Enter your second letter: ";
    cin >> second;
    cout << "Enter your third letter: ";
    cin >> third;
    cout << "Enter your fourth letter: ";
    cin >> fourth;
    cout << "Enter your fifth letter: ";
    cin >> fifth;
    cout << "Enter your sixth letter: ";
    cin >> sixth;
    letters.push_back(first);
    letters.push_back(second);
    letters.push_back(third);
    letters.push_back(fourth);
    letters.push_back(fifth);
    letters.push_back(sixth);
    int firstInt; //first random letter
    int secondInt; //etc
    int thirdInt;
    int fourthInt;
    int fifthInt;
    int sixthInt;
    Sleep(2000); //so the user can tab into the game
    //1! * 6 LetterBlox does not have 1-letter words
    /*for(int iter = 0; iter < 6; iter++){
        int firstInt = rand() % 6 + 0; //get a random letter
        word += letters[firstInt]; //add it to the word
        if(find(used_words.begin(), used_words.end(), word) == used_words.end()){ //if not found in used_words, enter it
            GenerateKey(keycodes.find(letters[firstInt])->second, TRUE);
            Sleep(1);
            GenerateKey(VK_RETURN, TRUE); //send it
            Sleep(1);
            used_words.push_back(word); //add it to used_words
        }
        else{ //else, make a new word
            continue;
        }
    }
    Sleep(100);*/
    //2! * 6  LetterBlox does not have 2-letter words
    /*for(int iter = 0; iter < 12; iter++){
        int firstInt = rand() % 6 + 0;
        int secondInt = rand() % 6 + 0;
        word += letters[firstInt];
        word += letters[secondInt];
        if(find(used_words.begin(), used_words.end(), word) == used_words.end()){ //if not found, enter it
            GenerateKey(keycodes.find(letters[firstInt])->second, TRUE);
            Sleep(1);
            GenerateKey(keycodes.find(letters[secondInt])->second, TRUE);
            Sleep(1);
            GenerateKey(VK_RETURN, TRUE);
            Sleep(1);
            used_words.push_back(word);
        }
        else{ //else, make a new word
            continue;
        }
    }
    Sleep(100);*/
    //3! * 6
    for(int iter = 0; iter < 36; iter++){
        int firstInt = rand() % 6 + 0;
        int secondInt = rand() % 6 + 0;
        int thirdInt = rand() % 6 + 0;
        word += letters[firstInt];
        word += letters[secondInt];
        word += letters[thirdInt];
        if(find(used_words.begin(), used_words.end(), word) == used_words.end()){ //if not found, enter it
            GenerateKey(keycodes.find(letters[firstInt])->second, TRUE);
            Sleep(1);
            GenerateKey(keycodes.find(letters[secondInt])->second, TRUE);
            Sleep(1);
            GenerateKey(keycodes.find(letters[thirdInt])->second, TRUE);
            Sleep(100);
            GenerateKey(VK_RETURN, TRUE);
            Sleep(1);
            used_words.push_back(word);
        }
        else{ //else, make a new word
            continue;
        }
    }
    Sleep(100);
    //4! * 6
    for(int iter = 0; iter < 144; iter++){
        int firstInt = rand() % 6 + 0;
        int secondInt = rand() % 6 + 0;
        int thirdInt = rand() % 6 + 0;
        int fourthInt = rand() % 6 + 0;
        word += letters[firstInt];
        word += letters[secondInt];
        word += letters[thirdInt];
        word += letters[fourthInt];
        if(find(used_words.begin(), used_words.end(), word) == used_words.end()){ //if not found, enter it
            GenerateKey(keycodes.find(letters[firstInt])->second, TRUE);
            Sleep(1);
            GenerateKey(keycodes.find(letters[secondInt])->second, TRUE);
            Sleep(1);
            GenerateKey(keycodes.find(letters[thirdInt])->second, TRUE);
            Sleep(1);
            GenerateKey(keycodes.find(letters[fourthInt])->second, TRUE);
            Sleep(100);
            GenerateKey(VK_RETURN, TRUE);
            Sleep(1);
            used_words.push_back(word);
        }
        else{ //else, make a new word
            continue;
        }
    }
    Sleep(100);
    //5! * 6
    for(int iter = 0; iter < 720; iter++){
        int firstInt = rand() % 6 + 0;
        int secondInt = rand() % 6 + 0;
        int thirdInt = rand() % 6 + 0;
        int fourthInt = rand() % 6 + 0;
        int fifthInt = rand() % 6 + 0;
        word += letters[firstInt];
        word += letters[secondInt];
        word += letters[thirdInt];
        word += letters[fourthInt];
        word += letters[fifthInt];
        if(find(used_words.begin(), used_words.end(), word) == used_words.end()){ //if not found, enter it
            GenerateKey(keycodes.find(letters[firstInt])->second, TRUE);
            Sleep(1);
            GenerateKey(keycodes.find(letters[secondInt])->second, TRUE);
            Sleep(1);
            GenerateKey(keycodes.find(letters[thirdInt])->second, TRUE);
            Sleep(1);
            GenerateKey(keycodes.find(letters[fourthInt])->second, TRUE);
            Sleep(1);
            GenerateKey(keycodes.find(letters[fifthInt])->second, TRUE);
            Sleep(100);
            GenerateKey(VK_RETURN, TRUE);
            Sleep(1);
            used_words.push_back(word);
        }
        else{ //else, make a new word
            continue;
        }
    }
    Sleep(100);
    //6! * 6
    for(int iter = 0; iter < 4320; iter++){
        int firstInt = rand() % 6 + 0;
        int secondInt = rand() % 6 + 0;
        int thirdInt = rand() % 6 + 0;
        int fourthInt = rand() % 6 + 0;
        int fifthInt = rand() % 6 + 0;
        int sixthInt = rand() % 6 + 0;
        word += letters[firstInt];
        word += letters[secondInt];
        word += letters[thirdInt];
        word += letters[fourthInt];
        word += letters[fifthInt];
        word += letters[sixthInt];
        if(find(used_words.begin(), used_words.end(), word) == used_words.end()){ //if not found, enter it
            GenerateKey(keycodes.find(letters[firstInt])->second, TRUE);
            Sleep(1);
            GenerateKey(keycodes.find(letters[secondInt])->second, TRUE);
            Sleep(1);
            GenerateKey(keycodes.find(letters[thirdInt])->second, TRUE);
            Sleep(1);
            GenerateKey(keycodes.find(letters[fourthInt])->second, TRUE);
            Sleep(1);
            GenerateKey(keycodes.find(letters[fifthInt])->second, TRUE);
            Sleep(1);
            GenerateKey(keycodes.find(letters[sixthInt])->second, TRUE);
            Sleep(100);
            GenerateKey(VK_RETURN, TRUE);
            Sleep(1);
            used_words.push_back(word);
        }
        else{ //else, make a new word
            continue;
        }
    }
    return 0;
}
