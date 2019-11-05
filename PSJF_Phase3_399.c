// Assignment: Project 2 Phase 3
// Name : Steven Perry, #800383399
// Course: CS314 - 002
// Created : 3 / 19 / 2018
// Description : Uses a Pre-emptive SJF algorithm to select processes
//					from a list.
// Note: the "PSJF_base.c" file which I have included seperately was 
// 	 provided by my instructor, this file
//       includes my modifications for the assignment
// 
			     
#include <string.h>                    // for strerror()               //
#include <stdio.h>                     // for printf                   //

#define NUM_PROCESSES      10          // Number of processes          //
#define TRUE               1           // TRUE label                   //
#define FALSE              0           // FALSE label                  //

#define NUM_ELEMENTS       4           // the number of elements       //

/* Prototype --------------------------------------------------------- */
void initialize_process_list(void);  // initialize the process definitions

int next_process(int);             // find the next process to run
int actual_exec_time2(int, int);   // the scheduled execution time of the next process to execute
int find_start_time2(int, int);

int  are_all_done(void);             // TRUE if all processes completed
                                     // FALSE otherwise

/* Global variables --------------------------------------------------- */
int current_time;                    // the current time     //
    // YOU CAN ADD YOUR GLOBAL VARIABLES


/* Function prototypes ------------------------------------------------ */
int process_list[NUM_PROCESSES][NUM_ELEMENTS];  // the thread list      //
    // YOU CAN ADD YOUR FUNCTIONS
int completion_flag[NUM_PROCESSES]; // completion flag for individual processes
int remaining_time[NUM_PROCESSES]; // keeps track of remaining time for processes

/* the MAIN ----------------------------------------------------------- */
void main(void)
{

   int next_proc_to_run;        // The process ID for the next process to run
   int all_processes_completed; // the "completion" flag (for the program)
   int exec_time;				// keeps track of execution time

   // YOU CAN ADD YOUR VARIABLES ------------------------------------
   int start_time;

   // initialzie the current time -----------------------------------
   current_time = 0;
   // initialize the all processes completed flag
   all_processes_completed = FALSE;

   // initialzie the thread list ------------------------------------
   initialize_process_list();

   // initialize the completion flag list for individual processes
   for (int i = 0; i < NUM_PROCESSES; i++)
   {
	   completion_flag[i] = FALSE;
   }
   
   // initialize the remaining time for all processes
   for (int i = 0; i < NUM_PROCESSES; i++)
   {
	   remaining_time[i] = process_list[i][2];
   }

   // repeat until all the processes are completed ------------------
   do
   {
      // find the next process to run -------------------------------
      next_proc_to_run = next_process(current_time);

	  // finds the start time of next process 
	  // (might be different than current time)
	  start_time = find_start_time2(current_time, next_proc_to_run);

	  // find the execution duration of the next thread -------------
	  exec_time = actual_exec_time2(next_proc_to_run, start_time);

      // display the progress ---------------------------------------
      printf("Process %d starts at time %d ...\n",
         next_proc_to_run, start_time);

      // display the running time -----------------------------------
      printf("    process %d runs for %d time units ...\n",
         next_proc_to_run, exec_time);

      // update the current time ------------------------------------
      // sleep(exec_time);                         // skip the time
      current_time = start_time + exec_time;     // update the clock
	  remaining_time[next_proc_to_run] -= exec_time;
	  // update the remaining time for this process

	  if (remaining_time[next_proc_to_run] > 0)
	  {
		  
		  printf("    process %d is preempted at time %d, reamining: %d...\n\n",
			  next_proc_to_run, current_time, remaining_time[next_proc_to_run]);
	  }
	  else 
	  {
		  // display the finishing time -----------------------------------
		  printf("    process %d finishes at time %d ...\n\n",
			  next_proc_to_run, current_time);

		  // set individual process completion flag
		  completion_flag[next_proc_to_run] = TRUE;

		  // check if all the processes are completed -------------------
		  all_processes_completed = are_all_done();
	  }

   } while (all_processes_completed == FALSE);

   printf("Press enter to continue...\n");
   getchar();
}

// THE END OF MODULE MAIN ====================================================



/* actual_exec_time2---------------------------------------------------- */
int actual_exec_time2(int next, int start_time)
{
   int execution_time;       // value to be returned for execution time
   int temp_time;			// working time used for pre-emption check

   execution_time = remaining_time[next]; // set the expected execution time
											// if no preemption occurs

   // this mess means: check every unit of time while the process is running
   // if, among all other processes, another process starts and has a higher 
   // priority or the same priority and lower execution time or the same 
   // priority, execution time and lower process ID then it will pre-empt 
   // the current process and stop it mid-way
   for (int i = 1; i < remaining_time[next]; i++)
   {
	   temp_time = start_time + i;
	   for (int j = 0; j < NUM_PROCESSES; j++)
	   {
		   if (process_list[j][1] == temp_time && (process_list[j][3] < process_list[next][3] || 
			    (process_list[j][3] == process_list[next][3] && 
				 (process_list[j][2] < process_list[next][2] || 
				  (process_list[j][2] == process_list[next][2] && j < next)))))
		   {
			   execution_time = i;
			   return (execution_time);

		   }
	   }
   }
   
   return(execution_time);
}
// actual_exec_time2 ///////////////////////////////////////////////////////


int find_start_time2(int curr_time, int next)
{
	int start_time;

	start_time = process_list[next][1];
	if (curr_time > start_time)
		start_time = curr_time;

	return start_time;
}
/* next_process -------------------------------------------------------- *
*                                                                        *
* This module finds the process that should be executed next.            *
* This module returns the process ID of the next process that should be  *
* executed.                                                              *
* ---------------------------------------------------------------------- */
int next_process(int curr_time)
{
 
   int next_process_ID;   // the ID of the chosen process to be returned

   int process_selected; // a check if a process has been identified yet
   int multiple_selected; // a check if multiple processes are currently 
							// selected and another rule check is needed
   int earliest_time; // these are temporary working values to narrow
						// down processes based on rules
   int highest_priority;
   int shortest_execution_time;

   process_selected = 0;
   multiple_selected = 0;
    // these below are all effectively infinity values,
    // they will be set to whatever the first found process
	// yet to be executed's values are (if needed for checks)
   earliest_time = 999999;
   shortest_execution_time = 999999;
   highest_priority = 999999;

   // first we proceed with a for loop that will find the next
   // process if there is a remaining process already queued 
   // (its start time <= current time)
   // and it selects the one with the highest priority
   for (int i = 0; i < NUM_PROCESSES; i++)
   {
	   if (completion_flag[i] == FALSE)
	   {
		   if (process_list[i][1] <= curr_time && process_list[i][3] < highest_priority)
		   {
			   process_selected = 1;
			   next_process_ID = i;
			   highest_priority = process_list[i][3];
			   multiple_selected = 0;
		   }
		   else if (process_list[i][1] <= curr_time && (process_list[i][3] == highest_priority))
		   {
			   multiple_selected = 1;
		   }

	   }
   }

   if (multiple_selected)
   {
	   // If multiple_selected, then we narrow it down by shortest execution time
	   shortest_execution_time = process_list[next_process_ID][2]; // set execution time check
	   multiple_selected = 0;
	   // now we check if another process with a start time <= curr_time and 
	   // a priority equal to the same one already selected has a shorter exeucion time.
	   // The last check would be the process with the lowest process ID 
	   // which will already be selected.
	   for (int i = next_process_ID + 1; i < NUM_PROCESSES; i++)
	   {
		   if (completion_flag[i] == FALSE)
		   {
			   if ((process_list[i][1] <= curr_time) && (process_list[i][3] == highest_priority)
				   && process_list[i][2] < shortest_execution_time)
			   {
				   next_process_ID = i;
				   shortest_execution_time = process_list[i][2];
			   }
		   }
	   }
   }

   // if the next process to run isn't already selected then it wasn't
   // already queued and we have to check for the earliest start time 
   // of the remaining processes. We then proceed in a similar fashion 
   // to the previous checks.
   if (process_selected == 0)
   {
	   for (int i = 0; i < NUM_PROCESSES; i++)
	   {
		   if (completion_flag[i] == FALSE)
		   {
			   if (process_list[i][1] < earliest_time)
			   {
				   next_process_ID = i;
				   earliest_time = process_list[i][1];
				   multiple_selected = 0;
			   }
			   else if (process_list[i][1] == earliest_time)
				   multiple_selected = 1;
		   }
	   }
	   // If multiple_selected, then we narrow it down by priority
	   if (multiple_selected)
	   {
		   highest_priority = process_list[next_process_ID][3];
		   multiple_selected = 0;
		   for (int i = next_process_ID + 1; i < NUM_PROCESSES; i++)
		   {
			   if (completion_flag[i] == FALSE)
			   {
				   if (process_list[i][1] == earliest_time && process_list[i][3] < highest_priority)
				   {
					   next_process_ID = i;
					   highest_priority = process_list[i][3];
					   multiple_selected = 0;
				   }
				   else if (process_list[i][1] == earliest_time && process_list[i][3] == highest_priority)
					   multiple_selected = 1;
			   }
		   }
	   }
	   // If we still have multiple_selected, we narrow down by execution time
	   // with a final implicit check for lowest process ID to break ties
	   if (multiple_selected)
	   {
		   shortest_execution_time = process_list[next_process_ID][2];
		   multiple_selected = 0;
		   for (int i = next_process_ID + 1; i < NUM_PROCESSES; i++)
		   {
			   if (completion_flag[i] == FALSE)
			   {
				   if (process_list[i][1] == earliest_time && process_list[i][3] == highest_priority
					   && process_list[i][2] < shortest_execution_time)
				   {
					   next_process_ID = i;
					   shortest_execution_time = process_list[i][2];
				   }
			   }
		   }
	   }
   }
 
   return(next_process_ID);
}
// next_process ////////////////////////////////////////////////////////////






/* are_all_done --------------------------------------------------------- *
*                                                                         *
*  This module returns "TRUE", if all processes are completed.            *
*  Otherwsie, it returns "FALSE".                                         *
* ----------------------------------------------------------------------- */
int are_all_done(void)
{
   int status = TRUE;      // status (result) code

   for (int i = 0;  i < NUM_PROCESSES; i++)
   {
	   if (completion_flag[i] == FALSE)
		   status = FALSE;
   }

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

///* initialize the process list ----------------------------------------- */
//void initialize_process_list(void)
//{
//	// process #0 ----------------------------------------
//	process_list[0][0] = 0;     // process ID
//	process_list[0][1] = 10;    // start time
//	process_list[0][2] = 4;     // total execution time
//	process_list[0][3] = 0;     // execution priority
//
//								// process #1 ----------------------------------------
//	process_list[1][0] = 1;     // process ID
//	process_list[1][1] = 10;    // start time
//	process_list[1][2] = 4;     // total execution time
//	process_list[1][3] = 1;     // execution priority
//
//								// process #2 ----------------------------------------
//	process_list[2][0] = 2;     // process ID
//	process_list[2][1] = 10;    // start time
//	process_list[2][2] = 3;     // total execution time
//	process_list[2][3] = 1;     // execution priority
//
//								// process #3 ----------------------------------------
//	process_list[3][0] = 3;     // process ID
//	process_list[3][1] = 10;    // start time
//	process_list[3][2] = 4;     // total execution time
//	process_list[3][3] = 1;     // execution priority
//
//								// process #4 ----------------------------------------
//	process_list[4][0] = 4;     // process ID
//	process_list[4][1] = 10;    // start time
//	process_list[4][2] = 4;     // total execution time
//	process_list[4][3] = 1;     // execution priority
//
//								// process #5 ----------------------------------------
//	process_list[5][0] = 5;     // process ID
//	process_list[5][1] = 10;    // start time
//	process_list[5][2] = 2;     // total execution time
//	process_list[5][3] = 1;     // execution priority
//
//								// process #6 ----------------------------------------
//	process_list[6][0] = 6;     // process ID
//	process_list[6][1] = 10;    // start time
//	process_list[6][2] = 4;     // total execution time
//	process_list[6][3] = 1;     // execution priority
//
//								// process #7 ----------------------------------------
//	process_list[7][0] = 7;     // process ID
//	process_list[7][1] = 10;    // start time
//	process_list[7][2] = 4;     // total execution time
//	process_list[7][3] = 1;     // execution priority
//
//								// process #8 ----------------------------------------
//	process_list[8][0] = 8;     // process ID
//	process_list[8][1] = 10;    // start time
//	process_list[8][2] = 4;     // total execution time
//	process_list[8][3] = 1;     // execution priority
//
//								// process #9 ----------------------------------------
//	process_list[9][0] = 9;     // process ID
//	process_list[9][1] = 50;    // start time
//	process_list[9][2] = 1;     // total execution time
//	process_list[9][3] = 1;     // execution priority
//}
