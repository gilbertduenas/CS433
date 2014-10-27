/*
Gilbert Duenas
02/09/14
CS 433 Assignment 01
Priority Queue of Processes
*/
//Implementation file for ReadyQueue
#ifndef READYQUEUE_CPP
#define READYQUEUE_CPP

#include <iostream>
#include "ReadyQueue.h"
using namespace std;

ReadyQueue::ReadyQueue()
{
  Process = new pcb[20];    // Array of processes
  numProcess = 0;    // Number of processes in ReadyQueue
  sizeHeap = 20;    // Array size
  lastProcessID = 0;    // Last process removed
}

// Destructor
ReadyQueue::~ReadyQueue()
{
  delete[] Process;
}

// Reheapify after adding a process
void ReadyQueue::insertReheap(int top, int bottom)
{
  int primary;
  pcb temp;

  // Reheap using recursion
  if(bottom > top)
  {
    primary = (bottom -1) / 2;
    if(Process[primary].getPriority() > Process[bottom].getPriority())
    {
       // Swap processes
       temp = Process[primary];
       Process[primary] = Process[bottom];
       Process[bottom] = temp;
       // Reheap using recursion
       insertReheap(top, bottom);
    }
  }
} 

// Reheapify after removing a process
void ReadyQueue::removeReheap(int top, int bottom)
{
  int mainNode;
  int rightNode;
  int leftNode;
  pcb temp;

  leftNode = top * 2 + 1;    // Get index of top's left node
  rightNode = top * 2 + 2;    // Get index of top's right node

  // Heapify using recursion starting at bottom
  if(leftNode <= bottom)               
  {
    if(leftNode == bottom)    // If top has no right node then 
    {
      mainNode = leftNode;     // leftNode must be top
    }
    else
    {     
      // Get lowest in ReadyQueue to become mainNode
      if(Process[leftNode].getPriority() > Process[rightNode].getPriority())
        mainNode = rightNode;
      else
        mainNode = leftNode;
    }
    if(Process[top].getPriority() >= Process[mainNode].getPriority())
    {
      // Swap processes
      temp = Process[top];
      Process[top] = Process[mainNode];
      Process[mainNode] = temp;
      // Reheap using recursion
      removeReheap(mainNode, bottom);
    }
  }
}

// Check if ReadyQueue is full
bool ReadyQueue::checkProcess(pcb *process)   
{
   if(numProcess < sizeHeap)
   {
      Process[numProcess] = *process; // Copy item into array
      insertReheap(0, numProcess);
      numProcess++;
      return true;
   }
   cout << "Cannot add Process " << process << ". The queue is full." << endl;
   return false;
}   

// Add process to queue
bool ReadyQueue::insertProcess(int id, int priority, string state)
{
   bool testProcess;
   pcb *temp = new pcb(id, priority, "READY");
   testProcess = checkProcess(temp);
   delete temp;  // Delete place holder
   return testProcess;
}

// Remove highest priority process from queue
pcb *ReadyQueue::removeHighestProc()
{
  if(numProcess == 0)
  {
    cout << "Unable to remove. The queue is empty." << endl;
    return NULL;
  }
  else
  {
    pcb *temp = new pcb(Process[0].getID(), Process[0].getPriority(), Process[0].getState());
    numProcess--;
    lastProcessID = Process[0].getID();
    // Copy last item into root
    Process[0] = Process[numProcess];
    // Reheap the tree
    removeReheap(0, numProcess - 1);
    return temp;
  }
}

// Return the number of elements in the queue
int ReadyQueue::size()
{
  return numProcess;
}
          
// Display the IDs and priorities of processes in the queue
void ReadyQueue::displayQueue()
{
  cout << "\nPCBs IN QUEUE \n==================================="
  << "\nID " << "\tPriority: " << "\tState: " << endl;
  for(int i=0; i<numProcess; i++)
  {
    cout << Process[i].getID() << "\t" << Process[i].getPriority() 
    << "\t\t" << Process[i].getState() << endl;
  }
}

// Return the last process removed from queue
int ReadyQueue::lastID()
{
  return lastProcessID;
}

// Decrement priority ID for existing processes in queue
void ReadyQueue::ageQueue()
{
  int temp = 0;
  for(int i=0; i<numProcess; i++)
  {
    temp = Process[i].getPriority();
    if(temp > 1)  // Priority ID should be at least 1
    {
      Process[i].setPriority(temp-1);
    }
  }
}

// Return process ID
int ReadyQueue::getID(int id)
{
  return Process[id].getID();
}
#endif //HEAP_CPP
