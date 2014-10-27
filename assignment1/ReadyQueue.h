/*
Gilbert Duenas
02/09/14
CS 433 Assignment 01
Priority Queue of Processes
*/
// Header file for ReadyQueue
#ifndef READYQUEUE_H
#define READYQUEUE_H

#include "pcb.h"

class ReadyQueue
{
  private:
    pcb *Process;    // Pointer to array
    int numProcess;    // Number of processes in  heap
    int sizeHeap;    // Array size
    int lastProcessID;    // Last process removed

  public:
    ReadyQueue();    // Constructor
    ~ReadyQueue();    // Destructor

    // Reheapify after adding a process
    void insertReheap(int top, int bottom);    
    // Reheapify after removing a process
    void removeReheap(int top, int bottom);    
    
    bool checkProcess(pcb *process);  // Check if ReadyQueue is full
    // Add the PCB of a process into the ready queue
    bool insertProcess(int id, int priority, string state);
    
    // Remove and return the PCB with the highest priority from the queue
    pcb *removeHighestProc();
    int size();    // Return the number of elements in the queue
    void displayQueue();    // Display the IDs and priorities of processes in the queue
    int lastID();   // Return the last process removed from queue
    void ageQueue();    // Decrement priority ID for existing processes in queue
    int getID(int id);    // Return process ID
};
#endif //READYQUEUE_H
