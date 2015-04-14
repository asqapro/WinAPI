#ifndef CURLFUNCTIONSHEADER_H_INCLUDED
#define CURLFUNCTIONSHEADER_H_INCLUDED

#include "headers.h"

using namespace std;

extern string curlData;

size_t writeCallback(char* buf, size_t size, size_t nmemb);

#endif // CURLFUNCTIONSHEADER_H_INCLUDED
