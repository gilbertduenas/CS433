/*
Gilbert Duenas
03/26/14
CS 433 Assignment 03
CPU Scheduling
*/
// Pseudo code was provided through Cougar Courses. 
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <queue>
#include "event.h"
#include "process.h"

using namespace std;

class Scheduler 
{
private:
  bool cpuState; // is the CPU idle?
  int currentTime;
  int quitTime; 
  int processInput;
  int reportInput;
 queue<Process> readyQueue; 
 //priority_queue<Process> readyQueue2;
 queue<Event> eventQueue;

public:  
  Scheduler();
  Scheduler(int processData, int reportData);
  ~Scheduler();

  void handle_the_event(Event &e);
  void run();
};
#endif // SCHEDULER_H
