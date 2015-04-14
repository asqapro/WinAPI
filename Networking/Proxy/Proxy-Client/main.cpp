#include <iostream>
#include <winsock.h>
#include <fstream>

using namespace std;

WSADATA wsadata;

bool init(){
    int error = WSAStartup(0x0202, &wsadata);

    if(error){
        return false;
    }
    if(wsadata.wVersion != 0x0202)
    {
        WSACleanup(); //Clean up Winsock
        return false;
    }
    return true;
}

string MESSAGE;

string file_piece;
ofstream file_full;

int TCP_PORT = 5721;
string TCP_IP;

bool CloseConnection (SOCKET s)
{
    //Close the socket if it exists
    if(s)
        closesocket(s);

    return true;
}

char acReadBuffer[5000];
bool exit_server_1;
bool exit_server_2;
bool password_entered = false;
int password_try_count = 3;
bool request_done = false;

int read_sock(SOCKET sd)
{
    // Read data from client
    int nReadBytes = 1;
    while(nReadBytes != 0){
        memset(acReadBuffer,0,5000);
        nReadBytes = recv(sd, acReadBuffer, 5000, 0);
        if(nReadBytes == SOCKET_ERROR){
            return -1;
        }
        if((string)acReadBuffer == "got"){
            cout << "Access granted." << endl;
            password_entered = true;
            return 1;
        }
        else if((string)acReadBuffer == "password"){
            password_entered = false;
            cout << "Password incorrect." << endl;
            cout << "You have " << password_try_count << " attempts left." << endl;
            password_try_count--;
            if(password_try_count <= 0){
                return 0;
            }
            return -2;
        }
        else if((string)acReadBuffer == "none"){
                return -4;
        }
        else if(strlen(acReadBuffer) > 0){
            file_piece += acReadBuffer;
            return 2;
        }
        else{
            return 3;
        }
    }
    return -3;
}

string url_request;

int handshake(const char* IPAddress, int PortNo){
    //Fill out the information needed to initialize a socket…
    SOCKADDR_IN target; //Socket address information

    target.sin_family = AF_INET; // address family Internet
    target.sin_port = htons (PortNo); //Port to connect on
    target.sin_addr.s_addr = inet_addr (IPAddress); //Target IP

    SOCKET s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
    if (s == INVALID_SOCKET)
    {
        return -1; //Couldn't create the socket
    }

    //Try connecting...

    if (connect(s, (SOCKADDR *)&target, sizeof(target)) == SOCKET_ERROR)
    {
        return -1; //Couldn't connect
    }
    else
        send(s, MESSAGE.c_str(), MESSAGE.length(), 0);
    while(true){
        int ret_code = read_sock(s);
        if(ret_code == -4){ //no data recieved from server
            cout << "No data recieved from " << url_request << "." << endl;
            return -1;
        }
        if(ret_code == -3){ //no data recieved from socket
            continue;
        }
        if(ret_code == -1){ //error with the socket
            return -1;
        }
        else if(ret_code == 0){ //password incorrect, no attempts left, kill server
            cout << "Server shutting down." << endl;
            MESSAGE = "kill";
            send(s, MESSAGE.c_str(), MESSAGE.length(), 0);
            exit(-1);
        }
        else if(ret_code == 1){ //password entered, grant access
            break;
        }
        else if(ret_code == -2){ //wrong password, but x amount of attempts left
            if(CloseConnection(s)){
            }
            else{
                cout << "Error disconnecting" << endl;
                cout << WSAGetLastError();
                return -1;
            }
            return 0;
        }
        else if(ret_code == 2){ //recieving file, keep reading
            continue;
        }
        else if(ret_code == 3){ //done recieving file
            request_done = true;
            cout << file_piece.length() << endl;
            cout << file_piece.size() << endl;
            file_full.open("Requested.html", ios::binary);
            file_full << file_piece;
            file_full.close();

            if(CloseConnection(s)){
                return 1;
            }
            else{
                cout << "Error disconnecting" << endl;
                cout << WSAGetLastError();
                return -1;
            }
            break;
        }
    }
    if(CloseConnection(s)){
        return 1;
    }
    else{
        cout << "Error disconnecting" << endl;
        cout << WSAGetLastError();
        return -1;
    }
}

string password;

void client(){
    cout << "Setting up client." << endl;
    cout << "IP of server? ";
    cin >> TCP_IP;
    while(true){
        if(!password_entered){
            cout << "Enter password: ";
            cin >> password;
            MESSAGE = password;
            int handshake_ret_code = handshake(TCP_IP.c_str(), TCP_PORT);
            if(handshake_ret_code == -1){
                cout << "Error occurred, restarting client." << endl;
                return;
            }
            else if(handshake_ret_code == 0){
                continue;
            }
        }
        else{
            cout << "URL: ";
            cin >> url_request;
            if(url_request.find("www.") == string::npos){
                url_request = "www." + url_request;
            }
            if(url_request.find(".com") == string::npos
                && url_request.find(".org") == string::npos
                && url_request.find(".gov") == string::npos
                && url_request.find(".net") == string::npos){
                    string response;
                    cout << "Either you skipped the domain suffix, or you entered one not recognized. Do you wish to add the typical .com suffix? (y/n) ";
                    cin >> response;
                    if(response == "y" || response == "Y" || response == "yes" || response == "Yes" || response == "YES"){
                        url_request += ".com";
                        cout << url_request << endl;
                    }
            }
            MESSAGE = url_request;
            int handshake_ret_code = handshake(TCP_IP.c_str(), TCP_PORT);
            if(handshake_ret_code == -1){
                cout << "Error occurred, restarting client.";
                for(int iter = 0; iter < 10; iter++){
                    cout << ".";
                    Sleep(1000);
                }
                return;
            }
        }
        if(request_done){
            cout << "Requested URL \'" << url_request << "\' fetched." << endl;
            cout << "You will find the HTML file to your URL in your current directory." << endl;
            cout << "Resetting client.";
            for(int iter = 0; iter < 10; iter++){
                cout << ".";
                Sleep(1000);
            }
            break;
        }
    }
}

int main()
{
    if(!init()){
        cout << "Something went wrong. Please restart the program." << endl;
        return 0;
    }
    while(true){
        client();
        exit_server_1 = false;
        exit_server_2 = false;
        password_entered = false;
        request_done = false;
        system("cls");
    }
    WSACleanup(); //Clean up Winsock
    return 0;
}
