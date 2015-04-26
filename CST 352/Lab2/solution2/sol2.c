/***********************************************************************
* CST 352 Operating Systems - Lab 2 - Solution 2
* Logan Wright
*
* Code listing from "Advanced Linux Programming," by CodeSourcery LLC
* Copyright (C) 2001 by New Riders Publishing
* See COPYRIGHT for license information.
***********************************************************************/

#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
sem_t emptyCount;
sem_t fillCount;

int produceItem()
{
    return rand();
}

void putItemIntoBuffer(int item)
{
    int pos;
    sem_getvalue(&fillCount, &pos);
    buffer[pos] = item;
}

int removeItemFromBuffer()
{
    int pos;
    sem_getvalue(&fillCount, &pos);
    return buffer[pos];
}

void consumeItem(int item)
{
    // Do nothing with item
}

void* producer(void* t)
{
    long tid = (long) t;

    while (1)
    {
        int item = produceItem();	            // Generate the random number
        sem_wait(&emptyCount);			        // Checks if OK to enter critical area
        putItemIntoBuffer(item);                // Once buffer has room, add the item to the buffer
        sem_post(&fillCount);					// Notify left critical
        printf("Producer added: %d\n", item);
    }

    pthread_exit(NULL);
}

void* consumer(void* t)
{
    long tid = (long) t;

    while (1)
    {
        sem_wait(&fillCount);			    // Checks if OK to enter critical area
        int item = removeItemFromBuffer();  // Once buffer has an item, remove the item from buffer
        sem_post(&emptyCount);				// Notify left critical
        consumeItem(item);
        printf("Consumer removed: %d\n", item);
    }

    pthread_exit(NULL);
}

int main()
{
    // Initialize semaphores
    sem_init(&emptyCount, 0, BUFFER_SIZE);
    sem_init(&fillCount, 0, 0);
    
    srand(time(NULL)); // seed generator

    int i;
    for (i = 0; i < BUFFER_SIZE; ++i)
    {
        buffer[i] = 0;
    }

    long tid_prod = 0, tid_cons = 1;
    
    // Spawn producer thread
    pthread_t prod_thread;
    pthread_create(&prod_thread, NULL, producer, (void*)tid_prod);

    // Spawn consumer thread
    pthread_t cons_thread;
    pthread_create(&cons_thread, NULL, consumer, (void*)tid_cons);
    
    // Join threads
    void* result;
    pthread_join(prod_thread, &result);
    pthread_join(cons_thread, &result);
    
    sem_destroy(&emptyCount);
    sem_destroy(&fillCount);

    pthread_exit(NULL);
}