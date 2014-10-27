/*
  Gilbert Duenas
  05/07/14
  CS 433 Assignment 05
  Simulation of Page Replacement Algorithms
*/
#include <iostream>
#include <sys/time.h>

using namespace std;

struct pageEntry
{
  // In the pagetable entry data structure, you need additionalfields, e.g. valid and dirty bits, 
  // besides the mapped frame number of the page. 
  bool dirty;
  bool valid;
  int pageInput;
  int last;
};

// Search for entry
int search(struct pageEntry *Table, int totalPageFault, int fileOutput)
{  
  for(int i = 0; i < totalPageFault; i++)
    if(Table[i].pageInput == fileOutput)
      {
	return i;
      }
  return -1;
}

void simulation(int pageSize, int physicalSize, int mainInput)
{
  int elapsedTime = 0;
  int totalPageFault = physicalSize/pageSize;
  int memoryRefCount = 0; 
  int pageEntryFaults = 0;
  int Flushed = 0;
  
  if (mainInput == 1)
    {
      cout << "\nRandom simulation, please wait.... " << endl;
    } 
  else if(mainInput == 2)
    {
      cout << "\nFIFO simulation, please wait.... " << endl;
    } 
  else
    {
      cout << "\nLRU simulation, please wait...." << endl;  
    } 
  
  // timer start
  struct timeval time; 
  gettimeofday(&time, NULL);  
  double t1=time.tv_sec+(time.tv_usec/1000000.0);
  
  // The simulator should read a sequence of logical memory references from a file (references.txt). 
  FILE *file = fopen("references.txt", "r");
  
  // Assume that when the simulation start, the physical memory is empty, 
  // i.e. all page table entries are invalid. 
  // As they are brought in, the simulator should make sure that the total 
  // number of pages in memory should never exceed the physical memory size.
  // Your program should keep track of pages in the memory and free frames. 
  // Therefore you need to maintain a pagetable data structure, 
  // which can be easily implemented as an array of page-table entries, and a free-frame list. 
  // The number of pages is dependent on the page size. 
  // In the pagetable entry data structure, you need additionalfields, e.g. valid and dirty bits, 
  // besides the mapped frame number of the page. 
  struct pageEntry pageTable[totalPageFault];
  for(int i = 0; i < totalPageFault; i++)
    {
      pageTable[i].dirty = false;
      pageTable[i].valid = false;
      pageTable[i].pageInput = 0;
      pageTable[i].last = 0;
    }
  
  char fileData[80];
  int lineCounter = 0;// for FIFO
  int fileCount = 0;// for LRU
  
  // This file contains a list of virtual (logical) memory byte addresses accessed by a program. 
  // In this simulation, the maximum virtual memory address is 128 MB (227bytes) 
  // and the number of addresses in the file is 5,000,000. 
  while(fgets(fileData, sizeof fileData, file) != NULL)
    {
      fileCount ++;
      int fileOutput = atoi(fileData);
      
      // In this simulation, the least significant bit is used to differentiate 
      // between a read access (0, i.e. even number) or write access (1, i.e. odd number). 
      // For example, the value 1220149 means a write reference to memory location 1220148. 
      // Those addresses can be assumed to be aligned at a two-byte boundary, 
      // i.e., they are always even. 
      // We can safely play this simple trick because the minimum page size is 256 bytes, 
      // so the eight least significant bits of an address are irrelevant to the page number anyway.
      bool dirty = fileOutput % 2;
      
      // For each memory reference,find out its page number 
      // and whether this page is in the main memory. 
      int inputFound = search(pageTable, totalPageFault, fileOutput - dirty);
      memoryRefCount ++;//increments memory reference for referencing pageEntry table
      
      // If the memory reference is a write, this page is marked dirty. 
      if(inputFound >= 0)
	{
	  pageTable[inputFound].dirty = dirty;
	  pageTable[inputFound].last = fileCount;
	  memoryRefCount ++;
	  continue;
	}
      // If this page is not in the main memory, 
      // a page fault is generated and this page is loaded into the main memory. 
      // However, if the main memory is full, 
      // a victim page must be selected and evicted according a page replacement algorithm. 
      // Your simulation is to compare different page replacement algorithms. 
      // Notice you may need to keep track of additional information 
      // such as last page access time for the LRU (least recently used) algorithm.  
      
      else
	{
	  //  cout << "pageEntryFaults ++;" << endl;
	  pageEntryFaults ++;
	  
	  struct pageEntry insertEntry;
	  insertEntry.dirty = dirty;
	  insertEntry.valid = true;
	  insertEntry.pageInput = fileOutput - dirty;
	  insertEntry.last = fileCount;
	  int selected;
	  
	  // calculate random
	  if (mainInput == 1)
	    {
	      int random = rand() % totalPageFault;
	      selected = random;
	    }
	  
	  // calculate FIFO
	  else if(mainInput == 2)
	    {
	      selected = lineCounter;
	      lineCounter++;
	      lineCounter = lineCounter % totalPageFault;
	    }
	  
	  // calculate LRU
	  else if(mainInput == 3)
	    {
	      if(!pageTable[lineCounter].valid)
		{
		  selected = lineCounter;
		  lineCounter++;
		  lineCounter = lineCounter % totalPageFault;
		}
	      else
		{
		  int lowestNumber = fileCount;
		  int lowestFound = lineCounter;//location on array of the page
		  
		  //goes through the table to find the earliest used page
		  for(int i = 0; i < totalPageFault; i++)
		    {
		      if(pageTable[i].last < lowestNumber)
			{
			  lowestFound = i;
			  lowestNumber = pageTable[i].last;
			}
		    }
		  selected = lowestFound;
		}   
	    }
	  Flushed += pageTable[selected].dirty;//if selected was dirty, increment Flushed
	  pageTable[selected] = insertEntry;//replace the new pageEntry
	  memoryRefCount ++;//increment memory reference
	}
    }  
  
  // timer end
  gettimeofday(&time, NULL);  
  double t2=time.tv_sec+(time.tv_usec/1000000.0);  
  elapsedTime = t2-t1;
  
  // print report
  if (mainInput == 1)
    {
      cout << "\nRandom Results.... ";
    } 
  else if(mainInput == 2)
    {
      cout << "\nFIFO Results.... ";
    } 
  else
    {
      cout << "\nLRU Results....";
    } 
  cout << "\nMemory References: " << memoryRefCount
       << "\nPage Faults:\t" << pageEntryFaults
       << "\nFlushed:\t" << Flushed
       << "\nElapsed:\t" << elapsedTime << endl;
}

int main(int argc, char* argv[])
{
  printf("Assignment 04 by Gilbert Duenas....\n");
  srand(time(NULL));
  int pageSize = atoi(argv[1]);
  int physicalSize = atoi(argv[2]); 
  
// The page size must be a number of power of 2 between 256 and 8192 bytes inclusively. 
  if(pageSize < 256 || pageSize > 8192 || argc < 3)
    {
      cout << "The page size must be a number of power of 2 between 256 and 8192 bytes inclusively." << endl;
      exit(1);
    }
  // The physical memory size is also power of 2.
  if(((pageSize & (pageSize -1)) != 0) || ((physicalSize &(physicalSize - 1)) != 0))
    {
      cout << "The physical memory size is also power of 2." << endl;
      exit(1);
    }
  
  simulation(pageSize, physicalSize, 1);
  simulation(pageSize, physicalSize, 2);
  simulation(pageSize, physicalSize, 3);
  
  return 0;
}
