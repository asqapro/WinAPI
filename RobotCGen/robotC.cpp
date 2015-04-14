#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <wx/msgdlg.h>
#include "RobotCGenMain.h"
#include "RobotCGenApp.h"

using namespace std;

void joystick(string input, string motor, string spec);
void button(string input, string motor, string spec, string power);
void makeMotor(string motor, string Motor_Type);

int taskTabs;
int loopTabs;

string tab(string which){ //for indentation within the generated code
    string tabString = "";
    if(which == "task"){
        for(int x = 0; x < taskTabs; x++){
            tabString += "\t";
        }
    }
    else{
        for(int x = 0; x < taskTabs + loopTabs; x++){
            tabString += "\t";
        }
    }
    return tabString;
}

vector<string> mainTask; //A vector of the RobotC commands to write to the main task
vector<string> mainLoop; //A vector of the RobotC commands to write to the main loop (while(true))
vector<string>::iterator mT, mL; //iterators for both of those vectors

ofstream program;

map<string, string> controllerBtns; //A map for the controller buttons
map<string, string> controllerJSticks; //A map for the controller joysticks
map<string, string>::iterator it1, it2; //iterators for said maps

vector<string> specKeyWords; //Special cases

vector<string> motors; //A list of motor configs to write
vector<string>::iterator mot; //iterator for that list
vector<string> motor_types; //A list of the different motor types (servo, normal)
vector<string>::iterator mot_type; //iterator for the list

string PortNumStr; //Must convert the port number to a string to write more easily to the file
vector<string> portNums; //A list of the port numbers the user inputted
vector<string>::iterator port; //iterator for the ports

bool process(wxString wxInput, wxString wxMotor, wxString wxSpecial, wxInt16 wxPower, wxString wxMotorType, wxInt16 wxPortNum){ //process the user input
    string input = string(wxInput.mb_str()); //convert the wx items to normal items
    string motor = string(wxMotor.mb_str());
    string special = string(wxSpecial.mb_str());
    wxString wxPowerString;
    wxPowerString << wxPower;
    string power = string(wxPowerString.mb_str());
    string Motor_Type = string(wxMotorType.mb_str());
    wxString wxPortNumString;
    wxPortNumString << wxPortNum;
    string PortNumStr = string(wxPortNumString.mb_str());

    if(motor != ""){ //for last input, when GUI returns "" for motor
        motor += "Motor";
        if(find(motors.begin(), motors.end(), motor) == motors.end()){ //If the motor has not yet been created
            motors.push_back(motor); //make the motor
            motor_types.push_back(Motor_Type);
            portNums.push_back(PortNumStr);
        }
    }
    it1 = controllerBtns.find(input); //look for the input in the button map
    it2 = controllerJSticks.find(input); //and the joystick map
    if(it1 != controllerBtns.end()){ //if the input is found in the buttons map
        button(input, motor, special, power); //write the code for button control
        return false; //do not end the GUI yet
    }
    else if(it2 != controllerJSticks.end()){; //if the input in found in the joysticks map
        joystick(input, motor, special); //write the code for joystick control
        return false; //do not end the GUI yet
    }
    else{ //if the input is not a button or joystick ("" as returned by "Cancled" GUI)
        for(mT = mainTask.begin(); mT != mainTask.end(); ++mT){ //write the main task code
            program << *mT;
        }
        for(mL = mainLoop.begin(); mL != mainLoop.end(); ++mL){ //write the main loop code
            program << *mL;
        }
        loopTabs -= 1;
        program << tab("loop") + "}\n";
        program.close(); //close the main task
        mot_type = motor_types.begin();
        port = portNums.begin();
        for(mot = motors.begin(); mot != motors.end(); ++mot){ //make the motors (#pragma config)
            makeMotor(*mot, *mot_type);
            mot_type++;
            port++;
        }
        ofstream output;
        output.open("robotCode.c", ios::out | ios::app);
        output << "}"; //I had a very hard time counting all of the ending braces I needed, and where. Adding this closes out the main task for me easily
        return true; //end the GUI
    }
}

void setup(){
    controllerJSticks["Ch1"] = "vexRT[Ch1]"; //populate the map with the joystick controls (as defined by RobotC)
    controllerJSticks["Ch2"] = "vexRT[Ch2]";
    controllerJSticks["Ch3"] = "vexRT[Ch3]";
    controllerJSticks["Ch4"] = "vexRT[Ch4]";
    controllerBtns["5U"] = "vexRT[Btn5U]"; //and the button controls
    controllerBtns["5D"] = "vexRT[Btn5D]";
    controllerBtns["6U"] = "vexRT[Btn6U]";
    controllerBtns["6D"] = "vexRT[Btn6D]";
    controllerBtns["7U"] = "vexRT[Btn7U]";
    controllerBtns["7D"] = "vexRT[Btn7D]";
    controllerBtns["7L"] = "vexRT[Btn7L]";
    controllerBtns["7R"] = "vexRT[Btn7R]";
    controllerBtns["8U"] = "vexRT[Btn8U]";
    controllerBtns["8D"] = "vexRT[Btn8D]";
    controllerBtns["8L"] = "vexRT[Btn8L]";
    controllerBtns["8R"] = "vexRT[Btn8R]";

    program.open("robotCode.c"); //the file to write to
    mainTask.push_back("task main(){\n"); //open the main task code block
    taskTabs += 1;
    mainLoop.push_back(tab("task") + "while(true){\n"); //open the main loop to keep the program running
    loopTabs += 1;
}

void joystick(string input, string motor, string spec){ //the joystick code
    mainLoop.push_back(tab("loop") + "motor[" + motor + "] = vexRT[" + input + "];\n"); //set the motor to a joystick
}

void button(string input, string motor, string spec, string power){ //the button code
    string buttonState = "toggle" + input; //toggle the motor back and forth (multi-button toggle can be added in)
    if(spec != "None"){ //if there is a special case
        if(spec == "const"){ //if the special case is constant motor power
            string nonConst = ""; //the non-constant input from the controller
            for(mL = mainLoop.begin(); mL != mainLoop.end();){ //search for the non-constant input
                string item = *mL;
                if(item.find(motor) != string::npos){
                    nonConst = item;
                    mainLoop.erase(mL);
                    break;
                }
                else{
                    ++mL;
                }
            }
            if(nonConst == ""){ //if the non-constant input is not found, give the user an error
                string msg = "You have not assigned what controls this motor normally.";
                wxString wxMsg(msg.c_str(), wxConvUTF8);
                wxMessageBox(wxMsg, _("Error"));
            }
            else{ //non-constant input found
                mainTask.push_back(tab("task") + "bool " + buttonState + " = false;\n");  //start like a normal button toggle
                mainLoop.push_back(tab("loop") + "if (vexRT[Btn" + input + "]){\n"); //if the button is pressed
                loopTabs += 1;
                mainLoop.push_back(tab("loop") + "if(" + buttonState + "){\n"); //if the toggle state is on
                loopTabs += 1;
                mainLoop.push_back(tab("loop") + buttonState + " = false;\n"); //toggle it off if it was on
                loopTabs -= 1;
                mainLoop.push_back(tab("loop") + "}\n"); //close the if statement
                mainLoop.push_back(tab("loop") + "else{\n"); //if the toggle state is off
                loopTabs += 1;
                mainLoop.push_back(tab("loop") + buttonState + " = true;\n"); //toggle it on
                loopTabs -= 1;
                mainLoop.push_back(tab("loop") + "}\n"); //close the else statement
                loopTabs -= 1;
                mainLoop.push_back(tab("loop") + "}\n"); //close the statement checking for button input
                mainLoop.push_back(tab("loop") + "if(" + buttonState + "){\n"); //if button state is true
                loopTabs += 1;
                mainLoop.push_back(tab("loop") + "motor[" + motor + "] = " + power + ";\n"); //set the motor to a power
                loopTabs -= 1;
                mainLoop.push_back(tab("loop") + "}\n"); //close the if statement
                mainLoop.push_back(tab("loop") + "else{\n");

                mainLoop.push_back("\t" + nonConst); //set the motor to whatever controlled it normally

                mainLoop.push_back(tab("loop") + "}\n");
            }
        }
    }
    else{ //if no special cases
        mainTask.push_back(tab("task") + "bool " + buttonState + " = false;\n"); //set the button toggle state to false initially
        mainLoop.push_back(tab("loop") + "if (vexRT[Btn" + input + "]){\n"); //if the button is pressed
        loopTabs += 1;
        mainLoop.push_back(tab("loop") + "if(" + buttonState + "){\n"); //if the state is on
        loopTabs += 1;
        mainLoop.push_back(tab("loop") + buttonState + " = false;\n"); //toggle it off
        mainLoop.push_back(tab("loop") + "motor[" + motor + "] = 0;\n"); //set the motor to low end power *add low-to-high powers*
        loopTabs -= 1;
        mainLoop.push_back(tab("loop") + "}\n");
        mainLoop.push_back(tab("loop") + "else{\n"); //if the state is off
        loopTabs += 1;
        mainLoop.push_back(tab("loop") + buttonState + " = true;\n"); //toggle it on
        mainLoop.push_back(tab("loop") + "motor[" + motor + "] = " + power + ";\n"); //set the motor to max power
        loopTabs -= 1;
        mainLoop.push_back(tab("loop") + "}\n");
        loopTabs -= 1;
        mainLoop.push_back(tab("loop") + "}\n");
    }
}

void makeMotor(string motor, string Motor_Type){ //#pragma config motors
    if(Motor_Type == "Servo"){
        Motor_Type = "ServoStandard";
    }
    else{
        Motor_Type = "Normal";
    }
    ifstream original; //the original code (pre-pending to already-written file)
    original.open("robotCode.c"); //open the original code
    string data;
    original.seekg(0, ios::end);
    data.resize(original.tellg());
    original.seekg(0, ios::beg);
    original.read(&data[0], data.size());
    original.close(); //read in the contents and close the original

    ofstream modified; //the new code, configed motors pre-pended
    modified.open("robotCode.c"); //open the original file (overwrite it)
    string toWrite = "#pragma config(Motor, port" + *port + ", " + motor + ", tmotor" + Motor_Type + ", openLoop)\n"; //config the motor with the input specified
    modified << toWrite; //write the motor config
    modified << data; //write the original data after
    modified.close(); //close the file
}
