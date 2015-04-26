/***********************************************************************
* CST 352 Operating Systems - Lab 2 - Solution 1
* Logan Wright
*
* Code listing from "Advanced Linux Programming," by CodeSourcery LLC
* Copyright (C) 2001 by New Riders Publishing
* See COPYRIGHT for license information.
***********************************************************************/

#include <time.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int itemCount;

int produceItem()
{
    return rand();
}

void putItemIntoBuffer(int item)
{
    buffer[itemCount] = item;
}

int removeItemFromBuffer()
{
    return buffer[itemCount - 1];
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
        int item = produceItem();	        // Generate the random number
        while (itemCount == BUFFER_SIZE);   // Spin if buffer is full
        putItemIntoBuffer(item);            // Once buffer has room, add the item to the buffer
        printf("Producer added: %d\n", item);
        itemCount = itemCount + 1;
    }

    pthread_exit(NULL);
}

void* consumer(void* t)
{
    long tid = (long) t;

    while (1)
    {
        while (itemCount == 0);             // Spin if nothing in buffer
        int item = removeItemFromBuffer();  // Once buffer has an item, remove the item from buffer
        printf("Consumer removed: %d\n", item);
        itemCount = itemCount - 1;
        consumeItem(item);
    }

    pthread_exit(NULL);
}

int main()
{
    itemCount = 0;
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

    pthread_exit(NULL);
}