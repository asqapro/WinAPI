#ifndef STIM_H_INCLUDED
#define STIM_H_INCLUDED

#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

map<string, string> responses;

string stim(string input){
    responses["gay"] = "no u";
    return responses.find(input)->second;
}

#endif // STIM_H_INCLUDED
