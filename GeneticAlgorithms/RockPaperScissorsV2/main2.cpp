#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int>::iterator p_p_t;
vector<int>::iterator p_p_t_copy;
vector<int> previous_player_throws;
int search_amount = 4;

vector<int>::iterator s_p_t;
vector<int> short_player_throws;
int next_player_throw;

void computer_throw(){
    int comp_throw;
    for(p_p_t = previous_player_throws.begin(); p_p_t != previous_player_throws.end(); p_p_t++){ //loop over all previous throws by player
        if(short_player_throws.size() < search_amount){ //get the last 4 throws
            short_player_throws.push_back(*p_p_t); //push them onto short_player_throws
        }
    }
    int iter = 0;
    //Breakdown of the loop:
    //1) set the s_p_t (short_player_throw) iterator to where the first int of short_player_throws appears in previous_player_throws
    //2) make sure the value of s_p_t (pointing to an int in previous_player_throws) is equal to the value in short_player_throws
    //3) tick s_p_t, check the next item
    //the loop will end when the value in short_player_throws does not equal the one in previous_player_throws
    for(s_p_t = find(previous_player_throws.begin(), previous_player_throws.end(), short_player_throws[0]); *s_p_t == short_player_throws[iter]; s_p_t++){
        cout << *s_p_t << endl;
        continue; //this is just to set s_p_t to the last matching value
    }
    s_p_t++; //get the value after the last matching value
    switch(*s_p_t){
        case 1:
            comp_throw = 2;
        case 2:
            comp_throw = 3;
        case 3:
            comp_throw = 1;
    }
    cout << comp_throw << endl;
}

int main(){
    previous_player_throws.push_back(2);
    previous_player_throws.push_back(1);
    previous_player_throws.push_back(3);
    previous_player_throws.push_back(3);
    //previous_player_throws.push_back(1);
    previous_player_throws.push_back(2);
    previous_player_throws.push_back(1);
    previous_player_throws.push_back(3);
    previous_player_throws.push_back(3);
    //previous_player_throws.push_back(1);
    computer_throw();
    return 0;
}
