#include "championClasses.h"

void champion::addSkill()
{
    double stats[19];
    for(unsigned int iter = 0; iter < 19; iter++)
    {
        stats[iter] = 0; //read stats from file
    }
    skills.push_back(skillSlot(stats));
}
