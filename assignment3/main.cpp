/*
Gilbert Duenas
03/26/14
CS 433 Assignment 03
CPU Scheduling
*/
#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <time.h>
#include "scheduler.h"

using namespace std;

int main()
{
  cout << "\nAssignment 03\nby Gilbert Duenas....\n";
  srand(time(NULL));
  int processInput;
  int reportInput;
    
  cout << "How many processes would you like to simulate?> ";
  cin >> processInput;
  cout << "\nPlease select report: \n1) FCFS  \n> ";
  //\n2) non-preemptive SJF
  cin >> reportInput;

  Scheduler simulation(processInput, reportInput);
  simulation.run();
  
  return 0;

  }
#endif // MAIN_CPP

