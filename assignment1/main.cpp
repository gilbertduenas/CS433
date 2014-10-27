/*
Gilbert Duenas

Priority Queue of Processes
*/
// Client file
#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <sys/time.h>
#include "pcb.h"
#include "ReadyQueue.h"
using namespace std;

int main()
{
  cout << "\nAssignment 01\nby Gilbert Duenas....\n";
  struct timeval tim; 
  bool run2 = true;

  cout << "\nPress Enter to begin Test 1.... " << endl;
  getchar();
  
  //In the first test, you make a pcb_table of 20 entries with PCB ID from 1 to 20.
  pcb pcb_table[20];
  for(int i=0; i<20; i++)
  {
    pcb_table[i] = pcb(i+1, i+1, "NEW");
  }

  //Create a ReadyQueue q1.
  ReadyQueue *q1 = new ReadyQueue();
  //(a) add processes 5, 1, 8, 11 to q1. Display the content of q1
  q1->insertProcess(pcb_table[4].getID(), pcb_table[4].getPriority(), "READY");
  q1->insertProcess(pcb_table[0].getID(), pcb_table[0].getPriority(), "READY");
  q1->insertProcess(pcb_table[7].getID(), pcb_table[7].getPriority(), "READY");
  q1->insertProcess(pcb_table[10].getID(), pcb_table[10].getPriority(), "READY");
  q1->displayQueue();

  //(b) remove the process with the highest priority from q1 and display q1
  q1->removeHighestProc();
  pcb_table[(q1->lastID())-1].setState("RUNNING");
  q1->displayQueue();

  //(c) remove the process with the highest priority from q1 and display q1
  q1->removeHighestProc();
  pcb_table[(q1->lastID())-1].setState("RUNNING");
  q1->displayQueue();
  
  //(d) Insert processes 3, 7, 2, 12, 9 to q1
  q1->insertProcess(pcb_table[2].getID(), pcb_table[2].getPriority(), "READY");
  q1->insertProcess(pcb_table[6].getID(), pcb_table[6].getPriority(), "READY");
  q1->insertProcess(pcb_table[1].getID(), pcb_table[1].getPriority(), "READY");
  q1->insertProcess(pcb_table[11].getID(), pcb_table[11].getPriority(), "READY");
  q1->insertProcess(pcb_table[8].getID(), pcb_table[8].getPriority(), "READY");
  
  //(e) One by one remove the process with the highest priority from the queue q1 
  //and display it after each removal.
  for(int i=0; i<7; i++)
  {
    q1->removeHighestProc();
    pcb_table[(q1->lastID())-1].setState("RUNNING");
    q1->displayQueue();
  }      

  cout << "\nPress Enter to begin Test 2.... " << endl;
  getchar();
  
  gettimeofday(&tim, NULL);  
  double t1=tim.tv_sec+(tim.tv_usec/1000000.0);
  int randomTemp = 0;
  //First randomly select 10 process from the pcb_table and add them into q1, 
  //but assign each process a random initial priority between 1 and 50
  for(int i=0; i<10; i++)
  {
    q1->insertProcess(pcb_table[rand()%19].getID(), 1+rand()%50, "READY");
  }
  for(int i=0; i<1000000; i++)
  {
    //(a) remove one process with the highest priority from q1 using the removeHighestProc function.    
    q1->removeHighestProc();
    pcb_table[(q1->lastID())-1].setState("RUNNING");
    
    //(b) Decrement the priority values of the processes still in q1.    
    q1->ageQueue();
    //(c) Randomly select one process from the pcb_table that isn't currently in q1 
    // and insert it into q1 using the insertProc function, 
    // with a random initial priority value between 1 and 50.
    while(run2)  // While loop to check
    {
      randomTemp = rand()%19;  // Generate a random index
      bool notFound = true;
      for(int i=0; i<q1->size(); i++)
      {
        if(randomTemp == q1->getID(i))  // Check if random index matches ID in queue
        {
          notFound = false;  // Return false if there is a match
        }
      }
      if(notFound)  // If the ID is not in queue, add the process to the queue
      {
          q1->insertProcess(pcb_table[randomTemp].getID(), 1+rand()%50, "READY");
          pcb_table[randomTemp].setState("READY");
          run2 = false;  // Break out of the while loop
      }
    }
    run2 = true;  // Reset the while loop before returning to the main for loop
  }
  gettimeofday(&tim, NULL);  
  double t2=tim.tv_sec+(tim.tv_usec/1000000.0);  
  printf("%.6lf seconds elapsed\n", t2-t1);  

  return 0;
}
#endif //MAIN_CPP
