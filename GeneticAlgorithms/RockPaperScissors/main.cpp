#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

int find_amount = 4;

vector<string> previous_throws_long; //complete list of previous throws
vector<string> previous_throws_short; //created when calculating what to throw next, compared against _long
vector<string>::iterator string_iter;

string c_throw;

void computer_throw(){
    bool find_throw;
    c_throw.clear();
    if(previous_throws_long.size() < find_amount){
        int to_throw = rand() % 3 + 1;
        switch(to_throw){
            case 1:
            {
                c_throw = "rock";
                cout << "computer throws " << c_throw << endl;
                break;
            }
            case 2:
            {
                c_throw = "paper";
                cout << "computer throws " << c_throw << endl;
                break;
            }
            case 3:
            {
                c_throw = "scissors";
                cout << "computer throws " << c_throw << endl;
                break;
            }
        }
    }
    else{
        for(int iter = previous_throws_long.size()-find_amount; iter < previous_throws_long.size(); iter++){
            previous_throws_short.push_back(previous_throws_long[iter]); //get last 4 (or less if that amount fails) throws
        }
        for(int iter2 = 0; iter2 < previous_throws_short.size()-1; iter2++){
            string_iter = find(previous_throws_long.begin(), previous_throws_long.end(), previous_throws_long[iter2]);
            string_iter++;
            if(*string_iter == previous_throws_long[iter2+1]){
                find_throw = true;
                string_iter++;
                if(*string_iter == "rock"){
                    c_throw = "paper";
                }
                else if(*string_iter == "paper"){
                    c_throw = "scissors";
                }
                else if(*string_iter == "scissors"){
                    c_throw = "rock";
                }
            }
            else{
                find_throw = false;
                break;
            }
        }
        if(find_throw){
            find_amount = 4;
            cout << "computer throws " << c_throw << endl;
        }
        else{
            find_amount--;
            computer_throw();
        }
        previous_throws_short.clear();
    }
}

string p_throw;
void player_throw(){
    p_throw.clear();
    cout << "Rock, paper, or scissors? ";
    cin >> p_throw;
    previous_throws_long.push_back(p_throw);
}

void compare(){
    if(c_throw == "rock"){
        if(p_throw == "rock"){
            cout << "tie" << endl;
        }
        if(p_throw == "paper"){
            cout << "player wins" << endl;
        }
        if(p_throw == "scissors"){
            cout << "computer wins" << endl;
        }
    }
    else if(c_throw == "paper"){
        if(p_throw == "rock"){
            cout << "computer wins" << endl;
        }
        if(p_throw == "paper"){
            cout << "tie" << endl;
        }
        if(p_throw == "scissors"){
            cout << "player wins" << endl;
        }
    }
    else if(c_throw == "scissors"){
        if(p_throw == "rock"){
            cout << "player wins" << endl;
        }
        if(p_throw == "paper"){
            cout << "computer wins" << endl;
        }
        if(p_throw == "scissors"){
            cout << "tie" << endl;
        }
    }
}

int main()
{
    srand(time(NULL));
    while(true){
        player_throw();
        computer_throw();
        compare();
    }
    return 0;
}
