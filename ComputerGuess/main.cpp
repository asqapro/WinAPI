#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
    srand ( time(NULL) );
    int counter = 0;
    while(counter < 100){
        cout << rand() % 2 + 0;
        counter++;
    }
    return 0;
}
