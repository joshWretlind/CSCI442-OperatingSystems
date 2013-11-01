/* This is the student's file for interacting with the GUI source code. There are
three pieces of information that the GUI needs to properly display the scheduling queues.
These are global variables and their extern decleration can be found in the glo.h file. 
1. An array of struct pi of HISTORY length. (HISTORY is a defined constant set to 50).
This is define in glo.h as extern struct pi pInfo[HISTORY][ALL_PROCS]. 
(ALL_PROCS is a defined constant equal to the lenght of the process table). 
HINT: You need to create a system call to the scheduler to obtain the information in struct pi.
HINT: struct pi is declared in /usr/src/include/minix/pi.h. 
This struct is used in place of struct proc, because it is easier to send.
2. An array of struct qh that contains the name and endpoint of the process at the head of each priority queue. 
struct qh pQh[HISTORY][NR_SCHED_QUEUES] is defined in glo.h. (NR_SCHED_QUEUES is a Minix defined constant with the number of priority queues).
HINT: You need to create a kernel call, because this information is in the kernel scheduling table.
HINT: The head of a priority queue may not exist if there are no runnable processes. Make sure you check for this. 
3. CPU frequency. This is defined as u64_t cpuFreq in glo.h.
HINT: You can add this to the kernel call from part 2. */
#include "student.h"
#include <stdio.h>

struct pi *pInfoPtrs[HISTORY];
struct pi pInfo[HISTORY][ALL_PROCS];
u64_t cpuFreq;
struct qh *pQhPtrs[HISTORY];
struct qh pQh[HISTORY][NR_SCHED_QUEUES];


void studentInput (void) {

	int i;

	printmessage();

	/* Replace struct pi pInfo[i][] = NULL with process table information from the scheduler*/
	for(i=0;i<HISTORY;i++){
		strcpy(pInfo[i][0].p_name,"NOPTABCOPY"); /*Signal to the GUI that there are no process tables */
		pInfoPtrs[i] = &pInfo[i][0]; /* Give these pointers to the scheduler so it knows where to copy the process tables to*/
		pQhPtrs[i] = &pQh[i][0];
	}

	/* Uncomment the following line to run the test processes */
	procs(); 

	/*Run this code to make sure all procs all killed after the simulation is complete */
	/* for(i=0;i<PROCNUM;i++){
		kill(pid_array[i]);
	}*/
}
