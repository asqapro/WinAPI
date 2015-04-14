#define WINVER 0x0500
#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <vector>
#include <pthread.h>

using namespace std;

void GenerateKey(int vk, BOOL bExtended) { //for sending the Q-Q

    KEYBDINPUT  kb = {0};
    INPUT       Input = {0};

    /* Generate a "key down" */
    if (bExtended) { kb.dwFlags  = KEYEVENTF_EXTENDEDKEY; }
    kb.wVk  = vk;
    Input.type  = INPUT_KEYBOARD;
    Input.ki  = kb;
    SendInput(1, &Input, sizeof(Input));

    /* Generate a "key up" */
    ZeroMemory(&kb, sizeof(KEYBDINPUT));
    ZeroMemory(&Input, sizeof(INPUT));
    kb.dwFlags  =  KEYEVENTF_KEYUP;
    if (bExtended) { kb.dwFlags |= KEYEVENTF_EXTENDEDKEY; }
    kb.wVk = vk;
    Input.type = INPUT_KEYBOARD;
    Input.ki = kb;
    SendInput(1, &Input, sizeof(Input));
}

string own_crypt_key;
string part_crypt_key;
bool decrypted = false;

string IPAddress_part = "";
string IPAddress_own = "";
int PortNo = 9955;
string site = "";
string own_username = "";
string own_pass = "";
int data = 0;
string part_pass = "";
bool info_recv = false;

WSADATA w;

bool CloseConnection (SOCKET s)
{
    //Close the socket if it exists
    if(s)
        closesocket(s);

    WSACleanup(); //Clean up Winsock
    return true;
}

char* get_local_address(){ //not used right now, but I find it handy to have around
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

vector<string> split_string(string split_this, string token){ //splits a string based on a token
    size_t pos = split_this.find(token);
    if(pos != string::npos){
        return vector<string>{split_this.substr(0, pos), split_this.substr(pos+1)};;
    }
    else{
        return vector<string>{"Error"};
    }
}

bool read_sock(SOCKET sd) //get data from the socket
{
    int acReadBuffer[1];
    int exmp[1];
    exmp[0] = VK_OEM_3;
    // Read data from client
    int nReadBytes = 1;
    while(nReadBytes != 0){
        nReadBytes = recv(sd, (char*)acReadBuffer, sizeof(exmp), 0);
        if(sizeof(acReadBuffer) > 0){
            data = acReadBuffer[0];
            return true;
        }
        else if (nReadBytes == SOCKET_ERROR) {
            cout << "Error reading information" << endl;
            cout << "Error code: " << WSAGetLastError() << endl;
            return false;
        }
    }
    cout << "No information received." << endl;
    return false;
}

SOCKET SetUpListener(const char* pcAddress, int nPort) //sets up the listner socket
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

SOCKET AcceptConnection(SOCKET ListeningSocket, sockaddr_in& sinRemote) //accepts a connection
{
    int nAddrSize = sizeof(sinRemote);
    return accept(ListeningSocket, (sockaddr*)&sinRemote, &nAddrSize);
}

bool listening = false;

void* handshake_receive(void* ignore){ //partner connecting to you
    SOCKET ListeningSocket = SetUpListener(INADDR_ANY, htons(PortNo));
    if (ListeningSocket == INVALID_SOCKET) {
        cout << "Error with setting up listener socket." << endl;
        cout << "Error code: " << WSAGetLastError() << endl;
        return NULL;
    }
    // Wait for a connection, and accepting it when one arrives.
    cout << "Waiting for a connection..." << endl;
    listening = true;
    sockaddr_in sinRemote;
    SOCKET sd = AcceptConnection(ListeningSocket, sinRemote);
    if (sd != INVALID_SOCKET) {
        cout << "Partner connected." << endl;
    }
    else {
        cout << "Error with partner connecting." << endl;
        cout << "Error code: " << WSAGetLastError() << endl;
        return NULL;
    }
    while(true){
        if(!read_sock(sd)){
            cout << "Error receiving your partner's information." << endl;
            return NULL;
        }
        if(data == VK_OEM_3){
            GenerateKey(VK_SPACE, false);
        }
    }
    if(!CloseConnection(sd)){ //try to close the connection
        cout << "Error closing connecting." << endl;
        cout << "Error code: " << WSAGetLastError() << endl;
        return NULL;
    }
    if(!CloseConnection(ListeningSocket)){ //shut down the listening socket
        cout << "Error turning listening socket off." << endl;
        cout << "Error code: " << WSAGetLastError() << endl;
        return NULL;
    }
    return 0;
}

void* handshake_send(void* ignore){ //you connecting to partner
    //Fill out the information needed to initialize a socket…
    SOCKADDR_IN target; //Socket address information

    target.sin_family = AF_INET; // address family Internet
    target.sin_port = htons (PortNo); //Port to connect on
    target.sin_addr.s_addr = inet_addr (IPAddress_part.c_str()); //Target IP

    SOCKET s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
    if (s == INVALID_SOCKET)
    {
        cout << "Connection socket could not be created." << endl;
        cout << "Error code: " << WSAGetLastError() << endl;
        return NULL; //Couldn't create the socket
    }

    //Try connecting...

    cout << "Connecting to partner..." << endl;

    while(true){
        if (connect(s, (SOCKADDR *)&target, sizeof(target)) != SOCKET_ERROR){
            cout << "Connected." << endl;
            int send_key[1];
            send_key[1] = VK_OEM_3;
            while(true){
                if((GetKeyState(VK_OEM_3) & 0x80) != 0){
                    send(s, (char*)send_key, sizeof(send_key), 0);
                }
            }
            break;
        }
        Sleep(1);
    }
    if(CloseConnection(s)){
        cout << "Connection with partner successfully terminated." << endl;
        return NULL;
    }
    else{
        cout << "Error disconnecting." << endl;
        cout << "Error code: " << WSAGetLastError() << endl;
        return NULL;
    }
}


int main(){
    cout << "Enter your IP Address: ";
    cin >> IPAddress_own;
    cin.clear();cin.sync();
    cout << "Enter your partner's IP Address: ";
    cin >> IPAddress_part;
    cin.clear();cin.sync();
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
    //cout << "Setting up middleman." << endl;
    //cout << "Enter the website of your account: ";
    //cin >> site;
    //cin.clear();cin.sync();
    //cout << "Enter your username: ";
    //cin >> own_username;
    //cin.clear();cin.sync();
    //cout << "Enter your password: ";
    //cin >> own_pass;
    //cin.clear();cin.sync();

    //cout << "Enter your cipher key (to encrypt your data): ";
    //cin >> own_crypt_key;
    //cin.clear();cin.sync();

    //own_username = encrypt(own_username, atoi(own_crypt_key.c_str()));
    //own_pass = encrypt(own_pass, atoi(own_crypt_key.c_str()));
    //cout << "Data encrypted." << endl;

    pthread_t receive_thread;
    pthread_t send_thread;
    pthread_create(&receive_thread, NULL, &handshake_receive, NULL);
    while(listening == false){
        Sleep(1);
    }
    pthread_create(&send_thread, NULL, &handshake_send, NULL);
    while(true){
        Sleep(1);
    }
    return 0;
}
