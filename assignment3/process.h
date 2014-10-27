/*
Gilbert Duenas
03/26/14
CS 433 Assignment 03
CPU Scheduling
*/
// Header file for process class
#ifndef PROCESS_H
#define PROCESS_H

#include <string>
using namespace std;

class Process
{
private:
  int processID;
  int startTime;
  int totalCPUduration;
  int remainCPUduration;
  int avgCPUburst;
  int nextCPUburst;
  int IOburst;
  int priority;
  int arriveTime;
  string status; // ready, running, waiting, or terminated 
  
public:
  Process();
  Process(const Process &cSource);
  ~Process();

  int getProcessID();
  int getStartTime();
  int getTotalCPU();
  void setRemainCPU(int input);
  int getAvgCPUburst();
  int getArriveTime();
  void setNextCPUburst(int input);
  void setIOburst(int input);
  void setPriority(int input);
  void setStatus(string input);
  void displayInfo();
};
#endif // PROCESS_H
