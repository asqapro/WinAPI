#ifndef DUNGEONFUNCTIONS_H_INCLUDED
#define DUNGEONFUNCTIONS_H_INCLUDED

#include "Headers.h"

using namespace std;

extern vector< vector< vector<int> > > dungeon; //forced to make this global due to act()
extern map< vector<int>, vector<int> > connections;

map< vector<int>, vector<int> > createConnections(vector< vector< vector<int> > > dungeonTemp);
vector< vector< vector< int> > > createDoors(vector< vector< vector<int> > > dungeonTemp); //note: Passageways/ stairways "connect" doors
vector< vector< vector< int> > > createNPCS(vector< vector< vector<int> > > dungeonTemp);
vector< vector< vector< int> > > createObjects(vector< vector< vector<int> > > dungeonTemp);
vector< vector< vector< int> > > createTreasure(vector< vector< vector<int> > > dungeonTemp);
vector< vector< vector< int> > > createDungeon();

#endif // DUNGEONFUNCTIONS_H_INCLUDED
