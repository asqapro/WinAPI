#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;

class player_class{
    public:

    int class_type;
    int stat_points; //5 earned per level, distribute to the different modifiers
    int current_level;
    //four different stats that can be increased
    int str; //strength for melee attacks
    int intellect; //intellect for magic attacks
    int consti; //consitution for health
    int dex; //dexterity for dodging and criticals

    int health; //player health
    int mana; //player mana (for spells)

    player_class();
    ~player_class();
    void level();
    void fight(player_class opponent);

};
vector<player_class> log;

player_class::player_class(){
    class_type = rand() % 2 + 1; //mage, warrior
    stat_points = 5;
    str = 5;
    intellect = 5;
    dex = 5;
    consti = 5;
    health = consti * 15;
    current_level = 0;
    level();
}
player_class::~player_class(){
}

bool operator == (player_class const& v1, player_class const& v2){
    return (v1.str == v2.str) && (v1.intellect == v2.intellect) && (v1.consti == v2.consti) && (v1.dex == v2.dex) && (v1.health == v2.health) && (v1.mana == v2.mana);
}

void player_class::level(){
    current_level++;
    int stat;
    for(int iter = 0; iter < stat_points; iter++){
        stat = rand() % 4 + 1;
        switch(stat){
            case 1: //increase str
            {
                str++;
            }
            case 2: //increase intellect
            {
                intellect++;
            }
            case 3: //increase consitution
            {
                consti++;
            }
            case 4: //increase dexterity
            {
                dex++;
            }
        }
    }
    health = consti * 15;
}

vector<player_class> population;
vector<player_class>::iterator popu, popu2;

void player_class::fight(player_class opponent){
    bool crit1;
    bool crit2;

    int melee_damage1 = this->str;
    int mag_damage1 = this->intellect*1.5;

    int melee_damage2 = opponent.str;
    int mag_damage2 = opponent.intellect*1.5;

    while(this->health > 0 && opponent.health > 0){
        crit1 = (rand() % 100 + this->dex == rand() % 100 + this->dex);
        crit2 = (rand() % 100 + opponent.dex == rand() % 100 + opponent.dex);
        if(crit1){
            melee_damage1 *= 3;
            mag_damage1 *= 3;
        }
        if(crit2){
            melee_damage2 *= 3;
            mag_damage2 *= 3;
        }
        switch(this->class_type){
            case 1: //mage
            {
                if(this->mana > 0){
                    opponent.health -= mag_damage1;
                    this->mana -= 25;
                }
                else{
                    opponent.health -= melee_damage1;
                }
            }
            case 2: //warrior
            {
                opponent.health -= melee_damage1;
            }
        }
        switch(opponent.class_type){
            case 1: //mage
            {
                if(opponent.mana > 0){
                    this->health -= mag_damage2;
                    opponent.mana -= 25;
                }
                else{
                    this->health -= melee_damage2;
                }
            }
            case 2: //warrior
            {
                this->health -= melee_damage2;
            }
        }
    }
    if(this->health <= 0 && opponent.health <= 0){
    }
    else if(this->health <= 0){
        for(popu2 = population.begin(); popu2 != population.end(); ++popu2){
            if(*popu2 == *this){
                *popu2 = opponent; //replace the loser in the population with the victor
                break;
            }
        }
        opponent.level();
        log.push_back(opponent);
        log.push_back(*this);
        this->level();
    }
    else if(opponent.health <= 0){
        for(popu2 = population.begin(); popu2 != population.end(); ++popu2){
            if(*popu2 == opponent){
                *popu2 = *this; //replace the loser in the population with the victor
                break;
            }
        }
        this->level();
        log.push_back(*this);
        log.push_back(opponent);
        opponent.level();
    }

}

void setup(){
    for(int iter = 0; iter < 1000; iter++){
        player_class player;
        population.push_back(player);
    }
}

vector<player_class> battle_pool;

void battle(){
    battle_pool = population;
    for(unsigned int iter = 0; iter < population.size()/2; iter++){
        int a = rand() % battle_pool.size() + 1;
        int b = rand() % battle_pool.size() + 1;
        if(a == b){
            while(a == b){
                b = rand() % battle_pool.size() + 1;
            }
        }
        player_class fighterA = battle_pool[a];
        player_class fighterB = battle_pool[b];
        fighterA.fight(fighterB);
        battle_pool.erase(find(battle_pool.begin(), battle_pool.end(), fighterA));
        battle_pool.erase(find(battle_pool.begin(), battle_pool.end(), fighterB));
    }
}

string convert(int type){
    switch(type){
        case 1:
        {
            return "mage";
        }
        case 2:
        {
            return "warrior";
        }
    }
}

int main()
{
    srand (time(NULL));
    setup();
    int counter = 0;
    while(counter < 1000){
        battle();
        cout << "battle " << counter << endl;
        counter++;
    }
    for(popu = population.begin(); popu != population.end(); ++popu){
        player_class person = *popu;
        cout << convert(person.class_type) << " class" << endl;
        cout << person.health << " health" << endl;
        cout << person.str << " strength" << endl;
        cout << person.intellect << " intellect" << endl;
        cout << person.dex << "dexterity" << endl;
        cout << endl << endl;
    }
    /*int count = 0;
    counter = 0;
    for(popu = log.begin(); popu != log.end(); ++popu){
        if(count >= 2){
            count = 0;
            cout << endl << endl << endl;
        }
        player_class person = *popu;
        cout << "battle: " << counter << endl;
        cout << person.health << " health" << endl;
        cout << person.str << " strength" << endl;
        cout << person.intellect << " intellect" << endl;
        cout << person.dex << " dexterity" << endl;
        cout << endl;
        count++;
        counter++;
        if(counter >= 1000){
            break;
        }
    }*/
    return 0;
}
