#include "itemClasses.h"

using namespace std;

item::item(vector<int> pTypes, vector<double> bonuses, string pMap)
{
    map = pMap;
    types = pTypes;
    healthBonus = bonuses[0];
    manaBonus = bonuses[1];
    magResBonus = bonuses[2];
    healthRegenBonus = bonuses[3];
    manaRegenBonus = bonuses[4];
    armorBonus = bonuses[5];
    ADBonus = bonuses[6];
    APBonus = bonuses[7];
    critChanceBonus = bonuses[8];
    ASBonus = bonuses[9];
    lifeStealBonus = bonuses[10];
    CDRBonus = bonuses[11];
    movementBonus = bonuses[12];
}
