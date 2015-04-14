#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>

using namespace std;

int player_wins = 0;
int computer_wins = 0;
int ties = 0;
int difficulty_level = 1;

vector<int> previous_player_throws;

string r_p_s_list[] = {"rock", "paper", "scissors"};

int search_prev_throws(){
    if(previous_player_throws.size() < 1){
        return -1;
    }
    int pattern_length;
    if(difficulty_level == -100){
        pattern_length = previous_player_throws.size()-1;
    }
    else{
        pattern_length = difficulty_level;
    }
    if((unsigned)pattern_length >= previous_player_throws.size()){
        pattern_length = previous_player_throws.size()/2;
    }
    int close_prev_throws[pattern_length];
    for(int iter = 0; iter < pattern_length; iter++){
        close_prev_throws[iter] = previous_player_throws[previous_player_throws.size()-(pattern_length-iter)];
    }
    vector<int> matched_patterns;
    int total_matched = 0;
    int pattern_index = 0;
    for(unsigned int p_throw = 0; p_throw < (previous_player_throws.size()-1); p_throw++){
        if(previous_player_throws[p_throw] == close_prev_throws[total_matched]){
            total_matched += 1;
        }
        else{
            if(total_matched >= pattern_length/2){
                for(int weight = 0; weight < total_matched; weight++){
                    matched_patterns.push_back(previous_player_throws[p_throw+1]);
                }
                total_matched = 0;
            }
        }
        if(total_matched >= pattern_length){
            for(int weight = 0; weight < total_matched; weight++){
                matched_patterns.push_back(previous_player_throws[p_throw+1]);
            }
            total_matched = 0;
        }
    }
    int rock_matches = 0;
    int paper_matches = 0;
    int scissors_matches = 0;
    for(unsigned int pattern_count = 0; pattern_count < matched_patterns.size(); pattern_count++){
        if(matched_patterns[pattern_count] == 0){
            rock_matches++;
        }
        if(matched_patterns[pattern_count] == 1){
            paper_matches++;
        }
        if(matched_patterns[pattern_count] == 2){
            scissors_matches++;
        }
    }
    if(rock_matches > paper_matches && rock_matches > scissors_matches){
        return 0;
    }
    else if(paper_matches > rock_matches && paper_matches > scissors_matches){
        return 1;
    }
    else if(scissors_matches > paper_matches && scissors_matches > rock_matches){
        return 2;
    }
    else if(rock_matches == paper_matches){
        return rand() % 2 + 0;
    }
    else if(paper_matches == scissors_matches){
        return rand() % 2 + 1;
    }
    else if(rock_matches == scissors_matches){
        int random_num;
        while((random_num = rand() % 3 + 0) == 1){
            continue;
        }
        return random_num;
    }
    else{
        return -1;
    }
}

void c_win(){
    cout << "Computer wins." << endl;
    computer_wins++;
    cout << "Current win count for computer: " << computer_wins << endl;
}

void p_win(){
    cout << "Player wins." << endl;
    player_wins++;
    cout << "Current win count for player: " << player_wins << endl;
}

void tie(){
    cout << "Tie." << endl;
    ties++;
    cout << "Current tie count: " << ties << endl;
}

void who_won(int p_throw, int c_throw){
    cout << "Computer throws: " << r_p_s_list[c_throw] << endl;
    cout << "Player throws: " << r_p_s_list[p_throw] << endl;
    if(c_throw == -1){
        cout << "Error with computer's throw" << endl;
        return;
    }
    if(p_throw == 0){
        if(c_throw == 0){
            tie();
        }
        else if(c_throw == 1){
            c_win();
        }
        else if(c_throw == 2){
            p_win();
        }
    }
    else if(p_throw == 1){
        if(c_throw == 0){
            p_win();
        }
        else if(c_throw == 1){
            tie();
        }
        else if(c_throw == 2){
            c_win();
        }
    }
    else if(p_throw == 2){
        if(c_throw == 0){
            c_win();
        }
        else if(c_throw == 1){
            p_win();
        }
        else if(c_throw == 2){
            tie();
        }
    }
    else{
        cout << "Something went wrong with player throw" << endl;
        return;
    }
}

int comp_choose_throw(){
    int next_p_throw = search_prev_throws();
    if(next_p_throw == 0){
        return 1;
    }
    else if(next_p_throw == 1){
        return 2;
    }
    else if(next_p_throw == 2){
        return 0;
    }
    else{
        return rand() % 3 + 0;
    }
}

int main()
{
    cout << "Choose your difficulty level: ";
    cin >> difficulty_level;
    if(difficulty_level < 1 && difficulty_level != -100){
        cout << "Difficulty level cannot be below 1, setting to 1." << endl;
        difficulty_level = 1;
    }
    else if(difficulty_level == -100){
        cout << "Difficulty level set to hardest setting." << endl;
    }
    while(true){
        string player_throw_str;
        int player_throw;
        int computer_throw;
        cout << "Rock, paper, or scissors? ";
        cin >> player_throw_str;
        if(player_throw_str != "rock" && player_throw_str != "paper" && player_throw_str != "scissors"){
            cout << "Invalid input." << endl;
            continue;
        }
        if(player_throw_str == "rock"){
            player_throw = 0;
        }
        else if(player_throw_str == "paper"){
            player_throw = 1;
        }
        else if(player_throw_str == "scissors"){
            player_throw = 2;
        }
        computer_throw = comp_choose_throw();
        previous_player_throws.push_back(player_throw);
        who_won(player_throw, computer_throw);
    }
    srand(time(NULL));
    return 0;
}
