/*
  Gilbert Duenas
  Shell Implementation
*/
/*
I used examples from sections of the following links to 
create a working prototype. 
However, I was not successful 
and the program is only about 40% complete.  
I had planned to create a shell class 
with separate header and implementation files.

Primary sources:
    http://nsl.cs.sfu.ca/teaching/11/300/prj2_shell.html
    http://keviv03.blogspot.com/2012/05/unix-shell-history-feature.html
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <string>

using namespace std;

#define MAX_LINE 80   // maximum length for commands
#define BUFFER_SIZE 50
#define buffer "\n\nosh > "

char history[10][BUFFER_SIZE];
int counter = 0;
int caught = 0;
int placePointer;

void displayHistory()
{
  int i;
  int j = 0;
  int historyCount = counter;
  
  for (i = 0; i<10;i++)
  {
    printf("%d.  ", historyCount);
    while (history[i][j] != '\n' && history[i][j] != '\0')
    {
      printf("%c", history[i][j]);
      j++;
    }
    printf("\n");
    j = 0;
    historyCount--;
    if (historyCount ==  0)
    {
      break;
    }
  }
}

void runHistory(int index)
{
  index = (index-1)%10;
  printf("Run History....\n");
  char *arg1 = &history[index][0]; 
  char *argLine[MAX_LINE/2+1];
  int j;
  for (j = 0; j < MAX_LINE/2+1; j++) 
  {
    *argLine[j] = history[index][j]; 
  }
  execvp(arg1,argLine);
}

void setup(char inputBuffer[], char *args[], int *background)
{
  int length, // number of characters entered
    start,  // index where beginning of next command parameter is 
    ct;     // index of where to place the next parameter into args[] 
  ct = 0;
  
  // read what the user enters on the command line 
  length = read(STDIN_FILENO, inputBuffer, MAX_LINE);
  
  // copy string into next index
  for (int i = 9; i>0; i--)
  {
    strcpy(history[i], history[i-1]);
  }
  
  strcpy(history[0],inputBuffer);
  counter++;
  start = -1;
  if (length == 0)
  {
    exit(0); 
  }
  
  if (length < 0)
  {
    perror("error reading the command\n");
    exit(-1);           // terminate with error code of -1 
  }
  
  // examine every character in the inputBuffer 
  for (int i=0;i<length;i++)
  {
    switch (inputBuffer[i])
    {
    case '\t' :               // argument separators 
      if(start != -1)
        {
          args[ct] = &inputBuffer[start];    // set up pointer 
          ct++;
        }
      inputBuffer[i] = '\0'; // add a null char; make a C string 
      start = -1;
      break;
      
    case '\n':                 // should be the final char examined 
      if (start != -1)
        {
          args[ct] = &inputBuffer[start];
          ct++;
        }
      inputBuffer[i] = '\0';
      args[ct] = 0; // no more arguments to this command 
      break;
    default :             // some other character 
      if (start == -1)
      {
        start = i;
      }
      if (inputBuffer[i] == '&')
      {
        *background  = 1;
        inputBuffer[i] = '\0';
      }
    }
  }
  args[ct] = 0; // just in case the input line was > 80 
}

int main(void)
{
  char *args[MAX_LINE/2 + 1];  // arguments for command line
  char inputBuffer[MAX_LINE]; // buffer to hold the command entered 
  int background;             // equals 1 if a command is followed by '&' 
  pid_t pid;
  //int i;

  while(1)
  {
    background= 0;
    printf("osh> ");
    fflush(stdout);
    setup(inputBuffer,args,&background);       // get next command 

    // After reading user input, the steps are:
    // (1) fork a child process using fork()
    pid = fork();
    if (pid < 0)
    {
      printf("Fork failed.\n");
      exit (1);
    }
    // (2) the child process will invoke execvp()
    else if (pid == 0)
    {
      if( strcmp(args[0],"history") == 0)
      { 
        displayHistory();
      }
      else if(strcmp(args[0],"!") == 0)
      { 
        int index = (int) args[1];
        runHistory(index - 1);
      }
      else if(strcmp(args[0], "!!") == 0)
      { 
        if(counter > 0)
        {
          runHistory(counter);
        }
        else
        {
          printf("No commands in history");
        }
      }
      placePointer = (placePointer + 1) % 10;
      // Execute!  
      execvp(args[0],args);
    }
    // (3) if command included &, parent will invoke wait()
    else
    {
      if (background == 0)
      wait();
    }  
  }
  return 0;
}

