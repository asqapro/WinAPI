#ifndef CHAMPCLASS_H_INCLUDED
#define CHAMPCLASS_H_INCLUDED

#include "headers.h"

using namespace std;

class skillSlot
{
    public:
    double ADDmg;
    double APDmg;
    double slowTime;
    double slowPercent;
    double stunTime;
    double airborneTime;
    double blindTime;
    double disarmTime; //polymorph
    double charmTime;
    double fleeTime; //speed reduction, 33%
    double tauntTime;
    double rootTime;
    double silenceTime;
    double stasisTime;
    double suppressionTime;
    double castRange;
    double aoeRange;
    double cooldown;
    double cost;
    skillSlot(double stats[])
    {
        ADDmg = stats[0];
        APDmg = stats[1];
        slowTime = stats[2];
        slowPercent = stats[3];
        stunTime = stats[4];
        airborneTime = stats[5];
        blindTime = stats[6];
        disarmTime = stats[7];
        charmTime = stats[8];
        fleeTime = stats[9];
        tauntTime = stats[10];
        rootTime = stats[11];
        silenceTime = stats[12];
        stasisTime = stats[13];
        suppressionTime = stats[14];
        castRange = stats[15];
        aoeRange = stats[16];
        cooldown = stats[17];
        cost = stats[18];
    }
};

class champion
{
    public:

    double health;
    double healthRegen;
    double healthScale;
    double healthRegenScale;

    double mana;
    double manaRegen;
    double manaScale;
    double manaRegenScale;

    int energy;
    int energyRegen;

    int range;

    double AD;
    double ADScale;

    double AS;
    double ASBase;
    double ASScale;

    double AP;

    double armor;
    double armorScale;

    double magRes;
    double magResScale;

    int movSpeed;

    double flatArmorPen;
    double percentArmorPen;
    double flatMagPen;
    double percentMagPen;

    string champName;
    string summonerName;
    string resource;

    double level;

    vector<double> cooldowns;

    vector<int> expRequired;

    int critDmg;
    int critPercent;

    vector<skillSlot> skills;

    champion(float stats[], string pResource, string pChampName, string pSummonerName);

    void levelUp();

    double calcADDealt(champion champ);
    double calcAPDealt(champion champ);
    //double calcDeathTimer()
    void addItem(vector<int> itemTypes, vector<double> bonuses);
    void applyOnHitProcs(champion champ);
    void addSkill();
};

extern vector<champion> champList;

#endif // CHAMPCLASS_H_INCLUDED
