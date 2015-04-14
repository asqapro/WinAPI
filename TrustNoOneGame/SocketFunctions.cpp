#include "ClientServer.h"

using namespace std;

SOCKET makeConnection(SOCKET s, sockaddr* name, int namelen){
    connect(s, name, namelen);
    return s;
}

bool closeConnection(SOCKET s){
    if(s){
        closesocket(s);
    }
    else{
        return false;
    }
    return true;
}

SOCKET acceptConnection(SOCKET ListeningSocket){
    return accept(ListeningSocket, NULL, NULL);
}

SOCKET makeSocket(){
    //Fill out the information needed to initialize a socket…
    SOCKADDR_IN target; //Socket address information

    target.sin_family = AF_INET; // address family Internet
    target.sin_addr.s_addr = inet_addr(serverIP.c_str()); //Target IP
    target.sin_port = htons(TCP_PORT);

    SOCKET s = socket(AF_INET, SOCK_STREAM, 0); //Create socket
    if(s == INVALID_SOCKET){
        return INVALID_SOCKET; //Couldn't create the socket
    }
    //Try connecting...
    cout << "??d" << endl;
    s = makeConnection(s, (SOCKADDR*)&target, sizeof(target));
    cout << "Afef" << endl;
    if(s == (unsigned int)SOCKET_ERROR){
        return INVALID_SOCKET; //Couldn't connect
    }
    return s;
}

SOCKET setUpListener(const char* pcAddress, int nPort){ //specific to Server.cpp
    u_long nInterfaceAddr = inet_addr(pcAddress);
    if(nInterfaceAddr != INADDR_NONE){
        SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
        if(s != INVALID_SOCKET){
            sockaddr_in sinInterface;
            sinInterface.sin_family = AF_INET;
            sinInterface.sin_addr.s_addr = nInterfaceAddr;
            sinInterface.sin_port = htons(TCP_PORT);
            if (bind(s, (sockaddr*)&sinInterface, sizeof(sinInterface)) != SOCKET_ERROR){
                listen(s, playerCount);
                return s;
            }
        }
    }
    return INVALID_SOCKET;
}

int readData(SOCKET s, int clientOrServer, u_long mode){
    ioctlsocket(s,FIONBIO,&mode);
    int readBytes = 1;
    memset(dataServer, 0, sizeof(int)*4);
    memset(dataClient, 0, sizeof(int)*4);
    while(readBytes > 0){
        if(clientOrServer == 0){ //signifying server
            readBytes = recv(s, (char*)dataServer, sizeof(int)*4, 0); //socket blocks if connection is not closed after send()ing
        }
        else if(clientOrServer == 1){ //signifying client
            readBytes = recv(s, (char*)dataClient, sizeof(int)*4, 0); //socket blocks if connection is not closed after send()ing
        }
        if(readBytes == SOCKET_ERROR){
            if(WSAGetLastError() != 10035){ //10035: non-blocking socket would block (ex: recv has no data)
                cout << "Read broke: " << WSAGetLastError() << endl;
                Sleep(100000);
            }
            return 0;
        }
    }
    return 1;
}

int sendData(SOCKET s, int* buf, int len){
    if(socketState(s, 0) != -1){
        while (len > 0){
            int i = send(s, (char*)buf, len, 0);
            if(i == SOCKET_ERROR){
                cout << "Send error: " << WSAGetLastError() << endl;
                Sleep(100000);
                return -1;
            }
            buf += i;
            len -= i;
        }
        return 1;
    }
    cout << "Socket dead" << endl;
    return -1;
}

int socketState(SOCKET s, SOCKET host){
    if(s == 0){ //if the socket does not have a connection
        if(host == 0){
            return 0;
        }
        u_long iMode = 1;
        ioctlsocket(host,FIONBIO,&iMode); //set to non-blocking
        s = acceptConnection(host); //try to accept a connection
        iMode = 0;
        ioctlsocket(host,FIONBIO,&iMode); //set to blocking
        if(s == INVALID_SOCKET){ //if a connection could not be made
            return 0; //return dead socket
        }
        ioctlsocket(s,FIONBIO,&iMode); //set to blocking
        return s; //otherwise, return the socket
    }
    u_long bytesAvailable;
    if(ioctlsocket(s, FIONREAD, &bytesAvailable) == SOCKET_ERROR){ //socket is dead
        cout << WSAGetLastError() << endl;
        return -1;
    }
    if(bytesAvailable > 0){ //data to read
        return 1;
    }
    else{ //no data to read
        return 0;
    }
}
