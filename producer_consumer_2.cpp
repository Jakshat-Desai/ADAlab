#include<iostream>
#include "windows.h"
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
using namespace std;

sem_t mutex,emp,full;
int buff=0;

int insertbuff()
{
    if(buff<5) return buff++;
    else return 34404;
}

int removebuff()
{
    if(buff>0) return buff--;
    else return 34404;
}

void* producer(void *arg)
{
    while(1)
    {
        sem_wait(&emp);
        sem_wait(&mutex);
        cout<<"Producing buffer: "<<insertbuff()<<"\n";;
        Sleep(500);
        sem_post(&mutex);
        sem_post(&full);
    }
}

void* consumer(void* arg)
{
    while(1)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        cout<<"Consuming buffer: "<<removebuff()<<"\n";;
        Sleep(500);
        sem_post(&mutex);
        sem_post(&emp);
    }
}

int main()
{
    sem_init(&mutex,0,1);
    sem_init(&emp,3,4);
    sem_init(&full,0,4);
    pthread_t p1,p2,c1,c2,c3,c4;
    pthread_create(&p1,NULL,producer,NULL);
    pthread_create(&p2,NULL,producer,NULL);
    pthread_create(&c1,NULL,consumer,NULL);
    pthread_create(&c2,NULL,consumer,NULL);
    pthread_create(&c3,NULL,consumer,NULL);
    pthread_create(&c4,NULL,consumer,NULL);
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    pthread_join(c1,NULL);
    pthread_join(c2,NULL);
    pthread_join(c3,NULL);
    pthread_join(c4,NULL);
}
