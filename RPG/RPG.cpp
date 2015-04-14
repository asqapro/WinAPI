#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <windows.h>
#include <algorithm>
#include <map>
#include <typeinfo>
#include <iterator>
//#include "RPG.pb.h"

using namespace std;

void save();
void load();
void char_create();
void alive();
void dead();
void mon_dead();
void base();
void battle();
void dungeon();
void explore();
void story();
void enchant();  //Implemented later
void alchemize(); //Implemented later

struct player{
    int money;
    string race_class;
    string player_race;
    string player_class;
    int health;
    bool defending;
    int max_health;
    int exp;
    int level;
    int base_dmg;
    int defense;
    int mana;
    int stamina;
    int crit;
    int head;
    int chest;
    int arms;
    int weapon;
    int legs;
    int feet;
    vector<string> inventory;

    void level_up(){
        max_health += 5;
        health = max_health;
        level++;
        if(!mana){
            stamina += 5;
        }
        else{
            mana += 5;
        }
    }

    void human(){
        //string special_race_abil "run if low health";
        player_race = "human";
    }

    void orc(){
        //string special_race_abil = "extra dmg";
        player_race = "orc";
    }

    void elf(){
        //string special_race_abil = "always escape battles";
        player_race = "elf";
    }
    void rogue(){
        //string special_proff_abil = "avoid battles";
        stamina = 100;
        base_dmg = 10;
        crit = 20;
        health = 35;
        max_health = 35;
        defense = 10;
        player_class = "rogue";
        race_class = player_race+"rogue";
    }
    void warrior(){
        //string special_proff_abil = "heavy items";
        stamina = 100;
        base_dmg = 15;
        health = 55;
        max_health = 55;
        defense = 20;
        player_class = "warrior";
        race_class = player_race+"warrior";
    }
    void mage(){
        //string special_proff_abil = "magic";
        base_dmg = 20;
        health = 40;
        max_health = 40;
        mana = 100;
        defense = 5;
        player_class = "mage";
        race_class = player_race+"mage";
    }
}character;

struct monster{
    int money_drop;
    int rep_count;
    int bi_count;
    int hum_count;
    int hy_count;
    vector<string> count;
    int health;
    bool defending;
    int max_health;
    int speed;
    int exp_drop;
    int stamina;
    int max_stamina;
    int mana;
    int max_mana;
    int base_dmg;
    int defense;
    int level;
    int freq;
    string rand_item;
    string name;
    vector<string> item_drop_list;

    void level_up(){
        level += 1;
        if(!mana){
            max_stamina += 5;
        }
        else{
            max_mana += 5;
        }
    }

    void item_drop(){
        int drop_rate1 = rand() % 5 + 1;
        int drop_rate2 = rand() % 5 + 1;
        int drop_rate_hy1 = rand() % 10 + 1;
        int drop_rate_hy2 = rand() % 10 + 1;
        int get_rand_item = rand() % 3 + 1;
        if(name=="hybrid"){
            if(drop_rate_hy1==drop_rate_hy2){
                rand_item = item_drop_list[get_rand_item];
            }
            else{
                rand_item = "nothing";
            }
        }
        if(drop_rate1==drop_rate2){
            rand_item = item_drop_list[get_rand_item];
        }
        else{
            rand_item = "nothing";
        }
    }

    void reptile(){
        base_dmg = 15;
        stamina = 100;
        max_stamina = 100;
        health = 45;
        max_health = 45;
        defense = 15;
        speed = 2;
        exp_drop = 35;
        money_drop = 500 + (level*100);
        name = "reptile";
        item_drop_list.push_back("health potion");
        item_drop_list.push_back("battle axe");
        item_drop_list.push_back("heavy chestplate");
        //frequency = 30
    }
    void bird(){
        base_dmg = 8;
        stamina = 50;
        max_stamina = 50;
        health = 30;
        max_health = 30;
        defense = 5;
        speed = 15;
        exp_drop = 15;
        name = "bird";
        money_drop = 300 + (level*100);
        item_drop_list.push_back("health potion");
        item_drop_list.push_back("dagger");
        item_drop_list.push_back("light chestplate");
        //frequency = 45
    }
    void humanoid(){
        base_dmg = 13;
        mana = 100;
        max_mana = 100;
        health = 40;
        max_health = 40;
        defense = 10;
        speed = 10;
        exp_drop = 20;
        name = "humanoid";
        money_drop = 500 + (level*100);
        item_drop_list.push_back("health potion");
        item_drop_list.push_back("wooden staff");
        item_drop_list.push_back("arcane chestplate"); //to be made more arcaney
        //frequency = 20
    }
    void hybrid(){
        base_dmg = 20;
        stamina = 120;
        max_stamina = 120;
        health = 60;
        max_health = 60;
        defense = 20;
        speed = 7;
        exp_drop = 55;
        money_drop = 700 + (level*100);
        name = "hybrid";
        item_drop_list.push_back("health potion");
        item_drop_list.push_back("potent health potion");
        item_drop_list.push_back("mystery health potion");
        //frequency = 5
    }
    void elite(){
        base_dmg = 30;
        stamina = 150;
        max_stamina = 150;
        health = 100;
        max_health = 100;
        defense = 30;
        speed = 15;
        exp_drop = 100;
        money_drop = 2000;
        name = "elite";
        item_drop_list.push_back("potent health potion");
    }
    void boss(){
        base_dmg = 50;
        stamina = 180;
        max_stamina = 180;
        health = 300;
        max_health = 300;
        defense = 50;
        speed = 30;
        exp_drop = 300;
        money_drop = 10000;
        name = "Boss name here";
        item_drop_list.push_back("special undefined item");
    }
}mob;

struct char_battle_setup{
    int dmg;
    string abil_name;
    //string effects
    void basic_attack(){
        abil_name = "basic attack";
        if(!character.crit){
            dmg = rand() % (character.base_dmg*2+(character.level*3)) + (character.base_dmg*1+(character.level*3));
        }
        else{
            int base = rand() % (character.base_dmg*2+(character.level*3)) + (character.base_dmg*1+(character.level*3)); //Rethink, less chance higher level
            int second_base = rand() % (character.base_dmg*2+(character.level*3)) + (character.base_dmg*1+(character.level*3));
            if(base == second_base){
                dmg = character.crit;
            }
            else{
                dmg = base;
            }
        }
        //effects = "None"
    }
    void magic(){ //Mage only
        abil_name = "magic bolt";
        dmg = rand() % (character.base_dmg*2+(character.level*3)) + (character.base_dmg*1+(character.level*3));
        dmg += 10;
        character.mana -= 20*character.level;
        //effects = "Lose mana based on char level"
    }
    void power_swing(){ //Warrior only
        abil_name = "power swing";
        dmg = rand() % (character.base_dmg*2+(character.level*3)) + (character.base_dmg*1+(character.level*3));
        dmg += 10;
        character.stamina -= 20*character.level;
        //effects = "Lose stamina based on char level"
    }

    void attack(){
        if(mob.defending){
            cout << "The monster's defense removes " << mob.defense << " points from your attack." << endl;
            dmg -= mob.defense;
            if(dmg < 0){
                dmg = 0;
            }
        }
        mob.health -= dmg;
        if(mob.health < 0){
            mob.health = 0;
        }
        cout << "The monster's health drops to " << mob.health << "." << endl;
        Sleep(800);
        if(mob.health<=0){
            mon_dead();
        }
    }
    void defend(){
        cout << "You assume a defensive stance." << endl;
        character.defending = true;
    }

    void choice(){
        while (true){
            string spec_or_base;
            string defend_attack;
            cin.clear(); cin.sync();
            cout << "Do you want to defend or attack? ";
            cin >> defend_attack;
            if(defend_attack=="defend"){
                defend();
                break;
            }
            else if(defend_attack=="attack"){
                cout << "What attack do you want to use?" << endl;
                cout << "Basic, power (warriors), or magic (mages): ";
                cin.clear(); cin.sync();
                cin >> spec_or_base;
                if(spec_or_base=="power"){
                    if(character.player_class!="mage"){
                        if(character.stamina>0){
                            power_swing();
                            cout << "You attack with a " << abil_name << ", dealing " << dmg << " damage." << endl;
                        }
                        else{
                            cout << "You don't have enough stamina." << endl;
                            continue;
                        }
                    }
                    else{
                        cout << "You can't use that attack." << endl;
                        continue;
                    }
                }
                else if(spec_or_base=="magic"){
                    if(character.player_class=="mage"){
                        if(character.mana>0){
                            magic();
                            cout << "You attack with a " << abil_name << ", dealing " << dmg << " damage." << endl;
                        }
                        else{
                            cout << "You don't have enough mana." << endl;
                            continue;
                        }
                    }
                    else{
                        cout << "You can't use that attack." << endl;
                        continue;
                    }
                }
                else if(spec_or_base=="basic"){
                    basic_attack();
                    cout << "You attack with a " << abil_name << ", dealing " << dmg << " damage." << endl;
                }
                else{
                    cout << "Choose 'basic', 'power', or 'magic'." << endl;
                }
                attack();
                break;
            }
            else{
                cout << "Please choose \'attack\' or \'defend\'." << endl;
            }
        }
    }
}char_battle;

struct mon_battle_setup{
    int dmg;
    string abil_name;
    //string effects
    void basic_attack(){
        abil_name = "basic attack";
        dmg = rand() % (mob.base_dmg*2+(mob.level*3)) + (mob.base_dmg*1+(mob.level*3));
    }
    void magic(){
        abil_name = "magic bolt";
        dmg = rand() % (mob.base_dmg*2+(mob.level*3)) + (mob.base_dmg*1+(mob.level*3));
        dmg += 10;
        mob.mana -= 20*mob.level;
        //effects = "Lose mana based on monster level"
    }
    void power_swing(){
        abil_name = "power swing";
        dmg = rand() % (mob.base_dmg*2+(mob.level*3)) + (mob.base_dmg*1+(mob.level*3));
        dmg += 10;
        mob.stamina -= 20*mob.level;
        //effects = "Lose stamina based on monster level"
    }
    void attack(){
        if(character.defending){
            cout << "Your defense removes " << character.defense << " points from the monster's attack." << endl;
            dmg -= character.defense;
            if(dmg < 0){
                dmg = 0;
            }
        }
        character.health -= dmg;
        if(character.health < 0){
            character.health = 0;
        }
        cout << "Your health drops to " << character.health << "." << endl;
        Sleep(800);
        if(character.health<=0){
            cout << "You have died." << endl;
            dead();
        }
    }
    void defend(){
        cout << "The monster assumes a defensive stance." << endl;
        mob.defending = true;
    }
    void choice(){
        int spec_or_base = rand() % 10 + 1;
        if(mob.health*2<mob.max_health){ //Change up
            defend();
            return;
        }
        else if(spec_or_base>5 && mob.name!="humanoid" && mob.stamina>0){ //If mob is phys and has enough stamina
            power_swing();
            cout << "The monster attacks you with a " << abil_name << ", dealing " << dmg << " damage." << endl;
            Sleep(1200);
        }
        else if(spec_or_base>5 && mob.mana>0){ //Doesn't need to check for mob, mana will be 0 if not magic
            magic();
            cout << "The monster attacks you with a " << abil_name << ", dealing " << dmg << " damage." << endl;
            Sleep(1200);
        }
        else{
            basic_attack();
            cout << "The monster attacks you with a " << abil_name << ", dealing " << dmg << " damage." << endl;
            Sleep(1200);
        }
        attack();
    }
}mon_battle;

struct NPCs{
    typedef map<string, int> stringIntmap;
    stringIntmap smith_items_to_sell;
    stringIntmap smith_items_to_buy;

    void set_prices(){
        smith_items_to_sell["heavy chestplate"]=3000;
        smith_items_to_sell["light chestplate"]=3000; //Just a base example, more to be added
        smith_items_to_sell["arcane chestplate"]=3000;

        smith_items_to_buy["heavy chestplate"]=1000;
        smith_items_to_buy["light chestplate"]=1000; //NPCs have families to support
        smith_items_to_buy["light chestplate"]=1000;

        //trader_items_to_sell;

        //trader_items_to_buy;

        //banker_store_prices;

        //banker_extract_prices;

        //alchemist_items_to_buy;

        //alchemist_items_to_sell;
    }

    void blacksmith(){ //Buy and sell equipment
        string bought_item;
        string buy_more;
        cout << "Here you can buy and sell equipment for your character." << endl;
        if(character.money<=0){
            cout << "You have no money to spend." << endl;
            base();
        }
        cout << "Here's a list of items being sold: " << endl;
        stringIntmap::iterator pos;
        for (pos = smith_items_to_sell.begin(); pos != smith_items_to_sell.end(); ++pos) {
            cout << pos->first
                << " : " << pos->second << endl;
        }
        while(true){
            cout << "What do you want to buy? ";
            getline(cin, bought_item);
            if(smith_items_to_sell.find(bought_item)!=smith_items_to_sell.end()){
                if(character.money>=smith_items_to_sell[bought_item]){
                    cout << "You bought " << bought_item << " for " << smith_items_to_sell[bought_item] << " coins." << endl;
                    Sleep(800);
                    while(true){
                        cout << "Do you want to buy anything else?(y/n) ";
                        cin >> buy_more;
                        if(buy_more=="y"){
                            break;
                        }
                        else if(buy_more=="n"){
                            base();
                        }
                        else{
                            cout << "Type 'y' or 'n'." << endl;
                        }
                        cin.clear(); cin.sync();
                    }
                }
                else{
                    cout << "You don't have enough money for that." << endl;
                    Sleep(800);
                    while(true){
                        cout << "Do you want to buy something else?(y/n) ";
                        cin >> buy_more;
                        if(buy_more=="y"){
                            break;
                        }
                        else if(buy_more=="n"){
                            base();
                        }
                        else{
                            cout << "Type 'y' or 'n'." << endl;
                        }
                        cin.clear(); cin.sync();
                    }
                }
            }
            else{
                cout << "That item is not sold here." << endl;
                Sleep(800);
                while(true){
                    cout << "Do you want to buy something else?(y/n) ";
                    cin >> buy_more;
                    if(buy_more=="y"){
                        break;
                    }
                    else if(buy_more=="n"){
                        base();
                    }
                    else{
                        cout << "Type 'y' or 'n'." << endl;
                    }
                    cin.clear(); cin.sync();
                }
            }
            cin.clear(); cin.sync();
        }
    }
    void trader(){ //Buy and sell misc stuff
        cout << "Here you can buy and sell miscellaneous items." << endl;
        if(character.money<=0){
            cout << "You have no money to spend." << endl;
            base();
        }
    }
    void alchemist(){ //Buy and sell potions, poisons, and boosts
        cout << "Here you can buy and sell potions, poisons, and boosts." << endl;
        if(character.money<=0){
            cout << "You have no money to spend." << endl;
            base();
        }
    }
    void banker(){ //Store extra items
        cout << "Here you can store extra items, for a price." << endl;
        if(character.money<=0){
            cout << "You have no money to spend." << endl;
            base();
        }
    }
}npc;

struct useable_items{
    string picked_potion;
    int wear_off;
    vector<string> health_restores;
    vector<string> poisons;
    vector<string> temp_boosts;
    vector<string> perm_boosts;
    vector<string> misc;
    void set_items(){
        health_restores.push_back("health potion");
        health_restores.push_back("potent health potion");
        health_restores.push_back("mystery health potion");
        health_restores.push_back("apple");
        poisons.push_back("sickly grey fish");                  //More to be added of everything, this is just basics
        temp_boosts.push_back("bass");
        temp_boosts.push_back("trout");
        perm_boosts.push_back("rainbow fish");
        misc.push_back("journal");
        misc.push_back("fishing bait");
    }
    void use_potions(){
        vector<string> num_health_pots;
        vector<string> num_boost_pots;
        cout << "Choose from: ";
        for(vector<string>::iterator i = character.inventory.begin(); i != character.inventory.end(); ++i){
            if(find(health_restores.begin(), health_restores.end(), *i) != health_restores.end()){
                num_health_pots.push_back(*i);
            }
            if(find(temp_boosts.begin(), temp_boosts.end(), *i) != temp_boosts.end()){
                num_boost_pots.push_back(*i);
            }
        }
        if(num_boost_pots.size()==0 && num_health_pots.size() != 0){
            for(vector<string>::iterator x = num_health_pots.begin(); x != num_health_pots.end(); x++){
                vector<string>::iterator it = x;
                cout << *x;
                if(++it!=num_health_pots.end()){
                    cout << ", ";
                }
                else{
                    cout << "." << endl;
                }
            }
        }
        else if(num_health_pots.size()==0 && num_boost_pots.size() != 0){
            for(vector<string>::iterator x = num_boost_pots.begin(); x != num_boost_pots.end(); x++){
                vector<string>::iterator it = x;
                cout << *x;
                if(++it!=num_boost_pots.end()){
                    cout << ", ";
                }
                else{
                    cout << "." << endl;
                }
            }
        }
        else if(num_health_pots.size()!=0 && num_boost_pots.size()!=0){
            for(vector<string>::iterator x = num_health_pots.begin(); x != num_health_pots.end(); x++){
                cout << *x << ", ";
            }
            for(vector<string>::iterator i = num_boost_pots.begin(); i != num_boost_pots.end(); i++){
                vector<string>::iterator it = i;
                cout << *i;
                if(++it!=num_boost_pots.end()){
                    cout << ", ";
                }
                else{
                    cout << "." << endl;
                }
            }
        }
        else{
            cout << endl;
            cout << "You have nothing to use." << endl;
            return;
        }
        while(true){
            cout << "Your choice: ";
            cin >> picked_potion;
            if(find(health_restores.begin(), health_restores.end(), picked_potion) != health_restores.end()){
                vector<string>::iterator position = find(character.inventory.begin(), character.inventory.end(), picked_potion);
                if(position != character.inventory.end()){
                    character.inventory.erase(position);
                    if(picked_potion=="health potion"){
                        character.health+=10;
                    }
                    else if(picked_potion=="potent health potion"){
                        character.health+=15;
                    }
                    else if(picked_potion=="mystery potion"){
                        int dmg_o_hp = rand() % 2 + 1;
                        if(dmg_o_hp==1){
                            character.health+=20;
                        }
                        else{
                            character.health-=20; //Ouch
                        }
                    }
                    else{
                        character.health+=5;
                    }
                    break;
                }
            }
            else if(find(temp_boosts.begin(), temp_boosts.end(), picked_potion) != temp_boosts.end()){
                vector<string>::iterator position = find(character.inventory.begin(), character.inventory.end(), picked_potion);
                if(position != character.inventory.end()){
                    character.inventory.erase(position);
                    if(picked_potion=="trout"){
                        wear_off = 3;
                    }
                    else if(picked_potion=="bass"){
                        wear_off = 2;
                    }
                    break;
                }
            }
            else{
                cout << "Pick from the list." << endl;
            }
        }
    }
}items;

struct equips{
    int itemInt;
    map<string, int> itemList;
    vector<string> itemOrder;
    bool headEq;
    bool chestEq;
    bool armsEq;
    bool legsEq;
    bool feetEq;

    string change;
    string repItem;

    void initialize(){
        itemList["none"] = 0;
        itemList["heavy helm"] = 4;        //defence 4
        itemList["heavy chestplate"] = 7; //defence 7
        itemList["heavy gauntlets"] = 5; //defence 5
        itemList["heavy leggings"] = 6; //defence 6
        itemList["heavy boots"] = 3;   //defence 3

        itemOrder.push_back("none");
        itemOrder.push_back("heavy helm");
        itemOrder.push_back("heavy chestplate");
        itemOrder.push_back("heavy gauntlets");
        itemOrder.push_back("heavy leggings");
        itemOrder.push_back("heavy boots");

        itemList["light helm"] = 3;        //defence 3
        itemList["light chestplate"] = 6; //defence 6
        itemList["light gauntlets"] = 4; //defence 4
        itemList["light leggings"] = 5; //defence 5
        itemList["light boots"] = 2;   //defence 2

        itemOrder.push_back("light helm");
        itemOrder.push_back("light chestplate");
        itemOrder.push_back("light gauntlets");
        itemOrder.push_back("light leggings");
        itemOrder.push_back("light boots");

        itemList["arcane helm"] = 2;        //defence 2
        itemList["arcane chestplate"] = 5; //defence 5
        itemList["arcane gauntlets"] = 3; //defence 3
        itemList["arcane leggings"] = 4; //defence 4
        itemList["arcane boots"] = 1;   //defence 1

        itemOrder.push_back("arcane helm");
        itemOrder.push_back("arcane chestplate");
        itemOrder.push_back("arcane gauntlets");
        itemOrder.push_back("arcane leggings");
        itemOrder.push_back("arcane boots");
    }

    void replaceCheck(string place){
        while(true){
            cout << "Replace? (y/n) ";
            cin.clear(); cin.sync();
            cin >> change;
            if(change == "yes"){
                cout << "Replace with? ";
                cin.clear(); cin.sync();
                string item;
                cin >> item;
                replace(place, item);
                return;
            }
            else if(change == "no"){
                return;
            }
            else{
                cout << "Please enter \'yes\' or \'no\'." << endl;
                continue;
            }
        }
    }
    void replace(string place, string item){
        itemInt = itemToInt(item);
        if(place == "head"){
            character.head = itemInt;
            return;
        }
        else if(place == "chest"){
            character.chest = itemInt;
            return;
        }
        else if(place == "arms"){
            character.arms = itemInt;
            return;
        }
        else if(place == "legs"){
            character.legs = itemInt;
            return;
        }
        else if(place == "feet"){
            character.feet = itemInt;
            return;
        }
    }
    string itemToString(int item){
        return itemOrder[item];
    }
    int itemToInt(string item){
        for(int iter = 0; iter < itemOrder.size(); iter++){
            if(item == itemOrder[iter]){
                return iter;
            }
        }
        cout << "Error: item not found." << endl;
        base();
    }
    void equipped(string item, bool pass){
        if(pass){
            cout << "You have equipped " << item << "." << endl;
        }
        else{
            cout << "You were not able to equip " << item << "." << endl;
        }
    }
    void equip(string item){
        itemInt = itemToInt(item);
        if(character.player_class == "warrior"){
            if(itemInt <= 5){
                if(itemInt == 1){
                    if(!headEq){
                        character.head = itemInt;
                        equipped(item, true);
                        return;
                    }
                    else{
                        cout << "You currently have " << item << " equipped." << endl;
                        replaceCheck("head");
                    }
                }
                else if(itemInt == 2){
                    if(!chestEq){
                        character.chest = itemInt;
                        equipped(item, true);
                        return;
                    }
                    else{
                        cout << "You currently have " << item << " equipped." << endl;
                        replaceCheck("chest");
                    }
                }
                else if(itemInt == 3){
                    if(!armsEq){
                        character.arms = itemInt;
                        equipped(item, true);
                        return;
                    }
                    else{
                        cout << "You currently have " << item << " equipped." << endl;
                        replaceCheck("arms");
                    }
                }
                else if(itemInt == 4){
                    if(!legsEq){
                        character.legs = itemInt;
                        equipped(item, true);
                        return;
                    }
                    else{
                        cout << "You currently have " << item << " equipped." << endl;
                        replaceCheck("legs");
                    }
                }
                else if(itemInt == 5){
                    if(!feetEq){
                        character.feet = itemInt;
                        equipped(item, true);
                        return;
                    }
                    else{
                        cout << "You currently have " << item << " equipped." << endl;
                        replaceCheck("feet");
                    }
                }
            }
            else{
                cout << "You may only equip heavy items to your class." << endl;
                equipped(item, false);
            }
        }
        else if(character.player_class == "rogue"){
            if(itemInt > 5 && itemInt <= 10){
                if(itemInt == 6){
                    if(!headEq){
                        character.head = itemInt;
                        equipped(item, true);
                        return;
                    }
                    else{
                        cout << "You currently have " << item << " equipped." << endl;
                        replaceCheck("head");
                    }
                }
                else if(itemInt == 7){
                    if(!chestEq){
                        character.chest = itemInt;
                        equipped(item, true);
                        return;
                    }
                    else{
                        cout << "You currently have " << item << " equipped." << endl;
                        replaceCheck("chest");
                    }
                }
                else if(itemInt == 8){
                    if(!armsEq){
                        character.arms = itemInt;
                        equipped(item, true);
                        return;
                    }
                    else{
                        cout << "You currently have " << item << " equipped." << endl;
                        replaceCheck("arms");
                    }
                }
                else if(itemInt == 9){
                    if(!legsEq){
                        character.legs = itemInt;
                        equipped(item, true);
                        return;
                    }
                    else{
                        cout << "You currently have " << item << " equipped." << endl;
                        replaceCheck("legs");
                    }
                }
                else if(itemInt == 10){
                    if(!feetEq){
                        character.feet = itemInt;
                        equipped(item, true);
                        return;
                    }
                    else{
                        cout << "You currently have " << item << " equipped." << endl;
                        replaceCheck("feet");
                    }
                }
            }
            else{
                cout << "You may only equip heavy items to your class." << endl;
                equipped(item, false);
            }
        }
        else if(character.player_class == "mage"){
            if(itemInt > 10){
                if(itemInt == 11){
                    if(!headEq){
                        character.head = itemInt;
                        equipped(item, true);
                        return;
                    }
                    else{
                        cout << "You currently have " << item << " equipped." << endl;
                        replaceCheck("head");
                    }
                }
                else if(itemInt == 12){
                    if(!chestEq){
                        character.chest = itemInt;
                        equipped(item, true);
                        return;
                    }
                    else{
                        cout << "You currently have " << item << " equipped." << endl;
                        replaceCheck("chest");
                    }
                }
                else if(itemInt == 13){
                    if(!armsEq){
                        character.arms = itemInt;
                        equipped(item, true);
                        return;
                    }
                    else{
                        cout << "You currently have " << item << " equipped." << endl;
                        replaceCheck("arms");
                    }
                }
                else if(itemInt == 14){
                    if(!legsEq){
                        character.legs = itemInt;
                        equipped(item, true);
                        return;
                    }
                    else{
                        cout << "You currently have " << item << " equipped." << endl;
                        replaceCheck("legs");
                    }
                }
                else if(itemInt == 15){
                    if(!feetEq){
                        character.feet = itemInt;
                        equipped(item, true);
                        return;
                    }
                    else{
                        cout << "You currently have " << item << " equipped." << endl;
                        replaceCheck("feet");
                    }
                }
            }
            else{
                cout << "You may only equip arcane items to your class." << endl;
                equipped(item, false);
            }
        }
    }
}equipment;

struct dungeons_setup{
    bool isactive;
    int room_count;
    void enter(){
        room_count = rand() % 20 + 1;
        isactive = true;
    }
    void exit(){
        isactive = false;
        base();
    }
}dungeon_setup;

struct locations{
    bool first_time_abon;
    bool first_time_mon;
    bool first_time_farm;
    bool first_time_boat;
    string rand_house_item;
    int dot_count;
    int dot_stop;

    void create_first_time(){
        first_time_abon = true;
        first_time_boat = true;
        first_time_farm = true;
        first_time_mon = true;
    }

    void fish(){
        vector<string> fish;
        fish.push_back("bass");
        fish.push_back("trout");
        fish.push_back("rainbow fish");
        fish.push_back("sickly grey fish");
        cout << "You sit by the edge of the lake and throw out your line";
        for(dot_count = 1; dot_count <= dot_stop; dot_count++){
                cout <<  ". ";
                Sleep(1200);
            }
        int rand_try = rand() % 3 + 1;
        int rand_try2 = rand() % 3 + 1;
        if(rand_try==rand_try2){
            int rand_caught = rand() % 4 + 1;
            string caught = fish[rand_caught];
            cout << "You caught a " << caught << "." << endl;
            character.inventory.push_back(caught);
        }
        else{
            cout << "Nothing bites and you give up." << endl;
        }
    }

    void abandoned_house(){
        vector<string> house_items;
        string location = "on the side of the path.";
        string inhabitants = "no one.";
        house_items.push_back("health potion");
        house_items.push_back("dagger");
        house_items.push_back("light leggings");
        string special_events = "You find a journal. Entries to be added. You put the journal in your bag.";

        if(first_time_abon==true){
            cout << "You discovered an abandoned house." << endl;
            Sleep(800);
            cout << "It is " << location << endl;
            Sleep(800);
            cout << "There is no one home";
            dot_stop = 3;
            for (dot_count = 1; dot_count <= dot_stop; dot_count++){
                cout <<  ". ";
                Sleep(1200);
            }
            cout << "Wait! You found some dead bodies..." << endl;
            Sleep(800);
            int house_item_get = rand() % house_items.size();
            rand_house_item = house_items[house_item_get];
            cout << "You search the house and find a " << rand_house_item << "." << endl;
            character.inventory.push_back(rand_house_item);
            Sleep(800);
            cout << special_events << endl;
            character.inventory.push_back("journal");
            first_time_abon = false;
        }
        else{
            cout << "You happen upon the abandoned house again." << endl;
        }
    }
    void monster_house(){
        vector<string> house_items;
        string location = "deep in the dark woods.";
        string inhabitants = "no one.";
        string special_events = "The house comes alive and tries to eat you! You manage to escape, but lose a little health.";
        if(first_time_mon==true){
            cout << "You find a large house..." << endl;
            Sleep(800);
            cout << "It is " << location << endl;
            Sleep(800);
            cout << "There is no one home." << endl;
            Sleep(800);
            cout << "You begin to search for any useful items";
            dot_stop = 3;
            for (dot_count = 1; dot_count <= dot_stop; dot_count++){
                cout <<  ". ";
                Sleep(1200);
            }
            cout << endl;
            cout << special_events << endl;
            character.health -= 10;
            first_time_mon = false;
        }
        else{
            cout << "You see the monster house, but avoid it." << endl;
        }
    }
    void farm(){
        vector<string> house_items;
        string location = "in a grassy field. You can see an orchard in the distance.";
        string inhabitants = "a kind woman by the name of Mary.";
        house_items.push_back("apple");
        string special_events = "Mary allows you to take as many apples as you can carry. They will each heal a small amount of health.";
        if(first_time_farm==true){
            cout << "You discover a farm " << location << endl;
            Sleep(800);
            cout << "You meet " << inhabitants << endl;
            Sleep(800);
            cout << special_events << endl;
            Sleep(800);
            cout << "You take 4." << endl;
            for(int i=0;i<4;i++){
                character.inventory.push_back(house_items[0]);
            }
            first_time_farm = false;
        }
        else{
            cout << "You find the farm again, and take an apple." << endl;
            character.inventory.push_back("apple");
        }
    }
    void boathouse(){
        vector<string> house_items;
        string location = "on the edge of a large lake.";
        string inhabitants = "no one.";
        house_items.push_back("wooden staff");
        house_items.push_back("fishing bait");
        string special_events = "You can fish if you want. Do you want to?(y/n) ";
        if(first_time_boat==true){
            cout << "You find a boathouse " << location << endl;
            Sleep(800);
            cout << "There is no one here." << endl;
            Sleep(800);
            int house_item_get = rand() % house_items.size();
            rand_house_item = house_items[house_item_get];
            cout << "You search the place and find " << rand_house_item << "." << endl;
            character.inventory.push_back(rand_house_item);
            Sleep(800);
            cout << special_events;
            string f_o_no;
            cin >> f_o_no;
            while(true){
                if(f_o_no=="y"){
                    fish();
                    break;
                }
                else if(f_o_no=="n"){
                    break;
                }
                else{
                    cout << "Type 'y' or 'n'." << endl;
                }
            }
            first_time_boat = false;
        }
        else{
            string fish_or_no;
            cout << "You find the boathouse." << endl;
            Sleep(800);
            cout << "You see the fishing rod again. Do you want to fish?(y/n) ";
            cin >> fish_or_no;
            while(true){
                if(fish_or_no=="y"){
                    fish();
                }
                else if(fish_or_no=="n"){
                    base();
                }
                else{
                    cout << "Choose 'y' or 'n'." << endl;
                }
            }
        }
    }
}locs;

struct story_lines{
    int progress; //Keep track of what event to show
    string back_story;
    string event1; //Only using one for now, as a base
    string event2; //Need more ideas
    string event3;
    string event4;
    string event5;
    string event6;
    string event7;
    string event8;
    string event9;
    string event10;
    void sit_one(){
        back_story = "You are an adventurer, ready to take on the world.\n"
        "You left your hometown at an early age, feeling like you didn't fit in.\n"
        "You find yourself in a strange land, filled with monsters.\n"
        "You must either fight your way out, or dispose of their leader.\n";
        event1 = "You decide to talk a walk through the woods.\n"
        "As you walk along, you hear a strange sound...\n"
        "It sounds like... Crying?\n"
        "But it's too dark out to go searching, so you head back to camp.\n";
    }
    void sit_two(){
        back_story = "You're a mercenary, roaming the world.\n"
        "Your family was killed when you were young by a monster of a man.\n"
        "You became a contract killer to support yourself.\n"
        "But you soon grew tired of killing your own kind, and set out killing monsters.\n"
        "You must kill enough monsters to satisfy your anger, or avenge your family.\n";
        event1 = "You decide to talk a walk through the woods.\n"
        "As you walk along, you hear a strange sound...\n"
        "It sounds like... Crying?\n"
        "But you don't have time for other people. You heads back to camp.\n";
    }
    void sit_three(){
        back_story = "You are a scientist, trying to reseach a potentially deadly virus.\n"
        "You traveled to this monster-infested land looking for 'samples'.\n"
        "You soon realized that you would have to fight for your research...\n"
        "So you picked up your weapon and screamed to the skies \"FOR SCIENCE!!!\"\n"
        "You need to collect many samples, or steal the virus from their leader.\n";
        event1 = "You decide to talk a walk through the woods.\n"
        "As you walk along, you hear a strange sound...\n"
        "It sounds like... Crying?\n"
        "It must be a weaker mind, succumbing to sadness.\n"
        "You ignore it and head back to camp to continue your research.\n";
    }
    void sit_four(){
        back_story = "You were a king in your old town - a powerful Lord. But make one mistake...\n"
        "Your \"followers\" turned on you as soon as they sensed your weakness.\n"
        "But you will have your revenge. You will return a warrior and kill them all.\n"
        "You will clear this land of monsters or kill their king and take over.\n"
        "\"Born to rule\" is your destiny, and it shall be fulfilled.\n";
        event1 = "You decide to talk a walk through the woods.\n"
        "As you walk along, you hear a strange sound...\n"
        "It sounds like... Crying?\n"
        "Being betrayed has made you suspicious of others.\n"
        "You suspect they are trying to trick you, so you run back to camp.\n";
    }
    void sit_five(){
        back_story = "You heard of this monster-filled land at a young age, and set out for it.\n"
        "There are many monsters to defeat, but you are unfaltering.\n"
        "You won't stop until they're dead, or their leader is defeated.\n"
        "Because you plan to be the best that ever was.\n";
        event1 = "You decide to talk a walk through the woods.\n"
        "As you walk along, you hear a strange sound...\n"
        "It sounds like... Crying?\n"
        "It's obviously not an animal, so not your concern.\n"
        "You return to your camp.\n";
    }
}sits; //Situations

struct easter_eggs{
    string h_sqaure;
    void hatch_eggs(){
        h_sqaure = "a sqaure";
    }
};

int main(){
    //GOOGLE_PROTOBUF_VERIFY_VERSION;
    while(true){
        cin.clear(); cin.sync();
        string reload;
        cout << "Do you want to load a save?(y/n) ";
        cin >> reload;
        if(reload=="y"){
            //load();
            cout << "Redoing." << endl;
            break;
        }
        else if(reload=="n"){
            break;
        }
        else{
            cout << "Choose \"y\" or \"n\"." << endl;
        }
    }
    srand(time(NULL)); //Seed the random number generator
    int situation = rand() % 5 + 1; //Picks a random adventure
    if(situation==1){
        sits.sit_one();
        cout << sits.back_story;
    }
    else if(situation==2){
        sits.sit_two();
        cout << sits.back_story;
    }
    else if(situation==3){
        sits.sit_three();
        cout << sits.back_story;
    }
    else if(situation==4){
        sits.sit_four();
        cout << sits.back_story;
    }
    else{
        sits.sit_five();
        cout << sits.back_story;
    }
    cout << endl; //Spaces out the wall of scenario text from the character creation
    mob.rep_count = 50;
    mob.bi_count = 95;
    mob.hum_count = 50; //Sets up the number of monsters you have to kill to win
    mob.hy_count = 5;
    for(int i=mob.bi_count;i>0;i--){
        mob.count.push_back("bird");
    }
    for(int i=mob.rep_count;i>0;i--){
        mob.count.push_back("reptile");
        mob.count.push_back("humanoid");
    }
    for(int i=mob.hy_count;i>0;i--){
        mob.count.push_back("hybrid");
    }
    equipment.initialize();
    locs.create_first_time(); //Set a true bool value for dealing with locations later
    items.set_items(); //Set up the items lists
    npc.set_prices(); //Set up shop
    char_create(); //Create the character
    character.inventory.push_back("arcane chestplate");
    alive(); //While this function runs, you are "alive", stays within itself
    cout << "Something crashed."; //More a note for more than anything, tells me if I forgot to call inside the alive function
    return 0; //Program ends (should not be reached)
}

void char_create(){
    character.level = 1;
    string pick_race = "";
	string pick_class = "";
	character.head = 0;
    character.chest = 0;
    character.arms = 0;
    character.weapon = 0;
    character.legs = 0;
    character.feet = 0;
	while(true){
        cout << "Pick your race(human, orc, or elf): ";
        cin >> pick_race;
        if(pick_race=="human"){
            character.human();
            break;
        }
        else if(pick_race=="orc"){
            character.orc();
            break;
        }
        else if(pick_race=="elf"){
            character.elf();
            break;
        }
        else{
            cout << "Choose 'human', 'orc', or 'elf'." << endl;
        }
	}
    while(true){
        cout << "Pick your class(warrior, mage, or rogue): ";
        cin >> pick_class;
        if(pick_class=="warrior"){
            character.warrior();
            break;
        }
        else if(pick_class=="rogue"){
            character.rogue();
            break;
        }
        else if(pick_class=="mage"){
            character.mage();
            break;
        }
        else{
            cout << "Pick 'warrior', 'rogue', or 'mage'." << endl;
        }
    }
}

void battle(){
    mob.freq = rand() % 200 + 1;
    string f_mon = mob.count[mob.freq];
    if(f_mon=="bird"){
        mob.bird();
    }
    else if(f_mon=="reptile"){
        mob.reptile();
    }
    else if(f_mon=="humanoid"){
        mob.humanoid();
    }
    else{
        mob.hybrid();
    }
    cout << "You encountered a " << mob.name << "!" << endl;
    Sleep(800);
    cout << "Prepare for battle." << endl;
    Sleep(800);
    if(character.player_class == "rogue"){
        string avoid;
        cout << "Do you want to avoid the battle?(y/n) ";
        cin >> avoid;
        if(avoid == "y" && dungeon_setup.isactive==false){
            cout << "You sneak back to your camp." << endl;
            base();
        }
        else{
            cout << "You take a different path." << endl;
            dungeon();
        }
    }
    bool p_turn;;
    int speed2 = rand() % mob.speed + 1; //check to see if monster attacks first
    if(mob.speed == speed2){
        p_turn = false;
        cout << "The monster attacks first." << endl;
        Sleep(800);
    }
    else{
        p_turn = true;
        cout << "You attack first." << endl;
    }
    while(true){
        if(p_turn){
            char_battle.choice();
            p_turn = false;
            Sleep(800);
            while(true){
                string choose_potion;
                cout << "Do you want to use a health potion or boost from your inventory?(y/n) ";
                cin >> choose_potion;
                if(choose_potion=="y"){
                    items.use_potions();
                    break;
                }
                else if(choose_potion=="n"){
                    break;
                }
                else{
                    cout << "Type 'y' or 'n'." << endl;
                }
            }
            while(true){
                string run;
                cout << "Do you want to try to run?(y/n) ";
                cin >> run;
                if(run=="y"){
                    if(character.race_class=="elf_rogue"){
                        cout << "You managed to escape!" << endl;
                        if(!dungeon_setup.isactive){
                            base();
                        }
                        else{
                            dungeon();
                        }
                    }
                    else{
                        if(mob.speed == speed2){
                            cout << "You managed to escape!" << endl;
                            if(!dungeon_setup.isactive){
                                base();
                            }
                            else{
                                dungeon();
                            }
                        }
                        else{
                            cout << "You try to escape, but trip." << endl;
                            Sleep(800);
                            cout << "The " << mob.name << " uses your blunder to attack again." << endl;
                            Sleep(800);
                            mon_battle.choice();
                            Sleep(800);
                        }
                    }
                }
                else if(run=="n"){
                    Sleep(800);
                    break;
                }
                else{
                    cout << "Please type \'n\' or \'y\'." << endl;
                }
            }
        }
        else{
            mon_battle.choice();
            p_turn = true;
        }
    }
}

void boss_elite_dungeon_battle(){
    cout << "You have entered the elite area!" << endl;
    Sleep(1200);
    cout << "You cannot rest until they are all dead, or you are." << endl;
    Sleep(1200);
    int elite_count = 5;
    while(elite_count>0){
        mob.elite();
        int speed2 = rand() % mob.speed + 1;
        if(mob.speed==speed2){
            cout << "You attack first." << endl;
            char_battle.choice();
            Sleep(1200);
            mob.health -= char_battle.dmg;
            if(mob.health <= 0){
                elite_count--;
                character.exp+=100;
                if(character.exp>=100){
                    cout << "You leveled up!" << endl;
                    character.level_up();
                    mob.level_up();
                    character.exp-=100;
                }
                cout << "Prepare for the next battle." << endl;
                continue;
            }
        }
        else{
            mon_battle.attack();
            Sleep(1200);
            character.health -= mon_battle.dmg;
            if(character.health<=0){
                cout << "You died. Game reset for now." << endl;
                dead();
            }
        }
        while(true){
            char_battle.choice();
            Sleep(1200);
            mob.health -= char_battle.dmg;
            if(mob.health<=0){
                elite_count--;
                cout << "You defeated the monster!" << endl;
                Sleep(1200);
                character.exp+=100;
                if(character.exp>=100){
                    cout << "You go up a level!" << endl;
                    Sleep(1200);
                    character.level_up();
                    mob.level_up();
                    character.exp-=100;
                }
                cout << "Prepare for the next battle." << endl;
                break;
            }
            cout << "The monster attacks, dealing " << mon_battle.dmg << " damage." << endl;
            if(character.health<=0){
                cout << "You have died. Game reset." << endl;
                main();
            }
        }
    }
    cout << "You managed to defeat the elite five!" << endl;
    Sleep(1200);
    cout << "But now you must defeat the boss. Good luck!" << endl;
    while(true){
        mob.boss();
        mon_battle.attack();
        character.health -= mon_battle.dmg;
        if(character.health<=0){
            cout << "The boss killed you. Game reset." << endl;
            dead();
        }
        char_battle.choice();
        mob.health-=char_battle.dmg;
        if(mob.health<=0){
            cout << "You have defeated the boss!!!" << endl;
            Sleep(1200);
            character.exp += mob.exp_drop;
            while(character.exp>=100){
                cout << "You leveled up!" << endl;
                Sleep(1200);
                character.level_up();
                mob.level_up();
                character.exp-=100;
            }
            cout << "You have beaten this dungeon. Treasure to be added." << endl;
        }

    }
    dungeon_setup.exit();
}

void dungeon(){
    if(dungeon_setup.room_count>0){
        dungeon_setup.room_count--;
        cout << "You find yourself in a large room." << endl;
        Sleep(1200);
        int enc_mon = rand() % 3 + 1;
        int enc_mon2 = rand() % 3 + 1;
        if(enc_mon==enc_mon2){
            cout << "A monster spots you!" << endl;
            battle();
        }
        else if(enc_mon-enc_mon2>0){
            cout << "You fall into a trap!" << endl;
            //trap();
            Sleep(1200);
            cout << "To be improved. Loose health for now." << endl;
            character.health -= 5;
            dungeon();
        }
        else if(enc_mon-enc_mon2<0){
            cout << "You find treasure!" << endl;
            Sleep(1200);
            cout << "To be improved, 500 gold added for now." << endl;
            character.money+=500;
            dungeon();
        }
        else{
            cout << "You find nothing interesting here." << endl;
            Sleep(1200);
            cout << "You walk to the next room." << endl;
            dungeon();
        }
    }
    else{
        cout << "You enter the boss's room!" << endl;
        Sleep(1200);
        boss_elite_dungeon_battle();
    }
}

void explore(){
    vector<string> poss_locs;
    cout << "You leave your camp, looking for anything interesting." << endl;
    cout << "You find a long path and walk along it." << endl;
    for (int iter = 1; iter <= 3; iter++){
            cout <<  ". ";
            Sleep(800);
        }
    poss_locs.push_back("abon_house");
    poss_locs.push_back("mon_house");
    poss_locs.push_back("f_house");
    poss_locs.push_back("b_house");
    poss_locs.push_back("None");
    int found_index = rand() % poss_locs.size();
    string found = poss_locs[found_index];
    if(found=="abon_house"){
        locs.abandoned_house();
    }
    else if(found=="mon_house"){
        locs.monster_house();
    }
    else if(found=="f_house"){
        locs.farm();
    }
    else if(found=="b_house"){
        locs.boathouse();
    }
    else{
        cout << "You find nothing interesting." << endl;
    }
    Sleep(800);
    base();
}

void base(){
    cin.clear(); cin.sync();
    string action;
    int dot_count = 1;
    int dot_stop = 3;
    cout << "What do you want to do? ";
    cin >> action;
    if (action == "rest"){
        for (dot_count = 1; dot_count <= dot_stop; dot_count++){
            cout <<  ". ";
             Sleep(800);
        }
        cout <<  "You awake feeling rested." << endl;
        character.health += (character.max_health - character.health);
        base();
    }
    else if(action == "explore"){
        int fequ = rand() % 100 + 1;
        if(fequ < 11){
            battle();
        }
        else{
            explore();
        }
    }
    else if(action == "battle"){
        battle();
    }
    else if(action == "story"){
        story();
    }
    else if(action == "status"){
        cout << "Your health is " << character.health << "." << endl;
        Sleep(800);
        if(character.inventory.empty()){
            cout << "Your inventory is empty." << endl;
        }
        else{
            cout << "Your inventory consists of: ";
            for (vector<string>::iterator i = character.inventory.begin(); i != character.inventory.end(); ++i){
                vector<string>::iterator x = i;
                cout << *i;
                if(++x!=character.inventory.end()){
                    cout << ", ";
                }
                else{
                    cout << "." << endl;
                }
            }
        }
        Sleep(800);
        cout << "You have " << character.exp << " experience points." << endl;
        Sleep(800);
        cout << "You need " << 100 - character.exp << " more point(s) to level." << endl;
        Sleep(800);
        cout << "You are level " << character.level << "." << endl;
        Sleep(800);
        cout << "You have " << character.money << " coins to spend." << endl;
        Sleep(800);
        cout << "Headgear: " << equipment.itemToString(character.head) << endl;
        cout << "Chestplate: " << equipment.itemToString(character.chest) << endl;
        cout << "Arms: " << equipment.itemToString(character.arms) << endl;
        //cout << "Weapon: " << equipment.itemToString(character.weapon) << endl;
        cout << "Leggings: " << equipment.itemToString(character.legs) << endl;
        cout << "Boots: " << equipment.itemToString(character.feet) << endl;
        base();
    }
    else if(action == "save"){
        cout << "Redoing. Game not saved." << endl;
        //save();
        cout << "Your game is saved. Only one saved game is possible at a time." << endl;
        base();
    }
    else if(action == "load"){
        cout << "Redoing. Game not loaded." << endl;
        //load();
        base();
    }
    else if(action == "equip"){
        cout << "Your inventory: ";
        for (vector<string>::iterator i = character.inventory.begin(); i != character.inventory.end(); ++i){
            vector<string>::iterator x = i;
            cout << *i;
            if(++x!=character.inventory.end()){
                cout << ", ";
            }
            else{
                cout << "." << endl;
            }
        }
        cout << "What do you wish to equip? ";
        cin.clear(); cin.sync();
        string item;
        getline(cin, item);
        equipment.equip(item);
        character.defense += equipment.itemList[equipment.itemToString(character.head)];
        character.defense += equipment.itemList[equipment.itemToString(character.chest)];
        character.defense += equipment.itemList[equipment.itemToString(character.arms)];
        character.defense += equipment.itemList[equipment.itemToString(character.legs)];
        character.defense += equipment.itemList[equipment.itemToString(character.feet)];

        for (int iter = 0; iter < character.inventory.size(); iter++){
            if(character.inventory[iter] == item){
                character.inventory.erase(character.inventory.begin()+iter);
            }
        }
        base();
    }
    else if(action=="help"){
        cout << "Type 'rest' to regain your health, 'explore' if you're feeling adventerous, status to view stats about your character, " << endl;
        cout << "'save' to save your character status, 'equip' to equip items in your inventory, ";
        cout << "'story' to adavance the storyline, ";
        cout << "or 'battle' to fight monsters for experience and special items." << endl;
        base();
    }
    else{
        cout << "Choose 'rest', 'status', 'explore', 'story', 'save', 'equip', or 'battle'." << endl;
        base();
    }
}

void alive(){
    cout << "This is your home base." << endl;
    Sleep(800);
    cout << "You can view character stats here, rest to regain health, and many other things.";
    cout << "For a list, type 'help'." << endl;
    base();
}

void story(){
    sits.progress++;
    switch(sits.progress){
        case 1:
            cout << sits.event1;
            break;
        case 2:
            cout << sits.event2;
            break;
        case 3:
            cout << sits.event3;
            break;
        case 4:
            cout << sits.event4;
            break;
        case 5:
            cout << sits.event5;
            break;
        case 6:
            cout << sits.event6;
            break;
        case 7:
            cout << sits.event7;
            break;
        case 8:
            cout << sits.event8;
            break;
        case 9:
            cout << sits.event9;
            break;
        case 10:
            cout << sits.event10;
            break;
        default:
            cout << "BOSS TIME!!! End game." << endl;
            main();
    }
    base();
}

void dead(){
    cout << "Working on dead function." << endl;
    cout << "For now, game is reset." << endl;
    main();
}

void mon_dead(){
    cout << "You defeated the monster! You earn " << mob.exp_drop << " experience." << endl;
    if(!dungeon_setup.isactive){
        mob.count.erase(mob.count.begin()+mob.freq);
        if(mob.count.size()==0){
            cout << "You win. To be expanded. For now, game reset." << endl;
            main();
        }
    }
    character.exp += mob.exp_drop;
    Sleep(800);
    cout << "You also earned " << mob.money_drop << " coins." << endl;
    character.money += mob.money_drop;
    Sleep(800);
    if(character.exp>=100){
        cout << "Congratulations, you went up a level! " << endl;
        Sleep(800);
        cout << "Your health increases by 5 points and your damage increases by 3 points." << endl;
        Sleep(800);
        cout << "But as you increase in strength, so do the monsters." << endl;
        Sleep(800);
        character.level_up();
        mob.level_up();
        character.exp -= 100;
    }
    mob.item_drop();
    cout << "The monster dropped " << mob.rand_item << "." << endl;
    if(mob.rand_item=="nothing"){
        if(!dungeon_setup.isactive){
            base();
        }
        else{
            dungeon();
        }
    }
    string pick_up;
    while(true){
        cout << "Do you want to put it in your inventory?(y/n) ";
        cin >> pick_up;
        if(pick_up=="y"){
            cout << "You picked up the item. You have limited inventory." << endl; //Specify inventory spaces left
            character.inventory.push_back(mob.rand_item);
            if(!dungeon_setup.isactive){
                base();
            }
            else{
                dungeon();
            }
        }
        else if(pick_up=="n"){
            if(!dungeon_setup.isactive){
                base();
            }
            else{
                dungeon();
            }
        }
        else{
            cout << "Pick \'y\' or \'n\'." << endl;
        }
    }
    Sleep(800);
    base();
}
