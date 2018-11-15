#include<iostream>
#include "windows.h"
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>

using namespace std;

sem_t mutex,wrt;
int readcount=0;

void* writer(void *arg)
{
    while(1)
    {
        sem_wait(&wrt);
        cout<<"Writing\n";
        Sleep(500);
        sem_post(&wrt);
    }
}

void* reader(void* arg)
{
    while(1)
    {
        sem_wait(&mutex);
        readcount++;
        if(readcount==1)
            sem_wait(&wrt);
        sem_post(&mutex);
        cout<<"Reading\n";
        Sleep(500);
        sem_wait(&mutex);
        readcount--;
        if(readcount==0)
            sem_post(&wrt);
        sem_post(&mutex);
    }
}

int main()
{
    sem_init(&mutex,0,1);
    sem_init(&wrt,0,4);
    pthread_t r1,r2,w1,w2,w3,w4;
    pthread_create(&r1,NULL,reader,NULL);
    pthread_create(&r2,NULL,reader,NULL);
    pthread_create(&w1,NULL,writer,NULL);
    pthread_create(&w2,NULL,writer,NULL);
    pthread_create(&w3,NULL,writer,NULL);
    pthread_create(&w4,NULL,writer,NULL);
    pthread_join(r1,NULL);
    pthread_join(r2,NULL);
    pthread_join(w1,NULL);
    pthread_join(w2,NULL);
    pthread_join(w3,NULL);
    pthread_join(w4,NULL);
}
