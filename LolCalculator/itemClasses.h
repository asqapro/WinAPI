#ifndef ITEMCLASSES_H_INCLUDED
#define ITEMCLASSES_H_INCLUDED

#include "headers.h"

using namespace std;

extern string map;

class item
{
    public:

    string map;
    vector<int> types; //item can have multiple attributes
    double healthBonus;
    double manaBonus;
    double magResBonus;
    double healthRegenBonus;
    double manaRegenBonus;
    double armorBonus;
    double ADBonus;
    double APBonus;
    double critChanceBonus;
    double ASBonus;
    double lifeStealBonus;
    double CDRBonus;
    double movementBonus;

    item(vector<int> pTypes, vector<double> bonuses, string pMap);
};

#endif // ITEMCLASSES_H_INCLUDED
