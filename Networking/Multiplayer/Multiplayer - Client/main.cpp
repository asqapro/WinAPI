#include <iostream>
#include <winsock2.h>
#include <fstream>

using namespace std;

string data;

int TCP_PORT = 5721;

bool CloseConnection (SOCKET s)
{
    //Close the socket if it exists
    if(s)
        closesocket(s);

    return true;
}

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

int client(){
    string IPAddress;
    cout << "Enter the IP address of the server: ";
    cin >> IPAddress;
    cin.clear(); cin.sync();
    //Fill out the information needed to initialize a socket…
    SOCKADDR_IN target; //Socket address information

    target.sin_family = AF_INET; // address family Internet
    target.sin_port = htons(TCP_PORT); //Port to connect on
    target.sin_addr.s_addr = inet_addr(IPAddress.c_str()); //Target IP

    SOCKET s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
    if (s == INVALID_SOCKET)
    {
        return -1; //Couldn't create the socket
    }

    //Try connecting...

    if (connect(s, (SOCKADDR *)&target, sizeof(target)) == SOCKET_ERROR){
        return -1; //Couldn't connect
    }
    else{
        cout << "> ";
        string MESSAGE;
        bool send_data = false;
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(s, &readfds);

        int n = s + 1;

        // wait until either socket has data ready to be recv()'d (timeout 10 millisecs)
        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 10;
        int rv;
        while(true){
            FD_ZERO(&readfds);
            FD_SET(s, &readfds);
            rv = select(n, &readfds, NULL, NULL, &tv);
            if(FD_ISSET(s, &readfds)){
                FD_CLR(s, &readfds);
                if(read_sock(s)){
                    cout << IPAddress << " said " << data << endl;
                }
            }
            if(getline(cin, MESSAGE)){
                send_data = true;
            }
            if(send_data){
                send_data = false;
                send(s, MESSAGE.c_str(), (int)(MESSAGE).size(), 0);
                cout << "> ";
            }
        }
        return 0;
    }
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
    client();
    return 0;
}
