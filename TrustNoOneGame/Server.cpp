#include "ClientServer.h"

using namespace std;

string localIP;

int dataServer[4];

int update(SOCKET s, int** playerData, int playerNumber){
    for(int iter = 0; iter < playerCount; iter++){
        if(playerData[iter][3] == 0){ //if playerData[iter] is not set
            continue; //skip it
        }
        if(playerData[iter][1] == playerNumber){ //if the player number matches the connection number
            continue;
        }
        sendData(s, playerData[iter], sizeof(playerData[iter]));
    }
    return 1;
}

int server(){
    //localIP = "192.168.56.1";
    localIP = "127.0.0.1";
    int iniInfo[2]; //1 int for playerCount, 1 int for pNum (playerNumber)
    int** playerData = new int*[playerCount];
    for(int iter = 0; iter < playerCount; iter++){
        playerData[iter] = new int[4]();
    }
    bool iniList[playerCount][3];
    memset(iniList, false, playerCount*sizeof(bool));
    SOCKET hostSock = setUpListener(localIP.c_str(), htons(TCP_PORT));
    SOCKET connections[playerCount];
    memset(connections, 0, playerCount*sizeof(SOCKET));
    SOCKET s;
    int state = -1;
    while(true){
        for(int iter = 0; iter < playerCount; iter++){
            state = -1;
            if(connections[iter] == 0){ //if the socket is not being used
                connections[iter] = socketState(0, hostSock); //try to fill it
            }
            s = connections[iter];
            if(s != 0){ //if the socket is not dead
                state = socketState(s, 0);
            }
            if(state == 0){ //0 means data is available to read
                cout << dataServer[0] << " " << dataServer[1] << " " << dataServer[2] << " " << dataServer[3] << endl;
                readData(s, 0, 1);
                if(dataServer[0] == -1){ //startup indicator
                    iniList[iter][0] = true;
                    iniList[iter][1] = true;
                }
                else if(dataServer[0] == -2){
                    iniList[iter][2] = true; //signifying connection is "closed"
                }
                else if(dataServer[0] == -3){
                    iniList[iter][2] = false; //signifying connection is "reopened"
                }
                else{
                    cout << dataServer[0] << " " << dataServer[1] << " " << dataServer[2] << " " << dataServer[3] << endl;
                    playerData[iter][0] = dataServer[0];
                    playerData[iter][1] = dataServer[1];
                    playerData[iter][2] = dataServer[2];
                    playerData[iter][3] = 1;
                    playerData[1][0] = 1;
                    playerData[1][1] = 1;
                    playerData[1][2] = 1;
                    playerData[1][3] = 1;
                }
            }
            else if(state == 1){ //1 means the connection is alive but there is no data to read (implied data to be recieved)
                if(iniList[iter][2]){ //meant to be skipped
                    continue;
                }
                if(iniList[iter][0]){
                    iniInfo[0] = playerCount;
                    iniInfo[1] = iter;
                    sendData(s, iniInfo, sizeof(iniInfo)/sizeof(iniInfo[0]));
                    iniList[iter][0] = false;
                }
                else if(iniList[iter][1]){ //if ini is done
                    update(connections[iter], playerData, iter);
                }
            }
            else if(state == -1){ //socket is dead
                connections[iter] = 0;
            }
        }
        Sleep(16); //62.5 FPS
    }
    return 0;
}
