/* ******************************************************************* *
* PSJF_base.c:                                                         *
*                                                                      *
* This C program simulates a short-term process scheduler for          *
* "Premptive Priority Non-Preemptive SJF (Shortest Job First)"         *
* short-term process scheduling algorithm.                             *
*                                                                      *
* This program takes a two-dimensional array ("process_list") that     *
* define each process "i" using the following attributes:              *
*                                                                      *
*   REQUIRED PARAMETERS (for Process i) ------------------------------ *
*   (0) process_list[i][0] = 0;     // process ID                      *
*   (1) process_list[i][1] = 1;     // start time                      *
*   (2) process_list[i][2] = 15;    // total execution time            *
*   (3) process_list[i][3] = 9;     // process priority                *
*   ------------------------------------------------------------------ *
*                                                                      *
* Each process is defined in a module, "initialize_process_list".      *
* For the process priority, the smaller the priority number is, the    *
* higher the priority is (i.e., '0' means the highest priority).       *
*                                                                      *
* The outputs from this simulator are:                                 *
*   (a) process start time (when it starts running)                    *
*   (b) how long a process is executed (in time units)                 *
*   (c) stop time (completed or preempted time)                        *
*   (d) - optional - if it is completed or preempted                   *
*                                                                      *
* Compile: cc PSJF_base.c                                              *
*                                                                      *
* Host: os.cs.siue.edu                                                 *
*                                                                      *
* Last Updated at: 19:12, Januray 12, 2018                             *
*                                                                      *
* Place: Edwardsville, IL                                              *
*                                                                      *
* ******************************************************************** */
#include <string.h>                    // for strerror()               //
#include <stdio.h>                     // for printf                   //

#define NUM_PROCESSES      10          // Number of processes          //
#define TRUE               1           // TRUE label                   //
#define FALSE              0           // FALSE label                  //

#define NUM_ELEMENTS       4           // the number of elements       //

/* Prototype --------------------------------------------------------- */
void initialize_process_list(void);  // initialize the process definitions
int  find_earliest_process(void);    // find the very first process to begin with
int  actual_exec_time1(....);        // the scheduled execution time for the very first process

int  next_process(....);             // find the next process to run
int  actual_exec_time2(....);        // the scheduled execution time of the next process to execute

int  are_all_done(void);             // TRUE if all processes completed
                                     // FALSE otherwise

/* Global variables --------------------------------------------------- */
int current_time;                    // the current time     //
    // YOU CAN ADD YOUR GLOBAL VARIABLES

/* Function prototypes ------------------------------------------------ */
int process_list[NUM_PROCESSES][NUM_ELEMENTS];  // the thread list      //
    // YOU CAN ADD YOUR FUNCTIONS

/* the MAIN ----------------------------------------------------------- */
void main(void)
{
   int                 i;       // loop counter

   int next_proc_to_run;        // The process ID for the next process to run
   int all_processes_completed; // the "completion" flag

   // YOU CAN ADD YOUR VARIABLES ------------------------------------





   // initialzie the current time -----------------------------------
   current_time = 0;

   // initialzie the thread list ------------------------------------
   initialize_process_list();

   // find the first thread to run ----------------------------------
   next_proc_to_run = find_earliest_process();


   // set the execution time length (Phase 2 and 3) -----------------
   exec_time = actual_exec_time1(next_proc_to_run);


   // advance the simulation time -----------------------------------
   // sleep(exec_time);                         // skip the time
   current_time = current_time + exec_time;     // update the clock





   // repeat until all the processes are completed ------------------
   do
   {
      // find the next process to run -------------------------------
      next_proc_to_run = next_process(....);

      // find the execution duration of the next thread -------------
      exec_time = actual_exec_time2(....);


      // display the progress ---------------------------------------
      printf("Process %d starts at time %d ...\n",
         next_proc_to_run, current_time);

      // display the running time -----------------------------------
      printf("    process %d runs for %d time units ...\n",
         next_proc_to_run, exec_time);


      // update the current time ------------------------------------
      // sleep(exec_time);                         // skip the time
      current_time = current_time + exec_time;     // update the clock



      // check if all the processes are completed -------------------
      all_processes_completed = are_all_done();

   } while ((all_processes_completed == FALSE) && (next_proc_to_run >= 0));
}

// THE END OF MODULE MAIN ====================================================

/* actual_exec_time1 --------------------------------------------------- */
int actual_exec_time1(....)
{
   int time_to_run;               // how long more can I use the processor

   return(time_to_run);
}
// actual_exec_time1 ///////////////////////////////////////////////////////



/* actual_exec_time2---------------------------------------------------- */
int actual_exec_time2(....)
{
   int more_execution_time;       // at least one unit time
   

   return(more_execution_time);
}
// actual_exec_time2 ///////////////////////////////////////////////////////



/* next_process -------------------------------------------------------- *
*                                                                        *
* This module finds the process that should be executed next.            *
* This module returns the process ID of the next process that should be  *
* executed.                                                              *
* ---------------------------------------------------------------------- */
int next_process(....)
{
 
   int next_process_ID;   // the ID of the chosen process (final)

 
   return(next_process_ID);
}
// next_process ////////////////////////////////////////////////////////////



/* find_earliest_process ------------------------------------------------- */
int find_earliest_process(void)
{

   int the_earliest_process;   // the ID of the process that is supposed to
                               // be executed first for each simulation run

   return(the_earliest_process);
}
// find_earliest_process ///////////////////////////////////////////////////



/* are_all_done --------------------------------------------------------- *
*                                                                         *
*  This module returns "TRUE", if all processes are completed.            *
*  Otherwsie, it returns "FALSE".                                         *
* ----------------------------------------------------------------------- */
int are_all_done(void)
{
   int status = TRUE;      // status (result) code




   return(status);
}
// are_all_done ////////////////////////////////////////////////////////////



/* initialize the process list ----------------------------------------- */
void initialize_process_list(void)
{
   // process #0 ----------------------------------------
   process_list[0][0] = 0;     // process ID
   process_list[0][1] = 1;     // start time
   process_list[0][2] = 6;     // total execution time
   process_list[0][3] = 2;     // execution priority

   // process #1 ----------------------------------------
   process_list[1][0] = 1;     // process ID
   process_list[1][1] = 5;     // start time
   process_list[1][2] = 3;     // total execution time
   process_list[1][3] = 3;     // execution priority

   // process #2 ----------------------------------------
   process_list[2][0] = 2;     // process ID
   process_list[2][1] = 3;     // start time
   process_list[2][2] = 4;     // total execution time
   process_list[2][3] = 0;     // execution priority

   // process #3 ----------------------------------------
   process_list[3][0] = 3;     // process ID
   process_list[3][1] = 5;     // start time
   process_list[3][2] = 4;     // total execution time
   process_list[3][3] = 2;     // execution priority

   // process #4 ----------------------------------------
   process_list[4][0] = 4;     // process ID
   process_list[4][1] = 11;    // start time
   process_list[4][2] = 1;     // total execution time
   process_list[4][3] = 0;     // execution priority

   // process #5 ----------------------------------------
   process_list[5][0] = 5;     // process ID
   process_list[5][1] = 8;     // start time
   process_list[5][2] = 4;     // total execution time
   process_list[5][3] = 1;     // execution priority

   // process #6 ----------------------------------------
   process_list[6][0] = 6;     // process ID
   process_list[6][1] = 8;     // start time
   process_list[6][2] = 2;     // total execution time
   process_list[6][3] = 0;     // execution priority
   
   // process #7 ----------------------------------------
   process_list[7][0] = 7;     // process ID
   process_list[7][1] = 4;     // start time
   process_list[7][2] = 3;     // total execution time
   process_list[7][3] = 2;     // execution priority

   // process #8 ----------------------------------------
   process_list[8][0] = 8;     // process ID
   process_list[8][1] = 23;    // start time
   process_list[8][2] = 4;     // total execution time
   process_list[8][3] = 1;     // execution priority
   
   // process #9 ----------------------------------------
   process_list[9][0] = 9;     // process ID
   process_list[9][1] = 19;    // start time
   process_list[9][2] = 3;     // total execution time
   process_list[9][3] = 1;     // execution priority  
}