/***********************************************************************
* CST 352 Operating Systems - Lab 1
* Logan Wright
*
* Code listing from "Advanced Linux Programming," by CodeSourcery LLC  *
* Copyright (C) 2001 by New Riders Publishing                          *
* See COPYRIGHT for license information.                               *
***********************************************************************/

#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 5
#define MAX_PRIME 200

int current = 1;
pthread_mutex_t thread_flag_mutex;

int get_next_candidate()
{
    pthread_mutex_lock (&thread_flag_mutex);
    int result = current++;
    pthread_mutex_unlock (&thread_flag_mutex);
    
    return result;
}

/* Compute successive prime numbers (very inefficiently).  Return the
   Nth prime number.  */
int compute_prime(int numPrime)
{
    int candidate = 2;
    while (1)
    {
        int factor;
        int is_prime = 1;

        /* Test primality by successive division.  */
        for (factor = 2; factor < candidate; ++factor)
        {
            if (candidate % factor == 0)
            {
                is_prime = 0;
                break;
            }
        }

        if (is_prime)
        {
            if (--numPrime == 0)
            {
                return candidate;
            }
        }
        ++candidate;
    }
  
  return 0;
}

/* Threaded function that finds the Nth prime using a shared
   global counter. Return the Nth prime number, where N is
   the value pointed to by *t.  */
void* prime_job(void* t)
{
    long tid = (long) t, candidate = 0, total = 0;
    
    printf("Thread %ld starting...\n", tid);
    
    while ((candidate = get_next_candidate()) <= MAX_PRIME)
    {
        int result = compute_prime(candidate);
        printf("Thread %ld found prime %ld: %d\n", tid, candidate, result);
        ++total;
    }

    pthread_exit((void*) total);
}

int main ()
{
    pthread_mutex_init(&thread_flag_mutex, NULL);
    pthread_t thread[NUM_THREADS];
    long t;

    // Start threads
    for (t = 0; t < NUM_THREADS; t++)
        pthread_create(&thread[t], NULL, prime_job, (void *) t);

    // Join threads
    for (t = 0; t < NUM_THREADS; t++)
    {
        void* numPrimesCalc;
        pthread_join(thread[t], &numPrimesCalc);
        printf("Thread %ld joined, calculated %ld prime numbers\n", t, (long) numPrimesCalc);
    }

    /* Print the largest prime it computed.  */
    
    pthread_exit(NULL);
}
