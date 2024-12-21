#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int ledger;
pthread_mutex_t lock;

void *update_ledger()
{
    pthread_mutex_lock(&lock);
    ledger++;
    printf ("%d\n", ledger);
    pthread_mutex_unlock(&lock);
}

int main ()
{    
    pthread_t   servers[1000];

    pthread_mutex_init(&lock, NULL);
    int i = 0;
    while (i < 1000)
    {
        pthread_create(servers + i, NULL, update_ledger, NULL);
        i++;
    }
    i = 0;
    while (i < 1000)
    {
        pthread_join(servers[i], NULL);
        i++;
    }
}