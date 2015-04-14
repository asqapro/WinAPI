#include <iostream>

using namespace std;

class creature{
    public:
    int vitality;
    int health;

    int strength;
    int damage;

    int wisdom;
    int magic;

    int wins;
    int losses;

    creature(int, int, int);
};

void setup(int vitality, int strength, int wisdom){

}

void battle(creature c_roster[], string params){

}

void eliminate(creature c_roster[], string params){

}

void reproduce(creature c1, creature c2, string params){

}

string get_func(string func_name, string complete){
    int func_start_index;
    int open_block;
    int open_block_prev = 0;
    int close_block;
    int close_block_prev;
    int func_end_index = 0;
    int brack_count = 0;

    func_start_index = complete.find(func_name);
    if((unsigned)func_start_index == string::npos){
        return "err";
    }
    open_block = complete.find("{", func_start_index);
    while((unsigned)open_block != string::npos){
        brack_count++;
        open_block_prev = open_block;
        open_block = complete.find("{", open_block_prev);
    }
    close_block = complete.find("}", open_block_prev);
    while((unsigned)close_block != string::npos && brack_count > 0){
        brack_count--;
        close_block_prev = close_block;
        close_block = complete.find("}", open_block_prev);
    }

    return complete.substr(func_start_index, func_end_index);
}

int main()
{
    cout << "Either enter your own genetic algorithm, or a directory to a file containing it." << endl;
    cout << "Enter \'STOP\' after you have entered either the directory or code." << endl;
    string line;
    string complete;
    while(getline(cin, line) && line != "STOP"){
        complete += line;
        complete += "\n";
    }
    if(get_func("setup", complete) == "err"){
        cout << "A setup function is required. Name it \'setup\'." << endl;
    }
    if(get_func("battle", complete) == "err"){
        cout << "A battle function is required. Name it \'battle\'." << endl;
    }
    if(get_func("eliminate", complete) == "err"){
        cout << "An eliminate function is required. Name it \'eliminate\'." << endl;
    }
    if(get_func("reproduce", complete) == "err"){
        cout << "A reproduce function is required. Name it \'reproduce\'." << endl;
    }

    //to translate string to code:
    //parse string same as compiler
    return 0;
}
