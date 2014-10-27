/*
Gilbert Duenas
02/09/14
CS 433 Assignment 01
Priority Queue of Processes
*/
// Header file for Process Control Block
#ifndef PCB_H
#define PCB_H

#include <string>
using namespace std;

class pcb
{
  private:
    int pcbID;    // ID number
    int pcbPriority;    // Priority value
    string State;   // Current pcb state

  public:
    pcb();    // Default constructor
    pcb(int id, int priority, string state);
    ~pcb();    // Destructor
    
    int getID();    // Return process ID
    void setID(int id);   // Set process ID  
    int getPriority();    // Return process priority
    void setPriority(int priority);   // Set process priority
    string getState();    // Return process state
    void setState(string state);    // Set process state
};
#endif //PCB_H
