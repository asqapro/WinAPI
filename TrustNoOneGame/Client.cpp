#include "ClientServer.h"

using namespace std;

player* playerList = NULL;
int TCP_PORT = 5721;

int playerNumber = -1;

int dataClient[4];

int initialConnection(SOCKET s){
    if(socketState(s, 0) == 1){
        int ini = -1;
        sendData(s, &ini, sizeof(ini));
    }
    return 1;
}

SOCKET client(SOCKET s){
    int state = -2;
    if(s == INVALID_SOCKET){
        cout << "A";
        s = makeSocket();
        cout << "B";
    }
    if(playerCount == -1){
        initialConnection(s);
        while(socketState(s, 0) != 1){ //while data is not available to read, wait
            continue;
        }
        readData(s, 1, 1); //stored in dataClient
        playerCount = dataClient[0];
        playerNumber = dataClient[1];
        cout << playerCount << endl;
        cout << playerNumber << endl;
    }
    else{
        state = -3;
        sendData(s, &state, sizeof(state)); //"reopening" the socket
        if(playerList == NULL){
            playerList = new player[playerCount];
            playerList[0] = player(5,5);
            playerList[0].playerNumber = playerNumber; //only the first player in playerList needs playerNumber set
            for(int iter = 1; iter < playerCount; iter++){
                playerList[iter] = player(1,1);
                playerList[iter].playerNumber = iter;
            }
        }
        dataClient[0] = playerList[0].playerNumber; //only the first player needs to be sent (client's player)
        dataClient[1] = playerList[0].locationX;
        dataClient[2] = playerList[0].locationY;
        sendData(s, dataClient, sizeof(dataClient));
        while(socketState(s, 0) != 0){ //while data is not available to read, wait
            continue;
        }
        cout << dataClient[0] << " " << dataClient[1] << " " << dataClient[2] << endl; //data only being read into dataClient[0]
        for(int iter = 1; iter < playerCount; iter++){
            readData(s, 1, 1);
            cout << dataClient[0] << " " << dataClient[1] << " " << dataClient[2] << endl;
            playerList[iter].playerNumber = dataClient[0];
            playerList[iter].locationX = dataClient[1];
            playerList[iter].locationY = dataClient[2];
            //cout << "Player" << iter << " Player Number: " << playerList[iter].playerNumber << endl;
            //cout << "Player" << iter << " X: " << playerList[iter].locationX << endl;
            //cout << "Player" << iter << " Y: " << playerList[iter].locationY << endl;
            Sleep(1000);
        }
        state = -2;
        sendData(s, &state, sizeof(state)); //"closing" the socket
    }
    return s;
}
