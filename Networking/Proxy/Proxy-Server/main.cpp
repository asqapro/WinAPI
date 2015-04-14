#include <iostream>
#include <winsock.h>
#include <fstream>
#include <sstream>

using namespace std;

WSADATA wsadata;

string password;
bool pass_recieved = false;

string MESSAGE;

int TCP_PORT = 5721;
char* TCP_IP;

string domain_suffixes[500];

bool CloseConnection (SOCKET s)
{
    //Close the socket if it exists
    if(s){
        closesocket(s);
        return true;
    }
    return false;
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
string url_request;
bool get_url_request = false;
bool url_request_recieved = false;

bool read_sock(SOCKET sd)
{
    // Read data from client
    int nReadBytes = 1;
    while(nReadBytes != 0){
        nReadBytes = recv(sd, acReadBuffer, 5000, 0);
        if((string)acReadBuffer == password){
            pass_recieved = true;
            return true;
        }
        if(strlen(acReadBuffer) > 0 && (string)acReadBuffer != "kill" && get_url_request){
            url_request = (string)acReadBuffer;
            url_request_recieved = true;
            return true;
        }
        else if((string)acReadBuffer == "kill"){
            exit(-1);
        }
        else if((string)acReadBuffer != password){
            return true;
        }
        if (nReadBytes == SOCKET_ERROR) {
            return false;
        }
    }
    return false;
}

void set_char_string(string str){
    const char* str_char = str.c_str();
    for(unsigned int iter = 0; iter < strlen(str_char); iter++){
        MESSAGE[iter] = str_char[iter];
    }
}

bool complete_send(SOCKET sd, char* data, int len){
    int curr_send = 0;
    int total = 0;
    int bytes_left = strlen(data);
    while(total < len){
        curr_send = send(sd, data + total, bytes_left, 0);
        if (curr_send == -1){
            return false;
        }
        total += curr_send;
        bytes_left -= curr_send;
    }
    return true;
}

void web_scrape(SOCKET sd, string MESSAGE){
    struct hostent *host;
	host = gethostbyname(url_request.c_str()); //url_request is a global variable, the client sends it in

    SOCKADDR_IN site; //Socket address information

    site.sin_family = AF_INET; // address family Internet
    site.sin_port = htons (80); //Port to connect on
    site.sin_addr.s_addr = *((unsigned long*)host->h_addr);

    SOCKET s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
    if (s == INVALID_SOCKET){
        return; //Couldn't create the socket
    }

    //Try connecting...

    if (connect(s, (SOCKADDR *)&site, sizeof(site)) == SOCKET_ERROR){
        return; //Couldn't connect
    }
    else{
        stringstream ss;
        ss << "GET / HTTP/1.1\r\n"
           << "Host:" + url_request + "\r\n"
           << "User-Agent:Custom-Client\r\n"
           << "Connection:close\r\n" //otherwise, connection will stay alive, never stop recv'ing data
           << "\r\n";
        string request = ss.str();
        char request_char[request.length()];
        memcpy(request_char, request.c_str(), request.size());
        /*int curr_send = 0;
        int total = 0;
        int bytes_left = request.length();
        while(total < request.length()){
            curr_send = send(sd, request_char + total, bytes_left, 0);
            total += curr_send;
            bytes_left -= curr_send;
        }*/
        complete_send(s, request_char, request.length());
    }

    char buffer[1024];
    string buf_str;
    while(recv(s, buffer, 1024, 0) > 0){
        buf_str += buffer;
    }
    CloseConnection(s);

    if(buf_str.length() <= 0){
        MESSAGE = "none"; //sends a response back to the client saying nothing was received
        send(sd, MESSAGE.c_str(), (int)(MESSAGE).size(), 0);
        return;
    }
    int cont_len_start = buf_str.find("Content-Length") + 16;
    int cont_len_end = buf_str.find(" ", cont_len_start + 1);
    int len = cont_len_end - cont_len_start;
    int content_length = atoi(buf_str.substr(cont_len_start, len).c_str());
    cout << content_length << endl;
    size_t strip = buf_str.find("\r\n\r\n") + 4;
    cout << buf_str.substr(0, strip) << endl;
    buf_str = buf_str.substr(strip);

    char buf_str_char[buf_str.length()];
    memcpy(buf_str_char, buf_str.c_str(), buf_str.size());
    int curr_send = 0;
    int total = 0;
    int bytes_left = buf_str.size();
    while(total < content_length){
        curr_send = send(sd, buf_str_char + total, bytes_left, 0);
        total += curr_send;
        bytes_left -= curr_send;
    }
}

WSADATA w;

bool exit_server;

int handshake()
{
    string TCP_IP_str = get_local_address();
    int TCP_PORT_OWN = 5721;

    SOCKET ListeningSocket = SetUpListener(TCP_IP_str.c_str(), htons(TCP_PORT_OWN));
    if (ListeningSocket == INVALID_SOCKET) {
        cout << "Error with listener" << endl;
        cout << WSAGetLastError() << endl;
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
            TCP_IP = inet_ntoa(sinRemote.sin_addr);
        }
        else {
            cout << "Error with accepter" << endl;
            cout << WSAGetLastError() << endl;
            return -1;
        }
        if(read_sock(sd)){
            if(pass_recieved && !get_url_request){
                MESSAGE = "got";
                send(sd, MESSAGE.c_str(), (int)(MESSAGE).size(), 0);
                get_url_request = true;
            }
            else if(get_url_request){
                if(url_request_recieved){
                    web_scrape(sd, url_request);
                    exit_server = true;
                }
            }
            else{
                MESSAGE = "password";
                send(sd, MESSAGE.c_str(), (int)(MESSAGE).size(), 0);
            }
        }
        if(CloseConnection(sd)){
        }
        else{
            cout << "Error disconnecting" << endl;
            return -1;
        }
        if(exit_server){
            break;
        }
        Sleep(500);
    }
    if(CloseConnection(ListeningSocket)){}
    else{
        cout << "Error disconnecting" << endl;
        return -1;
    }
    return 0;
}

void server(){
    cout << "Set a password: ";
    cin >> password;
    cout << "Setting up server." << endl;
    while(true){
        if(handshake() == -1){
            cout << "Error occured. Restarting server." << endl;
            return;
        }
        pass_recieved = false;
        get_url_request = false;
        url_request_recieved = false;
        exit_server = false;
    }
}

int main(int argc, char* argv[])
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

    while(true){
        server();
    }
    Sleep(10000);
    return 0;
}
