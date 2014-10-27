/*
Gilbert Duenas
03/26/14
CS 433 Assignment 03
CPU Scheduling
*/
// Pseudo code was provided through Cougar Courses. 
#ifndef SCHEDULER_CPP
#define SCHEDULER_CPP

#include <iostream>
#include "scheduler.h"
#include "event.h"
#include "process.h"

Scheduler::Scheduler()
{
  cpuState = true; 
  currentTime = 0;
  quitTime = 300002;
}

Scheduler::Scheduler(int processData, int reportData)
{
  cpuState = true; 
  currentTime = 0;
  quitTime = 300002;
  processInput = processData;
  reportInput = reportData;  
}

Scheduler::~Scheduler(){}

void Scheduler::handle_the_event(Event &e)
{
  int eventType = e.getType();
	switch(eventType) 
  {
    case 1: //"process_arrival":
      //handle_proc_arrival(e);
      eventQueue.push(e);
      break;
    case 2: //"CPU_completion":
      //handle_CPU_completion(e);
      eventQueue.push(e);
      break;
    case 3: //"IOcompletion":
    //handle_IO_completion(e);
      eventQueue.push(e);
      break;
    case 4: //"Timer_expiration":
      //handle_Timer_expiration(e);
      eventQueue.push(e);      
      break;
    default:
      cout << "Invalid event type." << endl;
      break;
	}
	//scheduler.run();
}

void Scheduler::run()
{
  if(cpuState) //(CPU is idle) 
  {
    /*
      select and dispatch a proc from ready queue;
      create a CPU completion event; 
      add the new event into EQ;
  */
  // add events to the event queue
    for(int i = 0; i < processInput; i++)
    {
      Process tempProcess; 
      int timeTemp = tempProcess.getStartTime();
      int procIdTemp = tempProcess.getProcessID();   
      Event tempEvent(timeTemp, 1, procIdTemp);
      handle_the_event(tempEvent);
      //Add processes to the queue    
      if(reportInput == 1)
      {
        readyQueue.push(tempProcess);
      }
      else
      {
      //readyQueue2.push(tempProcess);
      }
    }
  } 
  else //(preemptive scheduling and condition is true)
  { 
    /*
      move the running proc to ready queue;
      select and dispatch a proc from ready_queue;
      create a CPU completion event;
      add the new event into EQ;
    */
  }
  //  Generate report  
  switch(reportInput)
  {
    case 1:
    {
      cout << "\nFCFS\n" <<endl;
      int TotalWait = 0;
      int avgTotalWait = 0;
      int TotalTurnAround = 0;
      int avgTurnAround = 0;
      int minutes = 0;
      int seconds = 0;
      int mseconds = 0;
      for(int i = 0; i < processInput; i++)
      {
        Process tempProcess;
        tempProcess = readyQueue.front();
        
        int sumTurnAround;
        int tempStart = tempProcess.getStartTime();
        int tempTotalCPU = tempProcess.getTotalCPU();
        int tempArrive = tempProcess.getArriveTime();
        tempProcess.displayInfo();
        sumTurnAround = tempTotalCPU + tempStart - tempArrive;
        TotalWait += tempStart;
        TotalTurnAround += sumTurnAround;
        readyQueue.pop();
      }    
      avgTotalWait = TotalWait/processInput;
      minutes = avgTotalWait/60000;
      seconds = (avgTotalWait%60000)/1000;
      mseconds = (avgTotalWait%60000)%1000;
      cout << "\naverage Total Wait:\t" << avgTotalWait 
      << "\n" << minutes << " minutes, "
      << seconds << " seconds, " 
      << mseconds << " milliseconds" << endl;
      
      avgTurnAround = TotalTurnAround/processInput;
      minutes = avgTurnAround/60000;
      seconds = (avgTurnAround%60000)/1000;
      mseconds = (avgTurnAround%60000)%1000;
      cout << "\naverage Turn Around:\t" << avgTurnAround 
      << "\n" << minutes << " minutes, "
      << seconds << " seconds, " 
      << mseconds << " milliseconds" << endl;
     } 
     break;
    case 2:
    /*
    {
      cout << "\nnon-preemptive SJF\n" <<endl;
      int TotalWait2 = 0;
      int avgTotalWait2 = 0;
      int minutes2 = 0;
      int seconds2 = 0;
      int mseconds2 = 0;
      for(int i = 0; i < processInput; i++)
      {
        Process tempProcess;
        tempProcess = readyQueue2.top();
        int sum;
        int tempStart = tempProcess.getStartTime();
        int tempTotalCPU = tempProcess.getTotalCPU();
        tempProcess.displayInfo();
         sum = tempTotalCPU + tempStart;
        TotalWait2 += sum;
        readyQueue2.pop();
      }
      avgTotalWait2 = TotalWait2/processInput;
      minutes2 = avgTotalWait2/60000;
      seconds2 = (avgTotalWait2%60000)/1000;
      mseconds2 = (avgTotalWait2%60000)%1000;
      cout << "\naverage Total Wait:\t" << avgTotalWait2 
      << "\n" << minutes2 << " minutes,"
      << seconds2 << " seconds," 
      << mseconds2 << " milliseconds" << endl;
     } 
      
      */
      break;
    default:
      cout << "Invalid event type." << endl;
      break;
  }
} 
  #endif // SCHEDULER_CPP
