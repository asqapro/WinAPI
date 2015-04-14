#include "ClientServer.h"

using namespace std;

int playerCount = -1;

string serverIP;

int setup(){
    string runServer = "";
    cout << "Run the server?(y/n) ";
    cin >> runServer;
    if(runServer == "y"){
        cout << "How many player slots? ";
        cin >> playerCount;
        server();
        cout << "Server done" << endl;
        Sleep(100000);
        return 0;
    }
    return 1;
}

player mainAct(){
    player main(0,0);
    string action = "";
    cout << "> ";
    return main;
}

int main()
{
    //playerList[0] = player(0,0);
    WSADATA w;
    WSAStartup (0x0202, &w);   // Fill in WSA info
    if(!setup()){
        cout << "Server exiting." << endl;
        return 0;
    }
    cout << "Server IP? ";
    cin >> serverIP;
    SOCKET s = INVALID_SOCKET;
    s = client(s); //set up initial connection
    while(true){
        s = client(s);
    }
    WSACleanup();
    return 0;
}
