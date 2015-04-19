/***********************************************************************
* Code listing from "Advanced Linux Programming," by CodeSourcery LLC  *
* Copyright (C) 2001 by New Riders Publishing                          *
* See COPYRIGHT for license information.                               *
***********************************************************************/

#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 5
#define MAX_PRIME 100

int current = 1; // Start at first prime
pthread_mutex_t thread_flag_mutex;

int get_next_candidate()
{
    pthread_mutex_lock (&thread_flag_mutex);
    int result = current++;
    pthread_mutex_unlock (&thread_flag_mutex);
    
    return result;
}

/* Compute successive prime numbers (very inefficiently).  Return the
   Nth prime number, where N is the value pointed to by *ARG.  */

int compute_prime(int numPrime)
{
    int candidate;
    while (1)
    {
        int is_prime = 1;

        // Test primality by successive division
        int factor;
        for (factor = 2; factor < candidate && is_prime; ++factor)
            if (candidate % factor == 0)
                is_prime = 0;

        // Is this the prime number we're looking for?
        if (is_prime && --numPrime <= 0)
            return candidate;
        
        candidate++;
    }
  
  return 0;
}

/*
Prime_job() should extract its ID and max prime value and then
enter an endless loop that reads the master_list for a number,
increments master_list, compares the number with the maximum value,
and breaks out of the loop if the maximum is exceeded.  Otherwise,
it calls compute_prime().  Each thread should print its ID, the prime
#, and the value of the prime.  
*/
void* prime_job(void* t)
{
    long tid = (long) t, candidate = 0, total = 0;
    
    printf("Thread %ld starting...\n", tid);
    
    while ((candidate = get_next_candidate()) <= MAX_PRIME)
    {
        compute_prime(candidate);
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
