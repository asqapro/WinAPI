//====================================
//AWhisnantBC.cpp
//Author: Adam Whisnant
//This program is entirely my own work
//====================================

#include <iostream> //include standard library for I/O opertions
#include <string>

using namespace std; //use standard namespace

const string name          = "Adam J. Whisnant     "; //string containing my name
const string streetAddress = "1000 Ben Graves Drive"; //string containing my adress
const string phoneNumber   = "251-828-2743         "; //string containing made-up phone number
const string emailAddress  = "ConedIce@hotmail.com "; //string containing made-up email address

int main() //entry point of program
{
    for(int iter = 0; iter < 4; iter++) //loop from 4 times to print each set of cards
    {
        cout << name          << "\t\t" << name          << endl; //print name for both cards. Two cards per line, two names per line
        cout << streetAddress << "\t\t" << streetAddress << endl; //print streetAddress for both cards
        cout << phoneNumber   << "\t\t" << phoneNumber   << endl; //print phoneNumber for both cards
        cout << emailAddress  << "\t\t" << emailAddress  << endl; //print emailAdress for both cards
        cout << "\n\n"; //print two new lines to break apart each set of cards
    }
    return 0; //return 0 to signify the program ran correctly
}
