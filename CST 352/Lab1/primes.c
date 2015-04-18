/***********************************************************************
* Code listing from "Advanced Linux Programming," by CodeSourcery LLC  *
* Copyright (C) 2001 by New Riders Publishing                          *
* See COPYRIGHT for license information.                               *
***********************************************************************/

#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 5

int thread_flag;
int current = 2; // Start at first prime
pthread_mutex_t thread_flag_mutex;

void initialize_flag ()
{
    pthread_mutex_init(&thread_flag_mutex, NULL);
}

/* Compute successive prime numbers (very inefficiently).  Return the
   Nth prime number, where N is the value pointed to by *ARG.  */

int compute_prime(int numPrime)
{
  int candidate;
  while (candidate++)
  {
    int is_prime = 1;

    /* Test primality by successive division.  */
    int factor;
    for (factor = 2; factor < candidate; ++factor)
    {
      if (candidate % factor == 0)
      {
        is_prime = 0;
        break;
      }
    }
    
    /* Is this the prime number we're looking for?  */
    if (is_prime)
    {
      if (--numPrime == 0)
      {
        return candidate;
      }
    }
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
void* prime_job(void* arg)
{
    int pid = (int) getpid();
    int max_prime = *((int*) arg);
    int outputCounter = 0;
    
    int candidate = 0, numPrimesCalc, result;
    while (candidate <= max_prime)
    {
        pthread_mutex_lock (&thread_flag_mutex);
        candidate = current++;
        pthread_mutex_unlock (&thread_flag_mutex);

        result = compute_prime(candidate);
        
        // Print result 125 times
        if (outputCounter++ > 125)
        {
            printf("PID: %d computed %d prime: %d\n", pid, candidate, result);
            outputCounter = 0;
        }
        
        ++numPrimesCalc;
    }
    
    return (void*) numPrimesCalc;
}

int main ()
{
  initialize_flag();

  pthread_t thread[NUM_THREADS];
  int which_prime = 5000;
  int prime;

  // Start threads
  int i;
  for (i = 0; i < NUM_THREADS; ++i)
  {
    pthread_create(&thread[i], NULL, &prime_job, &which_prime);
  }

  // Join threads
  for (i = 0; i < NUM_THREADS; ++i)
  {
    int numPrimesCalc;
    pthread_join(thread[i], (void*) &numPrimesCalc);
    printf("Thread joined, calced %d primes\n", numPrimesCalc);
  }
  
  /* Print the largest prime it computed.  */
  printf("The %dth prime number is %d.\n", which_prime, prime);
  return 0;
}
