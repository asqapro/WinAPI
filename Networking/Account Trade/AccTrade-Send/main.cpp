#include <iostream>
#include <winsock2.h>
#include <vector>

using namespace std;

string IPAddress = "";
int PortNo = 9955;
string site = "";
string username = "";
string pass = "";

WSADATA w;

bool CloseConnection (SOCKET s)
{
    //Close the socket if it exists
    if(s)
        closesocket(s);

    WSACleanup(); //Clean up Winsock
    return true;
}

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

vector<string> split_string(string split_this, string token){
    size_t pos = split_this.find(token);
    if(pos != string::npos){

        return vector<string>{split_this.substr(0, pos), split_this.substr(pos+1)};;
    }
    else{
        return vector<string>{"Error"};
    }
}

bool read_sock(SOCKET sd)
{
    char acReadBuffer[5000];
    string info = "";
    // Read data from client
    int nReadBytes = 1;
    while(nReadBytes != 0){
        nReadBytes = recv(sd, acReadBuffer, 5000, 0);
        if(strlen(acReadBuffer) > 0){
            info = (string)acReadBuffer;
            username = split_string(info, ",")[0];
            pass = split_string(info, ",")[1];
            return true;
        }
        else if (nReadBytes == SOCKET_ERROR) {
            return false;
        }
    }
    return false;
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

int handshake_receive(){
    SOCKET ListeningSocket = SetUpListener(IPAddress.c_str(), htons(PortNo));
    if (ListeningSocket == INVALID_SOCKET) {
        cout << "Error with listener" << endl;
        cout << WSAGetLastError() << endl;
        return -1;
    }
    // Wait for a connection, and accepting it when one arrives.
    cout << "Waiting for a connection..." << flush;
    sockaddr_in sinRemote;
    SOCKET sd = AcceptConnection(ListeningSocket, sinRemote);
    if (sd != INVALID_SOCKET) {
        //cout << "Accepted connection from " <<
        //        inet_ntoa(sinRemote.sin_addr) << ":" <<
        //        ntohs(sinRemote.sin_port) << "." << endl;
        //IPAddress = inet_ntoa(sinRemote.sin_addr);
        cout << "Partner connected." << endl;
    }
    else {
        cout << "Error with partner connecting." << endl;
        cout << WSAGetLastError() << endl;
        return -1;
    }
    if(!read_sock(sd)){
        cout << "Error receiving your partner's information." << endl;
        return -1;
    }
    if(!CloseConnection(sd)){
        cout << "Error closing connecting." << endl;
        return -1;
    }
    if(!CloseConnection(ListeningSocket)){
        cout << "Error turning listening socket off." << endl;
        return -1;
    }
    return 0;
}

int handshake_send(){
    string MESSAGE = username + "," + pass;
    //Fill out the information needed to initialize a socket…
    SOCKADDR_IN target; //Socket address information

    target.sin_family = AF_INET; // address family Internet
    target.sin_port = htons (PortNo); //Port to connect on
    target.sin_addr.s_addr = inet_addr (IPAddress.c_str()); //Target IP

    SOCKET s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
    if (s == INVALID_SOCKET)
    {
        return -1; //Couldn't create the socket
    }

    //Try connecting...

    cout << "Connecting to partner." << endl;

    if (connect(s, (SOCKADDR *)&target, sizeof(target)) == SOCKET_ERROR)
    {
        cout << "Couldn't connect to partner." << endl;
        return -1; //Couldn't connect
    }
    else
        cout << "Sending info." << endl;
        send(s, MESSAGE.c_str(), MESSAGE.length(), 0);
    if(CloseConnection(s)){
        return 1;
    }
    else{
        cout << "Error disconnecting" << endl;
        cout << WSAGetLastError();
        return -1;
    }
}


int main(){
    int error = WSAStartup(0x0202, &w);

    //Did something happen?
    if (error)
        return false;

    //Did we get the right Winsock version?
    if(w.wVersion != 0x0202)
    {
        WSACleanup(); //Clean up Winsock
        return false;
    }
    cout << "Setting up middleman." << endl;
    cout << "Enter the website of your account: ";
    cin >> site;
    cin.clear();cin.sync();
    cout << "Enter your username: ";
    cin >> username;
    cin.clear();cin.sync();
    cout << "Enter your password: ";
    cin >> pass;
    cin.clear();cin.sync();
    handshake_send();
    return 0;
}
