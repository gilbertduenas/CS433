/*
Gilbert Duenas
03/26/14
CS 433 Assignment 03
CPU Scheduling
*/
// Implementation file for event class
// Pseudo code was provided through Cougar Courses. 
#ifndef EVENT_CPP
#define EVENT_CPP

#include <iostream>
#include "event.h"

Event::Event()
{
  time = 0;  //time when event should take place
  type = 1;  //type of event
  procId = 0;  //process to which event belongs 
}

Event::Event(int timeInput, int typeInput, int procIdInput)
{
  time = timeInput;  //time when event should take place
  type = typeInput;  //type of event
  procId = procIdInput;  //process to which event belongs 
}

Event::~Event(){}

Event::Event(const Event &cSource)
{
  time = cSource.time;
  type = cSource.type;
  procId = cSource.procId;
}
 
void Event:: setTime(int input)
{
  time = input;
}
  
void Event::setType(int input)
{
  type = input;
}

int Event::getType()
{
  return type;
}

void Event::displayInfo()
{
  cout << "\ntime:\t\t" << time
  << "\ntype:\t\t" << type
  << "\nprocId:\t\t" << procId << endl;
}
#endif // EVENT_CPP


