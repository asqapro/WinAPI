#include <iostream>
#include <fstream>
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
#include "RPG.pb.h"

using namespace std;

void save();
void load();
void char_create();
void alive();
void dead();
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
    int race_class_en;
    int health;
    int max_health;
    int exp;
    int level;
    int dmg;
    map<string, string> equip_places;
    string player_class;
    vector<string> inventory;

    void level_up(){
        max_health += 5;
        health = max_health;
        level++;
    }

    void warrior_dmg(){
        dmg = rand() % (8+(level*4)) + (4+(level*4));
    }
    void rogue_dmg(){
        int base = rand() % (5+(level*3)) + (1+(level*3));
        int second_base = rand() % (5+(level*3)) + (1+(level*3));
        int crit = (15+level*3);
        if (base == second_base){
            dmg = crit;
        }
        else{
            dmg = base;
        }
    }
    void mage_dmg(){
        dmg = rand() % (7+(level*5)) + (1+(level*5));
    }

    void human(){
        //string special_race_abil "run if low health";
        //string special_proff_abil = "avoid battles";
        health = 35;
        max_health = health;
        player_class = "rogue";
        race_class = "human_rogue";
    }
    void human_warrior(){
        //string special_race_abil = "run if low health";
        //string special_proff_abil = "heavy items";
        health = 55;
        max_health = health;
        player_class = "warrior";
        race_class = "human_warrior";
    }
    void human_mage(){
        //string special_race_abil = "run if low health";
        //string special_proff_abil = "magic";
        health = 40;
        max_health = health;
        player_class = "mage";
        race_class = "human_mage";
    }

    void orc_rogue(){
        //string special_race_abil = "extra dmg";
        //string special_proff_abil = "avoid battles";
        health = 35;
        max_health = health;
        player_class = "rogue";
        race_class = "orc_rogue";
    }

    void orc_warrior(){
        //string special_race_abil = "extra dmg";
        //string special_proff_abil = "heavy items";
        health = 55;
        max_health = health;
        player_class = "warrior";
        race_class = "orc_warrior";
    }
    void orc_mage(){
        //string special_race_abil = "extra dmg";
        //string special_proff_abil = "magic";
        health = 40;
        max_health = health;
        player_class = "mage";
        race_class = "orc_mage";
    }

    void elf_rogue(){
        //string extra_combo_abil = "always escape battles";
        //string special_race_abil = "first attack";
        string special_proff_abil = "avoid battles";
        health = 35;
        max_health = health;
        player_class = "rogue";
        race_class = "elf_rogue";
    }
    void elf_warrior(){
        //string special_proff_abil = "heavy items";
        health = 55;
        max_health = health;
        player_class = "warrior";
        race_class = "elf_warrior";
    }
    void elf_mage(){
        //string special_proff_abil = "magic";
        //string special_race_abil = "extra dmg";
        health = 40;
        max_health = health;
        player_class = "mage";
        race_class = "elf_mage";

    }
}character;

struct abilities{
    int dmg;
    string abil_name;
    //string effects
    void basic_attack(){
        dmg = rand()
    }

}abils;

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

struct monster{
    int money_drop;
    int rep_count;
    int bi_count;
    int hum_count;
    int hy_count;
    vector<string> mon_count;
    int mon_health;
    int mon_max_health;
    int speed;
    int exp_drop;
    int mon_dmg;
    int mon_level;
    string rand_item;
    string mon_name;
    vector<string> item_drop_list;

    void rep_dmg(){
        mon_dmg = rand() % (15+(mon_level*3)) + (10+(mon_level*3));
    }
    void bi_dmg(){
        mon_dmg = rand() % (8+(mon_level*1)) + (5+(mon_level*1));
    }
    void hum_dmg(){
        mon_dmg = rand() % (13+(mon_level*2)) + (8+(mon_level*2));
    }
    void hy_dmg(){
        mon_dmg = rand() % (20+(mon_level*4)) + (15+(mon_level*4));
    }
    void el_dmg(){
        mon_dmg = rand() % (30+(mon_level*5)) + (25+(mon_level*5));
    }
    void boss_dmg(){
        mon_dmg = rand() % 50 + 30;
    }
    void mon_level_up(){
        mon_level += 1;
    }

    void item_drop(){
        int drop_rate1 = rand() % 5 + 1;
        int drop_rate2 = rand() % 5 + 1;
        int drop_rate_hy1 = rand() % 10 + 1;
        int drop_rate_hy2 = rand() % 10 + 1;
        int get_rand_item = rand() % 3 + 1;
        if(mon_name=="hybrid"){
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
        mon_health = 45 + (mon_level * 3);
        speed = 2;
        exp_drop = 35;
        money_drop = 500 + (mon_level*100);
        mon_name = "reptile";
        item_drop_list.push_back("health potion");
        item_drop_list.push_back("battle axe");
        item_drop_list.push_back("heavy chestplate");
        //frequency = 30
    }
    void bird(){
        mon_health = 30 + (mon_level * 3);
        speed = 15;
        exp_drop = 15;
        mon_name = "bird";
        money_drop = 300 + (mon_level*100);
        item_drop_list.push_back("health potion");
        item_drop_list.push_back("dagger");
        item_drop_list.push_back("light chestplate");
        //frequency = 45
    }
    void humanoid(){
        mon_health = 40 + (mon_level * 3);
        speed = 10;
        exp_drop = 20;
        mon_name = "humanoid";
        money_drop = 500 + (mon_level*100);
        item_drop_list.push_back("health potion");
        item_drop_list.push_back("wooden staff");
        item_drop_list.push_back("arcane chestplate"); //to be made more arcaney
        //frequency = 20
    }
    void hybrid(){
        mon_health = 60 + (mon_level * 3);
        speed = 7;
        exp_drop = 55;
        money_drop = 700 + (mon_level*100);
        mon_name = "hybrid";
        item_drop_list.push_back("health potion");
        item_drop_list.push_back("potent health potion");
        item_drop_list.push_back("mystery health potion");
        //frequency = 5
    }
    void elite(){
        mon_health = 100 + (mon_level * 5);
        speed = 15;
        exp_drop = 100;
        money_drop = 2000;
        mon_name = "elite";
        item_drop_list.push_back("potent health potion");
    }
    void boss(){
        mon_health = 300;
        speed = 30;
        exp_drop = 300;
        money_drop = 10000;
        mon_name = "Boss name here";
        item_drop_list.push_back("special undefined item");
    }
}mob;

struct equips{
    vector<string> h_head;
    vector<string> h_chest;
    vector<string> h_arm;
    vector<string> h_hand;
    vector<string> h_leg;
    vector<string> h_feet;
    vector<string> l_head;
    vector<string> l_chest;
    vector<string> l_arm;
    vector<string> l_hand;
    vector<string> l_leg;
    vector<string> l_feet;
    vector<string> a_head;
    vector<string> a_chest;
    vector<string> a_arm;
    vector<string> a_hand;
    vector<string> a_leg;
    vector<string> a_feet;

    void heavy(){
        //h_head.push_back(/*head gear */);
        h_chest.push_back("heavy chestplate");
        //h_arm.push_back(/*arm stuff */);
        h_hand.push_back("battle axe");
        h_leg.push_back("heavy leggings");
        //h_feet.push_back(/*feet stuff */);
    }

    void light(){
        //l_head.push_back(/*head gear */);
        l_chest.push_back("light chestplate");
        //l_arm.push_back(/*arm stuff */);
        l_hand.push_back("dagger");
        l_leg.push_back("light leggings");
        //l_feet.push_back(/*feet stuff */);
    }

    void arcane(){
        //a_head.push_back(/*head gear */);
        a_chest.push_back("arcane chestplate");
        //a_arm.push_back(/*arm stuff */);
        a_hand.push_back("staff");
        a_leg.push_back("arcane leggings");
        //a_feet.push_back(/*feet stuff */);
    }
    void equip_heavy_items(){
        vector<string> inven_copy(character.inventory);
        if(!character.inventory.empty()){
            for (vector<string>::iterator i=inven_copy.begin(); i != inven_copy.end(); ++i){
                if(find(h_head.begin(), h_head.end(), *i) != h_head.end()){
                    if(character.equip_places.find("head")!=character.equip_places.end()){
                        cout << "You equipped: " << *i << endl;
                        character.equip_places["head"]=*i;
                        vector<string>::iterator position = find(character.inventory.begin(), character.inventory.end(), *i);
                        if (position != character.inventory.end()){
                            character.inventory.erase(position);
                        }
                    }
                    else{
                        cout << "Headgear already equipped." << endl;
                    }
                }
                else if(find(h_chest.begin(), h_chest.end(), *i) != h_chest.end()){
                    if(character.equip_places.find("chest")!=character.equip_places.end()){
                        cout << "You equipped: " << *i << endl;
                        character.equip_places["chest"]=*i;
                        vector<string>::iterator position = find(character.inventory.begin(), character.inventory.end(), *i);
                        if (position != character.inventory.end()){
                            character.inventory.erase(position);
                        }
                    }
                    else{
                        cout << "Chestplate already equipped." << endl;
                    }
                }
                else if(find(h_arm.begin(), h_arm.end(), *i) != h_arm.end()){
                    if(character.equip_places.find("arms")!=character.equip_places.end()){
                        cout << "You equipped: " << *i << endl;
                        character.equip_places["arms"]=*i;
                        vector<string>::iterator position = find(character.inventory.begin(), character.inventory.end(), *i);
                        if (position != character.inventory.end()){
                            character.inventory.erase(position);
                        }
                    }
                    else{
                        cout << "Arm guards already equipped." << endl;
                    }
                }
                else if(find(h_hand.begin(), h_hand.end(), *i) != h_hand.end()){
                    if(character.equip_places.find("hands")!=character.equip_places.end()){
                        cout << "You equipped: " << *i << endl;
                        character.equip_places["hands"]=*i;
                        vector<string>::iterator position = find(character.inventory.begin(), character.inventory.end(), *i);
                        if (position != character.inventory.end()){
                            character.inventory.erase(position);
                        }
                    }
                    else{
                        cout << "Weapon already equipped." << endl;
                    }
                }
                else if(find(h_leg.begin(), h_leg.end(), *i) != h_leg.end()){
                    if(character.equip_places.find("legs")!=character.equip_places.end()){
                        cout << "You equipped: " << *i << endl;
                        character.equip_places["legs"]=*i;
                        vector<string>::iterator position = find(character.inventory.begin(), character.inventory.end(), *i);
                        if (position != character.inventory.end()){
                            character.inventory.erase(position);
                        }
                    }
                    else{
                        cout << "Leggings already equipped." << endl;
                    }
                }
                else if(find(h_feet.begin(), h_feet.end(), *i) != h_feet.end()){
                    if(character.equip_places.find("feet")!=character.equip_places.end()){
                        cout << "You equipped: " << *i << endl;
                        character.equip_places["feet"]=*i;
                        vector<string>::iterator position = find(character.inventory.begin(), character.inventory.end(), *i);
                        if (position != character.inventory.end()){
                            character.inventory.erase(position);
                        }
                    }
                    else{
                        cout << "Boots already equipped." << endl;
                    }
                }
                else{
                    cout << "Nothing to equip." << endl;
                    break;
                }
            }
        }
        else{
            cout << "No items to equip." << endl;
        }
    }
    void equip_light_items(){
        vector<string> inven_copy(character.inventory);
        if(!character.inventory.empty()){
            for (vector<string>::iterator i=inven_copy.begin(); i != inven_copy.end(); ++i){
                if(find(l_head.begin(), l_head.end(), *i) != l_head.end()){
                    if(character.equip_places.find("head")!=character.equip_places.end()){
                        cout << "You equipped: " << *i << endl;
                        character.equip_places["head"]=*i;
                        vector<string>::iterator position = find(character.inventory.begin(), character.inventory.end(), *i);
                        if (position != character.inventory.end()){
                            character.inventory.erase(position);
                        }
                    }
                    else{
                        cout << "Headgear already equipped." << endl;
                    }
                }
                else if(find(l_chest.begin(), l_chest.end(), *i) != l_chest.end()){
                    if(character.equip_places.find("chest")!=character.equip_places.end()){
                        cout << "You equipped: " << *i << endl;
                        character.equip_places["chest"]=*i;
                        vector<string>::iterator position = find(character.inventory.begin(), character.inventory.end(), *i);
                        if (position != character.inventory.end()){
                            character.inventory.erase(position);
                        }
                    }
                    else{
                        cout << "Chestplate already equipped." << endl;
                    }
                }
                else if(find(l_arm.begin(), l_arm.end(), *i) != l_arm.end()){
                    if(character.equip_places.find("arms")!=character.equip_places.end()){
                        cout << "You equipped: " << *i << endl;
                        character.equip_places["arms"]=*i;
                        vector<string>::iterator position = find(character.inventory.begin(), character.inventory.end(), *i);
                        if (position != character.inventory.end()){
                            character.inventory.erase(position);
                        }
                    }
                    else{
                        cout << "Arm guards already equipped." << endl;
                    }
                }
                else if(find(l_hand.begin(), l_hand.end(), *i) != l_hand.end()){
                    if(character.equip_places.find("hands")!=character.equip_places.end()){
                        cout << "You equipped: " << *i << endl;
                        cout << "QWOP{ERDOOELRS" << endl;
                        character.equip_places["hands"]=*i;
                        vector<string>::iterator position = find(character.inventory.begin(), character.inventory.end(), *i);
                        if (position != character.inventory.end()){
                            character.inventory.erase(position);
                        }
                    }
                    else{
                        cout << "Weapon already equipped." << endl;
                    }
                }
                else if(find(l_leg.begin(), l_leg.end(), *i) != l_leg.end()){
                    if(character.equip_places.find("legs")!=character.equip_places.end()){
                        cout << "You equipped: " << *i << endl;
                        character.equip_places["legs"]=*i;
                        vector<string>::iterator position = find(character.inventory.begin(), character.inventory.end(), *i);
                        if (position != character.inventory.end()){
                            character.inventory.erase(position);
                        }
                    }
                    else{
                        cout << "Leggings already equipped." << endl;
                    }
                }
                else if(find(l_feet.begin(), l_feet.end(), *i) != l_feet.end()){
                    if(character.equip_places.find("feet")!=character.equip_places.end()){
                        cout << "You equipped: " << *i << endl;
                        character.equip_places["feet"]=*i;
                        vector<string>::iterator position = find(character.inventory.begin(), character.inventory.end(), *i);
                        if (position != character.inventory.end()){
                            character.inventory.erase(position);
                        }
                    }
                    else{
                        cout << "Boots already equipped." << endl;
                    }
                }
                else{
                    cout << "Nothing to equip." << endl;
                    break;
                }
            }
        }
        else{
            cout << "No items to equip." << endl;
        }
    }
    void equip_arcane_items(){
        vector<string> inven_copy(character.inventory);
        if(!character.inventory.empty()){
            for (vector<string>::iterator i=inven_copy.begin(); i != inven_copy.end(); ++i){
                if(find(a_head.begin(), a_head.end(), *i) != a_head.end()){
                    if(character.equip_places.find("head")!=character.equip_places.end()){
                        cout << "You equipped: " << *i << endl;
                        character.equip_places["head"]=*i;
                        vector<string>::iterator position = find(character.inventory.begin(), character.inventory.end(), *i);
                        if (position != character.inventory.end()){
                            character.inventory.erase(position);
                        }
                    }
                    else{
                        cout << "Headgear already equipped." << endl;
                    }
                }
                else if(find(a_chest.begin(), a_chest.end(), *i) != a_chest.end()){
                    if(character.equip_places.find("chest")!=character.equip_places.end()){
                        cout << "You equipped: " << *i << endl;
                        character.equip_places["chest"]=*i;
                        vector<string>::iterator position = find(character.inventory.begin(), character.inventory.end(), *i);
                        if (position != character.inventory.end()){
                            character.inventory.erase(position);
                        }
                    }
                    else{
                        cout << "Chestplate already equipped." << endl;
                    }
                }
                else if(find(a_arm.begin(), a_arm.end(), *i) != a_arm.end()){
                    if(character.equip_places.find("arms")!=character.equip_places.end()){
                        cout << "You equipped: " << *i << endl;
                        character.equip_places["arms"]=*i;
                        vector<string>::iterator position = find(character.inventory.begin(), character.inventory.end(), *i);
                        if (position != character.inventory.end()){
                            character.inventory.erase(position);
                        }
                    }
                    else{
                        cout << "Arm guards already equipped." << endl;
                    }
                }
                else if(find(a_hand.begin(), a_hand.end(), *i) != a_hand.end()){
                    if(character.equip_places.find("hands")!=character.equip_places.end()){
                        cout << "You equipped: " << *i << endl;
                        character.equip_places["hands"]=*i;
                        vector<string>::iterator position = find(character.inventory.begin(), character.inventory.end(), *i);
                        if (position != character.inventory.end()){
                            character.inventory.erase(position);
                        }
                    }
                    else{
                        cout << "Weapon already equipped." << endl;
                    }
                }
                else if(find(a_leg.begin(), a_leg.end(), *i) != a_leg.end()){
                    if(character.equip_places.find("legs")!=character.equip_places.end()){
                        cout << "You equipped: " << *i << endl;
                        character.equip_places["legs"]=*i;
                        vector<string>::iterator position = find(character.inventory.begin(), character.inventory.end(), *i);
                        if (position != character.inventory.end()){
                            character.inventory.erase(position);
                        }
                    }
                    else{
                        cout << "Leggings already equipped." << endl;
                    }
                }
                else if(find(a_feet.begin(), a_feet.end(), *i) != a_feet.end()){
                    if(character.equip_places.find("feet")!=character.equip_places.end()){
                        cout << "You equipped: " << *i << endl;
                        character.equip_places["feet"]=*i;
                        vector<string>::iterator position = find(character.inventory.begin(), character.inventory.end(), *i);
                        if (position != character.inventory.end()){
                            character.inventory.erase(position);
                        }
                    }
                    else{
                        cout << "Boots already equipped." << endl;
                    }
                }
                else{
                    cout << "Nothing to equip." << endl;
                    break;
                }
            }
        }
        else{
            cout << "No items to equip." << endl;
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

int main(){
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    while(true){
        string reload;
        cout << "Do you want to load a save?(y/n) ";
        cin >> reload;
        if(reload=="y"){
            load();
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
        mob.mon_count.push_back("bird");
    }
    for(int i=mob.rep_count;i>0;i--){
        mob.mon_count.push_back("reptile");
        mob.mon_count.push_back("humanoid");
    }
    for(int i=mob.hy_count;i>0;i--){
        mob.mon_count.push_back("hybrid");
    }
    equipment.heavy();
    equipment.light(); //Create the heavy, light, and arcane armor lists
    equipment.arcane();
    locs.create_first_time(); //Set a true bool value for dealing with locations later
    items.set_items(); //Set up the items lists
    npc.set_prices(); //Set up shop
    char_create(); //Create the character
    alive(); //While this function runs, you are "alive", stays within itself
    cout << "Something crashed."; //More a note for more than anything, tells me if I forgot to call inside the alive function
    return 0; //Program ends (should not be reached)
}

void save(){
    //Player
    RPG::player out_char_dat;
    out_char_dat.set_money(character.money);
    out_char_dat.set_race_class(character.race_class);
    out_char_dat.set_health(character.health);
    out_char_dat.set_max_health(character.max_health);
    out_char_dat.set_exp(character.exp);
    out_char_dat.set_level(character.level);
    out_char_dat.set_dmg(character.dmg);
    out_char_dat.set_player_class(character.player_class);
    vector<string>::iterator i;
    for(i=character.inventory.begin();i!=character.inventory.end();++i){
        out_char_dat.add_inventory(*i);// = *i;
    }
    map<string, string>::iterator it;
    for(it=character.equip_places.begin();it!=character.equip_places.end();++it){
        out_char_dat.add_equip_places_key(it->first);// = it->first;
        out_char_dat.add_equip_places_value(it->second);// = it->second;
    }
    //NPCs
    RPG::npc out_npc_dat;
    map<string, int>::iterator itt;
    for(itt=npc.smith_items_to_buy.begin();itt!=npc.smith_items_to_buy.end();++itt){
        out_npc_dat.add_smith_items_to_buy_key(itt->first);// = itt->first;
        out_npc_dat.add_smith_items_to_buy_value(itt->second);// = itt->second;
    }
    for(itt=npc.smith_items_to_sell.begin();itt!=npc.smith_items_to_sell.end();++itt){
        out_npc_dat.add_smith_items_to_sell_key(itt->first);// = itt->first;
        out_npc_dat.add_smith_items_to_sell_value(itt->second);// = itt->second;
    }
    //Useable items
    RPG::use_item out_item_dat;
    out_item_dat.set_picked_potion(items.picked_potion);
    out_item_dat.set_wear_off(items.wear_off);
    for(i=items.health_restores.begin();i!=items.health_restores.end();++i){
        out_item_dat.add_health_restores(*i);// = *i;
    }
    for(i=items.poisons.begin();i!=items.poisons.end();++i){
        out_item_dat.add_poisons(*i);// = *i;
    }
    for(i=items.temp_boosts.begin();i!=items.temp_boosts.end();++i){
        out_item_dat.add_temp_boosts(*i);// = *i;
    }
    for(i=items.perm_boosts.begin();i!=items.perm_boosts.end();++i){
        out_item_dat.add_perm_boosts(*i);// = *i;
    }
    for(i=items.misc.begin();i!=items.misc.end();++i){
        out_item_dat.add_misc(*i);// = *i;
    }
    //Monster
    RPG::monster out_mon_dat;
    for(i=mob.mon_count.begin();i!=mob.mon_count.end();++i){
        out_mon_dat.add_mon_count(*i);// = *i;
    }
    //Equipment
    RPG::equips out_equip_dat;
    //Heavy equipment
    for(i=equipment.h_head.begin();i!=equipment.h_head.end();++i){
        out_equip_dat.add_h_head(*i);// = *i;
    }
    for(i=equipment.h_chest.begin();i!=equipment.h_chest.end();++i){
        out_equip_dat.add_h_chest(*i);// = *i;
    }
    for(i=equipment.h_arm.begin();i!=equipment.h_arm.end();++i){
        out_equip_dat.add_h_arm(*i);// = *i;
    }
    for(i=equipment.h_hand.begin();i!=equipment.h_hand.end();++i){
        out_equip_dat.add_h_hand(*i);// = *i;
    }
    for(i=equipment.h_leg.begin();i!=equipment.h_leg.end();++i){
        out_equip_dat.add_h_leg(*i);// = *i;
    }
    for(i=equipment.h_feet.begin();i!=equipment.h_feet.end();++i){
        out_equip_dat.add_h_feet(*i);// = *i;
    }
    //Light equipment
    for(i=equipment.l_head.begin();i!=equipment.l_head.end();++i){
        out_equip_dat.add_l_head(*i);// = *i;
    }
    for(i=equipment.l_chest.begin();i!=equipment.l_chest.end();++i){
        out_equip_dat.add_l_chest(*i);// = *i;
    }
    for(i=equipment.l_arm.begin();i!=equipment.l_arm.end();++i){
        out_equip_dat.add_l_arm(*i);// = *i;
    }
    for(i=equipment.l_hand.begin();i!=equipment.l_hand.end();++i){
        out_equip_dat.add_l_hand(*i);// = *i;
    }
    for(i=equipment.l_leg.begin();i!=equipment.l_leg.end();++i){
        out_equip_dat.add_l_leg(*i);// = *i;
    }
    for(i=equipment.l_feet.begin();i!=equipment.l_feet.end();++i){
        out_equip_dat.add_l_feet(*i);// = *i;
    }
    //Arcane equipment
    for(i=equipment.a_head.begin();i!=equipment.a_head.end();++i){
        out_equip_dat.add_a_head(*i);// = *i;
    }
    for(i=equipment.a_chest.begin();i!=equipment.a_chest.end();++i){
        out_equip_dat.add_a_chest(*i);// = *i;
    }
    for(i=equipment.a_arm.begin();i!=equipment.a_arm.end();++i){
        out_equip_dat.add_a_arm(*i);// = *i;
    }
    for(i=equipment.a_hand.begin();i!=equipment.a_hand.end();++i){
        out_equip_dat.add_a_hand(*i);// = *i;
    }
    for(i=equipment.a_leg.begin();i!=equipment.a_leg.end();++i){
        out_equip_dat.add_a_leg(*i);// = *i;
    }
    for(i=equipment.a_feet.begin();i!=equipment.a_feet.end();++i){
        out_equip_dat.add_a_feet(*i);// = *i;
    }

    //RPG::dungeon_setup out_dun_dat; Optional, leaving out for now
    //Only needed if add global save function (save in dungeons)
    //Locations
    RPG::locations out_loc_dat;
    out_loc_dat.set_first_time_abon(locs.first_time_abon);
    out_loc_dat.set_first_time_mon(locs.first_time_mon);
    out_loc_dat.set_first_time_farm(locs.first_time_farm);
    out_loc_dat.set_first_time_boat(locs.first_time_boat);
    //Story
    RPG::story out_story_dat;
    out_story_dat.set_progress(sits.progress);
    out_story_dat.set_back_story(sits.back_story);
    out_story_dat.set_event1(sits.event1);
    out_story_dat.set_event2(sits.event2);
    out_story_dat.set_event3(sits.event3);
    out_story_dat.set_event4(sits.event4);
    out_story_dat.set_event5(sits.event5);
    out_story_dat.set_event6(sits.event6);
    out_story_dat.set_event7(sits.event7);
    out_story_dat.set_event8(sits.event8);
    out_story_dat.set_event9(sits.event9);
    out_story_dat.set_event10(sits.event10);


    fstream output("RPG.proto", ios::out | ios::trunc | ios::binary);
    out_char_dat.SerializeToOstream(&output);
    out_item_dat.SerializeToOstream(&output);
    out_loc_dat.SerializeToOstream(&output);
    out_mon_dat.SerializeToOstream(&output);
    out_npc_dat.SerializeToOstream(&output);
    out_story_dat.SerializeToOstream(&output);
    output.close();
}

void load(){
    RPG::player in_char_dat;
    RPG::npc in_npc_dat;
    RPG::use_item in_item_dat;
    RPG::monster in_mon_dat;
    RPG::equips in_equip_dat;
    RPG::locations in_loc_dat;
    RPG::story in_story_dat;
    fstream input("RPG.proto", ios::in | ios::binary);
    if(!in_char_dat.ParseFromIstream(&input)&&
       !in_npc_dat.ParseFromIstream(&input)&&
       !in_item_dat.ParseFromIstream(&input)&&
       !in_mon_dat.ParseFromIstream(&input)&&
       !in_equip_dat.ParseFromIstream(&input)&&
       !in_loc_dat.ParseFromIstream(&input)&&
       !in_story_dat.ParseFromIstream(&input)){
           cout << "No saved game." << endl;
           input.close();
    }
    else{
        //Character
        character.money = in_char_dat.money();
        character.race_class = in_char_dat.race_class();
        character.health = in_char_dat.health();
        character.max_health = in_char_dat.max_health();
        character.exp = in_char_dat.exp();
        character.level = in_char_dat.level();
        character.dmg = in_char_dat.dmg();
        character.player_class = in_char_dat.player_class();
        for(int i=1;i<in_char_dat.inventory_size();++i){
            character.inventory.push_back(in_char_dat.inventory(i));
        }
        for(int i=0;i<in_char_dat.equip_places_key_size();++i){
            character.equip_places.insert( pair<string,string>(in_char_dat.equip_places_key(i),in_char_dat.equip_places_value(i)) );
        }
        //NPC
        for(int i=0;i<in_npc_dat.smith_items_to_buy_key_size();++i){
            npc.smith_items_to_buy.insert( pair<string,int>(in_npc_dat.smith_items_to_buy_key(i),in_npc_dat.smith_items_to_buy_value(i)) );
        }
        for(int i=0;i<in_npc_dat.smith_items_to_buy_key_size();++i){
            npc.smith_items_to_sell.insert( pair<string,int>(in_npc_dat.smith_items_to_sell_key(i),in_npc_dat.smith_items_to_sell_value(i)) );
        }
        //Use_items
        for(int i=0;i<in_item_dat.health_restores_size();++i){
            items.health_restores.push_back(in_item_dat.health_restores(i));
        }
        for(int i=0;i<in_item_dat.poisons_size();++i){
            items.poisons.push_back(in_item_dat.poisons(i));
        }
        for(int i=0;i<in_item_dat.temp_boosts_size();++i){
            items.temp_boosts.push_back(in_item_dat.temp_boosts(i));
        }
        for(int i=0;i<in_item_dat.perm_boosts_size();++i){
            items.perm_boosts.push_back(in_item_dat.perm_boosts(i));
        }
        for(int i=0;i<in_item_dat.misc_size();++i){
            items.misc.push_back(in_item_dat.misc(i));
        }
        //Monster
        for(int i=0;i<in_mon_dat.mon_count_size();++i){
            mob.mon_count.push_back(in_mon_dat.mon_count(i));
        }
        //Equips
        //Heavy
        for(int i=0;i<in_equip_dat.h_head_size();++i){
            equipment.h_head.push_back(in_equip_dat.h_head(i));
        }
        for(int i=0;i<in_equip_dat.h_chest_size();++i){
            equipment.h_chest.push_back(in_equip_dat.h_chest(i));
        }
        for(int i=0;i<in_equip_dat.h_arm_size();++i){
            equipment.h_arm.push_back(in_equip_dat.h_arm(i));
        }
        for(int i=0;i<in_equip_dat.h_hand_size();++i){
            equipment.h_hand.push_back(in_equip_dat.h_hand(i));
        }
        for(int i=0;i<in_equip_dat.h_leg_size();++i){
            equipment.h_leg.push_back(in_equip_dat.h_leg(i));
        }
        for(int i=0;i<in_equip_dat.h_feet_size();++i){
            equipment.h_feet.push_back(in_equip_dat.h_feet(i));
        }
        //Light
        for(int i=0;i<in_equip_dat.l_head_size();++i){
            equipment.l_head.push_back(in_equip_dat.l_head(i));
        }
        for(int i=0;i<in_equip_dat.l_chest_size();++i){
            equipment.l_chest.push_back(in_equip_dat.l_chest(i));
        }
        for(int i=0;i<in_equip_dat.l_arm_size();++i){
            equipment.l_arm.push_back(in_equip_dat.l_arm(i));
        }
        for(int i=0;i<in_equip_dat.l_hand_size();++i){
            equipment.l_hand.push_back(in_equip_dat.l_hand(i));
        }
        for(int i=0;i<in_equip_dat.l_leg_size();++i){
            equipment.l_leg.push_back(in_equip_dat.l_leg(i));
        }
        for(int i=0;i<in_equip_dat.l_feet_size();++i){
            equipment.l_feet.push_back(in_equip_dat.l_feet(i));
        }
        //Arcane
        for(int i=0;i<in_equip_dat.a_head_size();++i){
            equipment.a_head.push_back(in_equip_dat.a_head(i));
        }
        for(int i=0;i<in_equip_dat.a_chest_size();++i){
            equipment.a_chest.push_back(in_equip_dat.a_chest(i));
        }
        for(int i=0;i<in_equip_dat.a_arm_size();++i){
            equipment.a_arm.push_back(in_equip_dat.a_arm(i));
        }
        for(int i=0;i<in_equip_dat.a_hand_size();++i){
            equipment.a_hand.push_back(in_equip_dat.a_hand(i));
        }
        for(int i=0;i<in_equip_dat.a_leg_size();++i){
            equipment.a_leg.push_back(in_equip_dat.a_leg(i));
        }
        for(int i=0;i<in_equip_dat.a_feet_size();++i){
            equipment.a_feet.push_back(in_equip_dat.a_feet(i));
        }
        //Locations
        locs.first_time_abon = in_loc_dat.first_time_abon();
        locs.first_time_mon = in_loc_dat.first_time_mon();
        locs.first_time_farm = in_loc_dat.first_time_farm();
        locs.first_time_boat = in_loc_dat.first_time_boat();
        //Story
        sits.progress = in_story_dat.progress();
        sits.back_story = in_story_dat.back_story();
        sits.event1 = in_story_dat.event1();
        sits.event2 = in_story_dat.event2();
        sits.event3 = in_story_dat.event3();
        sits.event4 = in_story_dat.event4();
        sits.event5 = in_story_dat.event5();
        sits.event6 = in_story_dat.event6();
        sits.event7 = in_story_dat.event7();
        sits.event8 = in_story_dat.event8();
        sits.event9 = in_story_dat.event9();
        sits.event10 = in_story_dat.event10();

        cout << "Game loaded successfully." << endl;
        input.close();
        base();
    }
}

void char_create(){
    character.level = 1;
    string pick_race = "";
	string pick_class = "";
	character.equip_places["head"]="";
	character.equip_places["arms"]="";
	character.equip_places["hands"]="";
	character.equip_places["chest"]="";
	character.equip_places["legs"]="";
	character.equip_places["feet"]="";
	while(true){
        cout << "Pick your race(human, orc, or elf): ";
        cin >> pick_race;
        if(pick_race!="human"){
                if(pick_race!="orc"){
                    if(pick_race!="elf"){
                        cout << "Choose 'human', 'orc', or 'elf'." << endl;
                    }
                    else{
                        break;
                    }
                }
                else{
                    break;
                }
        }
        else{
            break;
        }
    }
    while(true){
        cout << "Pick your class(warrior, mage, or rogue): ";
        cin >> pick_class;
        if(pick_class!="warrior"){
                if(pick_class!="mage"){
                    if(pick_class!="rogue"){
                        cout << "Choose 'warrior', 'mage', or 'rogue'." << endl;
                    }
                    else{
                        break;
                    }
                }
                else{
                    break;
                }
        }
        else{
            break;
        }
    }
	string picked = pick_race+"_"+pick_class;
    if (picked == "human_rogue"){
        character.human_rogue();
    }
    else if (picked == "human_warrior"){
        character.human_warrior();
    }
    else if (picked == "human_mage"){
        character.human_mage();
    }

    else if (picked == "orc_rogue"){
        character.orc_rogue();
    }
    else if (picked == "orc_warrior"){
        character.orc_warrior();
    }
    else if (picked == "orc_mage"){
        character.orc_mage();
    }

    else if (picked == "elf_rogue"){
        character.elf_rogue();
    }
    else if (picked == "elf_warrior"){
        character.elf_warrior();
    }
    else if (picked == "elf_mage"){
        character.elf_mage();
    }
};

void battle(){
    int freq = rand() % 200 + 1;
    string f_mon = mob.mon_count[freq];
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
    cout << "You encountered a " << mob.mon_name << "!" << endl;
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
    int speed2 = rand() % mob.speed + 1;
    if(mob.speed == speed2){
        if(mob.mon_name=="reptile"){
            mob.rep_dmg();
        }
        else if(mob.mon_name=="bird"){
            mob.bi_dmg();
        }
        else if(mob.mon_name=="humanoid"){
            mob.hum_dmg();
        }
        else{
            mob.hy_dmg();
        }
        cout << "The monster attacks first, dealing " << mob.mon_dmg << " damage." << endl;
        character.health -= mob.mon_dmg;
        cout << "Your health drops to " << character.health << "." << endl;
        Sleep(800);
    }
    else{
        if(character.player_class=="warrior"){
            character.warrior_dmg();
        }
        else if(character.player_class=="rogue"){
            character.rogue_dmg();
        }
        else{
            character.mage_dmg();
        }
        cout << "You attack first, dealing " << character.dmg << " damage." << endl;
        mob.mon_health -= character.dmg;
        cout << "The monster's health drops to " << mob.mon_health << "." << endl;
        Sleep(800);
    }
    while(true){
        if(mob.mon_name=="reptile"){
            mob.rep_dmg();
        }
        else if(mob.mon_name=="bird"){
            mob.bi_dmg();
        }
        else if(mob.mon_name=="humanoid"){
            mob.hum_dmg();
        }
        else{
            mob.hy_dmg();
        }

        if(character.player_class=="warrior"){
            character.warrior_dmg();
        }
        else if(character.player_class=="rogue"){
            character.rogue_dmg();
        }
        else{
            character.mage_dmg();
        }
        cout << "You attack, dealing " << character.dmg << " damage." << endl;
        Sleep(800);
        mob.mon_health -= character.dmg;
        if(mob.mon_health <= 0){
            if(!dungeon_setup.isactive){
                mob.mon_count.erase(mob.mon_count.begin()+freq);
                if(mob.mon_count.size()==0){
                    cout << "You win. To be expanded. For now, game reset." << endl;
                    main();
                }
            }
            cout << "You defeated the monster! You earn " << mob.exp_drop << " experience." << endl;
            character.exp += mob.exp_drop;
            Sleep(800);
            cout << "You also earned " << mob.money_drop << " coins." << endl;
            character.money += mob.money_drop;
            Sleep(800);
            if(character.exp>=100){
                cout << "Congratulations, you went up a level! " << endl;
                Sleep(800);
                if(character.player_class=="rogue"){
                    cout << "Your health increases by 5 and your damage by 3." << endl;
                }
                else if(character.player_class=="warrior"){
                    cout << "Your health increases by 5 and your damage by 4." << endl;
                }
                else{
                    cout << "Your health increases by 5 and your damage by 5." << endl;
                }
                Sleep(800);
                cout << "But as you increase in strength, so do the monsters." << endl;
                Sleep(800);
                character.level_up();
                mob.mon_level_up();
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
        cout << "The monster's health drops to " << mob.mon_health << "." << endl;
        Sleep(800);
        cout << "The monster attacks, dealing " << mob.mon_dmg << " damage." << endl;
        Sleep(800);
        character.health -= mob.mon_dmg;
        if(character.health <= 0){
            cout << "You have died." << endl;
            dead();
        }
        cout << "Your health drops to " << character.health << "." << endl;
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
                        if(mob.mon_name=="reptile"){
                            mob.rep_dmg();
                        }
                        else if(mob.mon_name=="bird"){
                            mob.bi_dmg();
                        }
                        else if(mob.mon_name=="humanoid"){
                            mob.hum_dmg();
                        }
                        else{
                            mob.hy_dmg();
                        }
                        cout << "You try to escape, but trip." << endl;
                        Sleep(800);
                        cout << "The " << mob.mon_name << " uses your blunder to attack again." << endl;
                        Sleep(800);
                        cout << "It attacks, dealing " << mob.mon_dmg << " damage." << endl;
                        Sleep(800);
                        character.health -= mob.mon_dmg;
                        if(character.health<=0){
                            cout << "You have died." << endl;
                            dead();
                        }
                        cout << "Your health drops to " << character.health << "." << endl;
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
            if(character.player_class=="warrior"){
                character.warrior_dmg();
            }
            else if(character.player_class=="mage"){
                character.mage_dmg();
            }
            else{
                character.rogue_dmg();
            }
            cout << "You attack first, dealing " << character.dmg << " damage." << endl;
            Sleep(1200);
            mob.mon_health -= character.dmg;
            if(mob.mon_health <= 0){
                cout << "The monster is dead!" << endl;
                character.exp += mob.exp_drop;
                if(character.exp>=100){
                    cout << "You go up a level!" << endl;
                    character.level_up();
                    mob.mon_level_up();
                    character.exp -= 100;
                }
                cout << "Prepare for the next battle." << endl;
                continue;
            }
        }
        else{
            mob.el_dmg();
            cout << "The monster attacks first, dealing " << mob.mon_dmg << " damage." << endl;
            Sleep(1200);
            character.health -= mob.mon_dmg;
            if(character.health<=0){
                cout << "You died. Game reset for now." << endl;
                dead();
            }
        }
        while(true){
            if(character.player_class=="warrior"){
                character.warrior_dmg();
            }
            else if(character.player_class=="mage"){
                character.mage_dmg();
            }
            else{
                character.rogue_dmg();
            }
            mob.el_dmg();
            cout << "You attack, dealing " << character.dmg << " damage." << endl;
            Sleep(1200);
            mob.mon_health -= character.dmg;
            if(mob.mon_health<=0){
                elite_count--;
                cout << "You defeated the monster!" << endl;
                Sleep(1200);
                character.exp+=100;
                if(character.exp>=100){
                    cout << "You go up a level!" << endl;
                    Sleep(1200);
                    character.level_up();
                    mob.mon_level_up();
                    character.exp-=100;
                }
                cout << "Prepare for the next battle." << endl;
                break;
            }
            cout << "The monster attacks, dealing " << mob.mon_dmg << " damage." << endl;
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
        mob.boss_dmg();
        cout << "The boss attacks first, dealing " << mob.mon_dmg << " damage." << endl;
        character.health -= mob.mon_dmg;
        if(character.health<=0){
            cout << "The boss killed you. Game reset." << endl;
            dead();
        }
        if(character.player_class=="warrior"){
            character.warrior_dmg();
        }
        else if(character.player_class=="mage"){
            character.mage_dmg();
        }
        else{
            character.rogue_dmg();
        }
        cout << "You attack, dealing " << character.dmg << " damage." << endl;
        mob.mon_health-=character.dmg;
        if(mob.mon_health<=0){
            cout << "You have defeated the boss!!!" << endl;
            Sleep(1200);
            character.exp += mob.exp_drop;
            while(character.exp>=100){
                cout << "You leveled up!" << endl;
                Sleep(1200);
                character.level_up();
                mob.mon_level_up();
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
    int dot_count = 1;
    int dot_stop = 3;
    cout << "You leave your camp, looking for anything interesting." << endl;
    cout << "You find a long path and walk along it." << endl;
    for (dot_count = 1; dot_count <= dot_stop; dot_count++){
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
    getline(cin, action);
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
        cout << character.player_class << endl;
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
        cout << "Headgear: " << character.equip_places.find("head")->second << endl;
        cout << "Chestplate: " << character.equip_places.find("chest")->second << endl;
        cout << "Arms: " << character.equip_places.find("arms")->second << endl;
        cout << "Weapon: " << character.equip_places.find("hands")->second << endl;
        cout << "Leggings: " << character.equip_places.find("legs")->second << endl;
        cout << "Boots: " << character.equip_places.find("feet")->second << endl;
        base();
    }
    else if(action == "save"){
        save();
        cout << "Your game is saved. Only one saved game is possible at a time." << endl;
        base();
    }
    else if(action == "load"){
        load();
        base();
    }
    else if(action == "equip"){
        if(character.player_class=="warrior"){
            equipment.equip_heavy_items();
        }
        else if(character.player_class=="rogue"){
            equipment.equip_light_items();
        }
        else if(character.player_class=="mage"){
            equipment.equip_arcane_items();
        }
        base();
    }
    else if(action=="help"){
        cout << "Type 'rest' to regain your health, 'explore' if you're feeling adventerous, " << endl;
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
