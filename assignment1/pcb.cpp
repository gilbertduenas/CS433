/*
Gilbert Duenas
02/09/14
CS 433 Assignment 01
Priority Queue of Processes
*/
//Implementation file for Process Control Block
#ifndef PCB_CPP
#define PCB_CPP

#include "pcb.h"

// Default constructor
pcb::pcb()    
{
  pcbID = 0;    // ID value
  pcbPriority = 0;    // Priority value
  State = "NEW";   // Current pcb state
}

pcb::pcb(int id, int priority, string state)
{
  pcbID = id;   // ID value
  pcbPriority = priority;    // Priority value
  State = state;   // Current pcb state  
} 

// Destructor
pcb::~pcb(){}   

// Return process ID
int pcb::getID()
{
  return pcbID;
}

// Set process ID  
void pcb::setID(int id)
{
  pcbID = id;
}

// Return process priority
int pcb::getPriority()
{
  return pcbPriority;
} 

// Set process priority
void pcb::setPriority(int priority)
{
  pcbPriority = priority;    // Priority value  
} 

// Return process state
string pcb::getState()
{
  return State;
} 

// Set process state
void pcb::setState(string state)
{
  State = state;   // Current pcb state  
} 
#endif //PCB_CPP
