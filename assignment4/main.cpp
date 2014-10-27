/*
Gilbert Duenas
04/21/14
CS 433 Assignment 04
Multi-threaded Programing for the Producer-Consumer Problem
*/
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef int buffer_item;
#define BUFFER_SIZE 5

buffer_item buffer[BUFFER_SIZE];
int counter, first, last;
pthread_mutex_t mutex;
sem_t maximum;
sem_t none;

int insert_item(buffer_item item)
{
  // insert an item into buffer
  if(counter != BUFFER_SIZE)
  {
    buffer[last] = item;
    printf ("Producer: %d\n", item);
    last = (last + 1) % BUFFER_SIZE;
    counter++;
    // return 0 if successful, otherwise
    return 0;
  }
  // return -1 indicating an error condition   
  return -1;
}

int remove_item(buffer_item *item)
{
  // remove an object from buffer and placing it in item
  if(counter > 0)
  {
    item = &buffer[first];
    printf("Consumer: %d\n", buffer[first]);
    first = (first + 1) % BUFFER_SIZE;
    counter--;
    // return 0 if successful, otherwise
    return 0;
  }
  // return -1 indicating an error condition 
  return -1;
}

void print()
{
  if(counter == 0)
  {
    printf("\nThe buffer is empty\n");
  }
  else
  {
    printf("The current content of the buffer is [");
    if(last > first)
    {	  
      for(int i = first; i < last; i++)
      {
        printf(" %i ", buffer[i]);
      }
    }
    if(last <= first)
    {
      for(int i = first; i < BUFFER_SIZE; i++)
      {
        printf(" %i ", buffer[i]);
      }
      for(int i = 0; i < last; i++)
      {
        printf(" %i ", buffer[i]);
      }
    }
    printf("]\n");
  }
}

void *producer(void *param)
{
  buffer_item item;

  while(1)
  {
    sleep(rand() % 5 + 1);
    item =  rand() % 50 + 1;
    sem_wait(&none); // wait for opening
    pthread_mutex_lock(&mutex); // lock mutex

    if(insert_item(item) == - 1)
    {
    }
    else
    {
      print();
    }
    pthread_mutex_unlock(&mutex); //unlock mutex
    sem_post(&maximum); 
  }
}

void *consumer(void *param)
{
  buffer_item item;
  
  while(1)
  {
    sleep(rand() % 5 + 1);
    sem_wait(&maximum); // wait for maximum
    pthread_mutex_lock(&mutex); // lock mutex

    if(remove_item(&item)){}
    else
    {
      print();
    }
    pthread_mutex_unlock(&mutex);//release mutex 
    sem_post(&none); // informs producer slot has been opened
  }
}

int main(int argc, char *argv[]) 
{
  printf("\nAssignment 04\nby Gilbert Duenas....\n");
  srand(time(NULL));
  
// 1. Get command line arguments argv[1], argv[2], argv[3] 
  int sleepInput = atoi(argv[1]);
  int producerInput = atoi(argv[2]);
  int consumerInput = atoi(argv[3]);

  if((argc < 4) || (sleepInput <= 0) || (producerInput <= 0) || (consumerInput <= 0))  
  {
    printf("Invalid entry. Please enter three parameters greater than zero.\n");
    return -1;
  }
  
// 2. Initialize buffer, mutex, semaphores, and other global vars 
  char *produce = "Producer";
  char *consume = "Consumer";
  pthread_t producerThread[producerInput];
  pthread_t consumerThread[consumerInput];  
  sem_init(&none, 0, BUFFER_SIZE); // set to none
  sem_init(&maximum, 0, 0); // set to zero
  pthread_mutex_init(&mutex, NULL); 
  
// 3. Create producer thread(s) 
  for(int i = 0; i < producerInput; i++)
  {
    pthread_create(&producerThread[i], NULL, producer, produce);
  }

// 4. Create consumer thread(s) 
  for(int i = 0; i < consumerInput; i++)
  {
    pthread_create(&consumerThread[i], NULL, consumer, consume);
  }

// 5. Sleep 
  sleep(sleepInput);

// 6. Release resources, e.g. destroy mutex and semaphores 
  //pthread_mutex_destroy mutex;
  //sem_destroy(&none);
  //sem_destroy(&maximum);
// 7. Exit 
  return 0;
}
