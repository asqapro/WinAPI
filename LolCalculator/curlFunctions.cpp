#include "curlFunctionsHeader.h"

using namespace std;

string curlData;

size_t writeCallback(char* buf, size_t size, size_t nmemb)
{
    //buf is a pointer to the data that curl has for us
    //size*nmemb is the size of the buffer

    for (unsigned int c = 0; c < size*nmemb; c++)
    {
        curlData.push_back(buf[c]);
    }
    return size*nmemb; //tell curl how many bytes we handled
}
