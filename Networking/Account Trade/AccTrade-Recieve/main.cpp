#include <iostream>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include <time.h>


using namespace std;

WSADATA w;

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

char* get_local_address(){
    WSADATA wsadata;

    int error = WSAStartup(0x0202, &wsadata);


    if(error){
        return NULL;
    }
    if(wsadata.wVersion != 0x0202)
    {
        WSACleanup(); //Clean up Winsock
        return NULL;
    }

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

bool CloseConnection (SOCKET s)
{
    //Close the socket if it exists
    if(s)
        closesocket(s);

    WSACleanup(); //Clean up Winsock
    return true;
}

char acReadBuffer[5000];
string user_pass;

bool release_info = false;
bool got_info = false;

bool read_sock(SOCKET sd)
{
    // Read data from client
    int nReadBytes = 1;
    while(nReadBytes != 0){
        nReadBytes = recv(sd, acReadBuffer, 5000, 0);
        if((string)acReadBuffer != "ok" && strlen(acReadBuffer) > 0){
            user_pass = (string)acReadBuffer;
            got_info = true;
            return true;
        }
        if((string)acReadBuffer == "ok"){
            release_info = true;
            return true;
        }
        if (nReadBytes == SOCKET_ERROR) {
            return false;
        }
    }
    return false;
}

char *MESSAGE;

SOCKET s; //Socket handle

//CONNECTTOHOST – Connects to a remote host
bool ConnectToHost(int PortNo, char* IPAddress)
{
    //Start up Winsock…
    WSADATA wsadata;

    int error = WSAStartup(0x0202, &wsadata);

    //Did something happen?
    if (error)
        return false;

    //Did we get the right Winsock version?
    if(wsadata.wVersion != 0x0202)
    {
        WSACleanup(); //Clean up Winsock
        return false;
    }


    //Fill out the information needed to initialize a socket…
    SOCKADDR_IN target; //Socket address information

    target.sin_family = AF_INET; // address family Internet
    target.sin_port = htons (PortNo); //Port to connect on
    target.sin_addr.s_addr = inet_addr (IPAddress); //Target IP

    s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
    if (s == INVALID_SOCKET)
    {
        return false; //Couldn't create the socket
    }

    //Try connecting...

    if (connect(s, (SOCKADDR *)&target, sizeof(target)) == SOCKET_ERROR)
    {
        return false; //Couldn't connect
    }
    else
        send(s, MESSAGE, (int)strlen(MESSAGE), 0);
        return true; //Success
}

int handshake()
{
    char* TCP_IP_OWN = get_local_address();
    int TCP_PORT_OWN = 5721;
    cout << "Tell your trading partner this IP: " << TCP_IP_OWN << endl;
    cout << "Tell your trading partner this port #: " << TCP_PORT_OWN << endl;
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

    SOCKET ListeningSocket = SetUpListener(TCP_IP_OWN, htons(TCP_PORT_OWN));
    if (ListeningSocket == INVALID_SOCKET) {
        cout << "Error with listener" << endl;
        return -1;
    }

    // Spin forever handling clients
    while (1) {
        // Wait for a connection, and accepting it when one arrives.
        cout << "Waiting for a connection..." << flush;
        sockaddr_in sinRemote;
        SOCKET sd = AcceptConnection(ListeningSocket, sinRemote);
        if (sd != INVALID_SOCKET) {
            cout << "Accepted connection from " <<
                    inet_ntoa(sinRemote.sin_addr) << ":" <<
                    ntohs(sinRemote.sin_port) << "." << endl;
        }
        else {
            cout << "Error with accepter" << endl;
            return -1;
        }
        if(read_sock(sd)){
            /*if(!message_sent){
                MESSAGE = (char*)"ok";
                send_spec_shake(inet_ntoa(sinRemote.sin_addr), sinRemote.sin_port);
                message_sent = true;
            }*/
            if(release_info && got_info){
                return 1;
            }
        }
        if(CloseConnection(sd)){}
        else{
            cout << "Error disconnecting" << endl;
            return -1;
        }
    }
    CloseConnection(ListeningSocket);
    return 0;
}

int main()
{
    cout << "Recieving data." << endl;
    srand(time(NULL));
    if(handshake() == -1){
        cout << "Error occured." << endl;
    }
    if(release_info){
        cout << user_pass << endl;
    }
    else{
        cout << "An error occured with the transaction" << endl;
    }
    cout << "Press ESC to exit." << endl;
    while(true){
        if((GetKeyState(VK_ESCAPE) & 0x80)){
            break;
        }
    }
    return 0;
}


