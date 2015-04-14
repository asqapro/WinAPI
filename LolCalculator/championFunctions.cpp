#include "championClasses.h"
#include "itemClasses.h"

vector<champion> champList;

champion::champion(float stats[], string pResource, string pChampName, string pSummonerName)
{
    health = stats[0];
    healthScale = stats[1];
    AD = stats[2];
    ADScale = stats[3];
    AS = stats[4];
    ASBase = AS; //preserve base attack speed
    ASScale = stats[5];
    movSpeed = stats[6];
    healthRegen = stats[7];
    healthRegenScale = stats[8];
    AP = 0;
    armor = stats[9];
    armorScale = stats[10];
    magRes = stats[11];
    magResScale = stats[12];
    range = stats[13];
    flatArmorPen = 0;
    percentArmorPen = 0;
    flatMagPen = 0;
    percentMagPen = 0;
    champName = pChampName;
    summonerName = pSummonerName;
    expRequired.push_back(180);
    for(int iter = 0; iter < 18; iter++)
    {
        expRequired.push_back((expRequired[iter])+100);
    }
    resource = pResource;
    if(resource == "Mana")
    {
        mana = stats[14];
        manaScale = stats[15];
        manaRegen = stats[16];
        manaRegenScale = stats[17];
    }
    else if(resource == "Energy")
    {
        energy = stats[14];
        energyRegen = stats[15];
    }
    else
    {
        mana = 0;
        manaScale = 0;
        manaRegen = 0;
        manaRegenScale = 0;
        energy = 0;
        energyRegen = 0;
    }
    critDmg = 200;
    critPercent = 0;
}

void champion::levelUp()
{
    health += healthScale;
    healthRegen += healthRegenScale;
    AD += ADScale;
    AS += ASScale*(ASBase/100);
    armor += armorScale;
    magRes += magResScale;
}

void champion::addItem(vector<int> itemTypes, vector<double> bonuses)
{
    item newItem(itemTypes, bonuses, map);

}

double champion::calcADDealt(champion champ)
{
    double armorAfterPen = champ.armor - (percentArmorPen/100.0);
    armorAfterPen -= flatArmorPen;
    if(armorAfterPen < 0)
    {
        armorAfterPen = 0;
    }
    double trueAD = AD - armorAfterPen;
    if(trueAD < 0)
    {
        trueAD = 0;
    }
    return trueAD;
}

double champion::calcAPDealt(champion champ)
{
    double magResAfterPen = champ.magRes - (percentMagPen/100.0);
    magResAfterPen -= flatMagPen;
    if(magResAfterPen < 0)
    {
        magResAfterPen = 0;
    }
    double trueAP = AP - magResAfterPen;
    if(trueAP < 0)
    {
        trueAP = 0;
    }
    return trueAP;
}
