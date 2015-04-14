#include <iostream>
#include <time.h>
#include <pthread.h>

using namespace std;

float timeslice = 0.01;
clock_t start;
float duration;

int noThreads[50];
int threads[50];

clock_t noThreadTime;
clock_t threadTime;
clock_t noThreadStart;
clock_t threadStart;

int noThreadsDone = 0;
int threadsDone = 0;

int noThreadCount(int index){
    start = clock();
    for(int iter = noThreads[index]; iter < 1000000; iter++){ //loop from 0 to 1000000-1
        duration = (clock() - start ); //get how long the current function has been running
        cout << duration << endl;
        noThreads[index] = iter; //set the new value to what it counted to
        if(duration > timeslice){ //if it has been running longer than allowed
            return 0; //exit the function
        }
    }
    return 1;
}

void* threadCount(void* index_p){
    int index = (int)index_p;
    for(int iter = threads[index]; iter < 1000000; iter++){ //loop from 0 to 1000000-1
        threads[index] = iter; //set the new value to what it counted to
    }
    threadsDone++;
    return NULL;
}

int main()
{
    for(int i = 0; i < 50; i++){ //loop through noThreads
        noThreads[i] = 0; //set each value to 0 as initial value
    }
    int index = 0;
    noThreadStart = clock();
    while(!noThreadCount(index)){
        index++;
        if(index == 50){
            index = 0;
        }
    }
    noThreadTime = (clock()-noThreadStart);

    threadStart = clock();
    pthread_t threadList[50];
    for(int i = 0; i < 50; i++){ //loop through noThreads
        threads[i] = 0; //set each value to 0 as initial value
        pthread_create(&threadList[i], NULL, &threadCount, (void*)i);
    }
    while(threadsDone < 48){
        continue;
    }
    threadTime = (clock()-threadStart);

    cout << "no threads: " << noThreadTime << endl;
    cout << "threads: " << threadTime << endl;
    return 0;
}
