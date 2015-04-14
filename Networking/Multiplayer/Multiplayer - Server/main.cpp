#include <iostream>
#include <winsock2.h>
#include <fstream>
#include <vector>

using namespace std;

int player_count;
vector<string> ip_addrs;

string data;

int TCP_PORT = 5721;

bool CloseConnection (SOCKET s)
{
    //Close the socket if it exists
    if(s)
        closesocket(s);

    return true;
}

char* get_local_address(){
    char ac[80];
    gethostname(ac, sizeof(ac));

    struct hostent *phe = gethostbyname(ac);
    if (phe == 0) {
        cerr << "Yow! Bad host lookup." << endl;
        return NULL;
    }

    struct in_addr addr;
    memcpy(&addr, phe->h_addr_list[0], sizeof(struct in_addr));
    return inet_ntoa(addr);
}


SOCKET SetUpListener(const char* pcAddress, int nPort)
{
    u_long nInterfaceAddr = inet_addr(pcAddress);
    if (nInterfaceAddr != INADDR_NONE) {
        SOCKET sd = socket(AF_INET, SOCK_STREAM, 0);
        if (sd != INVALID_SOCKET) {
            sockaddr_in sinInterface;
            sinInterface.sin_family = AF_INET;
            sinInterface.sin_addr.s_addr = nInterfaceAddr;
            sinInterface.sin_port = nPort;
            if (bind(sd, (sockaddr*)&sinInterface,
                    sizeof(sockaddr_in)) != SOCKET_ERROR) {
                listen(sd, 1);
                return sd;
            }
        }
    }

    return INVALID_SOCKET;
}

SOCKET AcceptConnection(SOCKET ListeningSocket, sockaddr_in& sinRemote)
{
    int nAddrSize = sizeof(sinRemote);
    return accept(ListeningSocket, (sockaddr*)&sinRemote, &nAddrSize);
}

SOCKET SetUpListener(const char* pcAddress, int nPort);
SOCKET AcceptConnection(SOCKET ListeningSocket, sockaddr_in& sinRemote);

char acReadBuffer[5000];

bool read_sock(SOCKET sd)
{
    // Read data from client
    int nReadBytes = 1;
    while(nReadBytes != 0){
        nReadBytes = recv(sd, acReadBuffer, 5000, 0);
        if(strlen(acReadBuffer) > 0){
            data = acReadBuffer;
            return true;
        }
        if (nReadBytes == SOCKET_ERROR) {
            return false;
        }
    }
    return false;
}


int server(SOCKADDR_IN* target){
    string local_IP = get_local_address();
    SOCKET listeners[player_count];

    fd_set readfds;
    FD_ZERO(&readfds);
    for(int iter = player_count; iter < player_count; iter++){
        listeners[iter] = SetUpListener(get_local_address(), htons(TCP_PORT));
        if (listeners[iter] == INVALID_SOCKET) {
            cout << "Error with listener: " << WSAGetLastError() << endl;
            return -1;
        }
        // add our descriptors to the set
        FD_SET(listeners[iter], &readfds);
    }
    // since we got s2 second, it's the "greater", so we use that for
    // the n param in select()
    int n = listeners[player_count] + 1;

    // wait until either socket has data ready to be recv()'d (timeout 10 secs)
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 10;
    int rv = select(n, &readfds, NULL, NULL, &tv);
    for(int iter = player_count; iter < player_count; iter++){
        if (rv == -1) {
            perror("select"); // error occurred in select()
            return -2;
        } else if (rv == 0) {
            cout << "None of the players made an attempt to update after 10 seconds" << endl;
            return -3;
        } else {
            // one of the descriptors have data
            if (FD_ISSET(listeners[iter], &readfds)) {
                sockaddr_in sinRemote;
                SOCKET sd = AcceptConnection(listeners[iter], sinRemote);
                if (sd == INVALID_SOCKET) {
                    cout << "Error with accepter: " << WSAGetLastError() << endl;
                    return -4;
                }
                if(read_sock(sd)){
                }
                if(CloseConnection(sd)){}
                else{
                    cout << "Error disconnecting: " << WSAGetLastError() << endl;
                    return -5;
                }
            }
        }
    }
    return 0;
}

int servertwo(){
    bool send_data = false;
    string MESSAGE;
    SOCKET host_me = SetUpListener(get_local_address(), htons(TCP_PORT));
    sockaddr_in sinRemote;
    cout << "Awaiting connection..." << endl;
    SOCKET sd = AcceptConnection(host_me, sinRemote);
    cout << "Client connected" << endl;
    cout << "> ";

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sd, &readfds);

    int n = sd + 1;

    // wait until either socket has data ready to be recv()'d (timeout 10 millisecs)
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 10;
    int rv;
    while(true){
        FD_ZERO(&readfds);
        FD_SET(sd, &readfds);
        rv = select(n, &readfds, NULL, NULL, &tv);
        if(FD_ISSET(sd, &readfds)){
            FD_CLR(sd, &readfds);
            if(read_sock(sd)){
                cout << inet_ntoa(sinRemote.sin_addr) << " said " << data << endl;
            }
        }
        if(getline(cin, MESSAGE)){
            send_data = true;
        }
        if(send_data){
            send_data = false;
            send(sd, MESSAGE.c_str(), (int)(MESSAGE).size(), 0);
            cout << "> ";
        }
        Sleep(10);
    }
    return 0;
}

int main()
{
    WSADATA w;
    int error = WSAStartup (0x0202, &w);   // Fill in WSA info

    if (error)
    {
        return -1; //For some reason we couldn't start Winsock
    }

    if (w.wVersion != 0x0202) //Wrong Winsock version?
    {
        WSACleanup ();
        return -1;
    }

    /*SOCKADDR_IN targets[player_count];

    for(int iter = 0; iter < player_count; iter++){
        SOCKADDR_IN target;
        target.sin_family = AF_INET; // address family Internet
        target.sin_port = htons(TCP_PORT); //Port to connect on
        target.sin_addr.s_addr = inet_addr(ip_addrs.at(iter).c_str()); //Target IP
        targets[iter] = target;
    }*/
    //server(targets);
    servertwo();
    WSACleanup(); //Clean up Winsock
    return 0;
}
