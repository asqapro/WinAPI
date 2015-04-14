#ifndef CLIENTSERVER_H_INCLUDED
#define CLIENTSERVER_H_INCLUDED

#include <iostream>
#include <wininet.h>
#include <winsock2.h>
#include "Player.h"

extern int playerCount; //implemented in main.cpp
extern std::string serverIP; //implemented in main.cpp
extern std::string localIP; //implemented in Server.cpp
extern int TCP_PORT; //implemented in Client.cpp
extern int dataServer[4];
extern int dataClient[4];

int server(); //implented in Server.cpp
SOCKET client(SOCKET s); //implemented in Client.cpp
int waitToRead(SOCKET s); //implented in Server.cpp

SOCKET makeConnection(SOCKET s, sockaddr* name, int namelen); //implemented in SocketFunctions.cpp
bool closeConnection (SOCKET s); //implemented in SocketFunctions.cpp
int readData(SOCKET s, int clientOrServer, u_long mode); //implemented in SocketFunctions.cpp
int sendData(SOCKET s, int*, int len); //implemented in SocketFunctions.cpp
SOCKET setUpListener(const char* pcAddress, int nPort); //implemented in SocketFunctions.cpp
SOCKET acceptConnection(SOCKET ListeningSocket); //implemented in SocketFunctions.cpp
int socketState(SOCKET s, SOCKET host); //implemented in SocketFunctions.cpp
bool toRead(SOCKET s); //implemented in SocketFunctions.cpp
SOCKET makeSocket();

#endif // CLIENTSERVER_H_INCLUDED
