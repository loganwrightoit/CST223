/***********************************************************************
* Code listing from "Advanced Linux Programming," by CodeSourcery LLC  *
* Copyright (C) 2001 by New Riders Publishing                          *
* See COPYRIGHT for license information.                               *
***********************************************************************/

#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 5

int thread_flag;
int candidate = 2;
pthread_mutex_t thread_flag_mutex;

void initialize_flag ()
{
  pthread_mutex_init (&thread_flag_mutex, NULL);
}

int get_prime_candidate()
{
	// Only one thread can access counter at a time
	pthread_mutex_lock (&thread_flag_mutex);
    return candidate++;
    pthread_mutex_unlock (&thread_flag_mutex);
    
    printf("New candidate of %d\n", candidate);
}

/* Compute successive prime numbers (very inefficiently).  Return the
   Nth prime number, where N is the value pointed to by *ARG.  */

void* compute_prime (void* arg)
{
  int n = *((int*) arg) + 1;

  int next_candidate;
  while ((next_candidate = get_prime_candidate()) <= n)
  {
    int factor;
    int is_prime = 1;

    /* Test primality by successive division.  */
    for (factor = 2; factor < next_candidate; ++factor)
      if (next_candidate % factor == 0) {
        is_prime = 0;
        break;
      }
    /* Is this the prime number we're looking for?  */
    if (is_prime) {
      if (--n == 0)
        /* Return the desired prime number as the thread return value.  */
        return (void*) next_candidate;
    }
  }
  return NULL;
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
    pthread_create(&thread[i], NULL, &compute_prime, &which_prime);
  }

  // Join threads
  for (i = 0; i < NUM_THREADS; ++i)
  {
    printf("Joining thread %d\n", (int) getpid());
    int result;
    pthread_join(thread[i], (void*) &result);
    prime &= result;
  }
  
  /* Print the largest prime it computed.  */
  printf("The %dth prime number is %d.\n", which_prime, prime);
  return 0;
}
