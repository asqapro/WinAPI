#include <iostream>
#include <winsock2.h>
#include <wininet.h>

using namespace std;

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
    cout << "All possible localhost IPs:" << endl;
    for(unsigned int iter = 0; iter < sizeof(phe->h_addr_list); iter++){
        memcpy(&addr, phe->h_addr_list[iter], sizeof(struct in_addr));
        cout << "   Possible IP: " << inet_ntoa(addr) << endl;
    }
    return inet_ntoa(addr);
}

char *MESSAGE;

int main(){
    get_local_address();

    HINTERNET hInternet, hFile;
    DWORD rSize;
    char buffer[32];

    hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    hFile = InternetOpenUrl(hInternet, "http://ipecho.net/plain", NULL, 0, INTERNET_FLAG_RELOAD, 0);
    InternetReadFile(hFile, &buffer, sizeof(buffer), &rSize);
    buffer[rSize] = '\0';

    InternetCloseHandle(hFile);
    InternetCloseHandle(hInternet);

    cout << "Your external IP Address is: " << buffer << "\n";
    system("pause");
    return 0;
}
