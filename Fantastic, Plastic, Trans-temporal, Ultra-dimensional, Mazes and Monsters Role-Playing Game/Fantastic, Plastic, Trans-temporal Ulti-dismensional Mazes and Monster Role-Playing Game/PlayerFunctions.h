#ifndef PLAYERFUNCTIONS_H_INCLUDED
#define PLAYERFUNCTIONS_H_INCLUDED

#include "Headers.h"

//NOTE: only Player.cpp #include's this file

using namespace std;

vector<int> move(vector<int> playerPosition);
vector<int> act(vector<int> playerPosition, int command, map< vector<int>, vector<int> > connections);
void battle();
void level();
int keypress();

void help();

int searchArray(string searchFor, string searchIn[], int size);

#endif // PLAYERFUNCTIONS_H_INCLUDED
