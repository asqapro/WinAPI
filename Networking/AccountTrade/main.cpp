#include <iostream>
#include <winsock2.h>
#include <vector>
#include <pthread.h>

using namespace std;

string alphabet = "abcdefghijklmnopqrstuvwxyz"; //encryption alphabet

string encrypt(string data, int key){ //encrypt the data to be sent
    for(unsigned int iter = 0; iter < data.size(); iter++){ //shift each letter by key amount
        data[iter] = alphabet[alphabet.find(data[iter])+key];
    }
    return data;
}

string decrypt(string data, int key){ //reverse the encryption for your partner's info
    for(unsigned int iter = 0; iter < data.size(); iter++){
        data[iter] = alphabet[alphabet.find(data[iter])-key];
    }
    return data;
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
string part_username = "";
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
    char acReadBuffer[5000];
    string info = "";
    // Read data from client
    int nReadBytes = 1;
    while(nReadBytes != 0){
        nReadBytes = recv(sd, acReadBuffer, 5000, 0);
        if(strlen(acReadBuffer) > 0){
            info = (string)acReadBuffer;
            if(info.find(",") != string::npos){ //"," indicated username/ password info
                part_username = split_string(info, ",")[0];
                part_pass = split_string(info, ",")[1];
            }
            else{
                part_crypt_key = info;
            }
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
    SOCKET ListeningSocket = SetUpListener(IPAddress_own.c_str(), htons(PortNo));
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
    if(!read_sock(sd)){
        cout << "Error receiving your partner's information." << endl;
        return NULL;
    }
    info_recv = true;
    while(!decrypted){ //if the info isn't yet decrypted
        if(!read_sock(sd)){ //read the socket for info
            cout << "Error receiving your partner's information." << endl;
            return NULL;
        }
        part_username = decrypt(part_username, atoi(part_crypt_key.c_str())); //decrypt the username
        part_pass = decrypt(part_pass, atoi(part_crypt_key.c_str())); //and password
        decrypted = true;
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
    string MESSAGE = own_username + "," + own_pass;
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
            cout << "Sending encrypted info." << endl;
            send(s, MESSAGE.c_str(), MESSAGE.length(), 0);
            break;
        }
        Sleep(1);
    }
    while(!info_recv){
        Sleep(1);
    }
    MESSAGE = own_crypt_key;
    send(s, MESSAGE.c_str(), MESSAGE.length(), 0);
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
    cout << "Setting up middleman." << endl;
    cout << "Enter the website of your account: ";
    cin >> site;
    cin.clear();cin.sync();
    cout << "Enter your username: ";
    cin >> own_username;
    cin.clear();cin.sync();
    cout << "Enter your password: ";
    cin >> own_pass;
    cin.clear();cin.sync();

    cout << "Enter your cipher key (to encrypt your data): ";
    cin >> own_crypt_key;
    cin.clear();cin.sync();

    own_username = encrypt(own_username, atoi(own_crypt_key.c_str()));
    own_pass = encrypt(own_pass, atoi(own_crypt_key.c_str()));
    cout << "Data encrypted." << endl;

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
