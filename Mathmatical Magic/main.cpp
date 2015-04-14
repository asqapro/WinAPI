#include <iostream>
#include <string>
#include <algorithm> //For setting strings to lowercase
#include <sstream>
#include <map> //For operator processing
#include <vector> //Lists or arrays or whatever you may call them

using namespace std;

void choose_path_alg();
void var_solve();
void factor();
void slope();
void inequalities();

int main()
{
    choose_path_alg(); //For now, the only thing to solve is algebra problems
    return 0;
}

void choose_path_alg(){ //Choose the type of math - alegbra only
    string choose = ""; //User input string
    cout << "What math are you doing? ";
    getline(cin, choose); //Get the user input
    transform(choose.begin(), choose.end(), choose.begin(), ::tolower); //Set the string to lowercase

    if(choose == "equations"){ //Process user input
        var_solve();
    }
    if(choose == "factoring"){
        factor();
    }
    else if(choose == "slope"){
        slope();
    }
    else if(choose == "inequalities"){
        inequalities();
    }
    else{
        cout << "Please choose \'Factoring\', \'Euqations\', or \'Slope\'.";
        cout << "You may have entered your selection incorrectly. Please use the format shown above.";
        choose_path_alg(); //Loop back if an error occurs
    } //End process user input
}

void var_solve(){
    string equation = "";
    cout << "Euqation: ";
    getline(cin, equation); //Get the user's equation to solve

    unsigned equalPos = equation.find("="); //Find the index of '=' in the equation

    //Break the equation up into the left and right sides
    string leftSide = equation.substr(1, equalPos); //From the start to the equals sign
    string rightSide = equation.substr(equalPos); //From the equals sign to the end

    string solveFor = "";
    cout << "Variable(s) to solve for: ";
    getline(cin, equation); //Get the variables used in said equation

    map<string, string> changeOp; //Operator swap map
    changeOp.insert(make_pair("+", "-")); //Swap + to -
    changeOp.insert(make_pair("-", "+")); //Swap - to +
    changeOp.insert(make_pair("*", "/")); //Swap * to /
    changeOp.insert(make_pair("/", "*")); //Swap / to *

    //Collecting like terms to be added. Reference MathmaticalMagicRevamp.py


    //Move all variables to left side; move all numbers out of left side
    for(int iter = 0; iter < leftSide.length(); iter++){ //Loop through the left side
        if(solveFor.find(leftSide[iter]) != string::npos && leftSide[iter+1] != " "){ //If the current item is not a variable
        //Check if leftSide[iter] is in sovleFor         and check if the next item is a space
            leftSide[iter-1] = changeOp.find(leftSide[iter-1]) ->second;
        }
    }
}

void factor(){

}

void slope(){

}

void inequalities(){

}
