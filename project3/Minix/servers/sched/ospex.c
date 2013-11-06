#include "ospex.h"
#include "glo.h"
#include "sched.h"

void OSSendPtab(void) {
		
		printf("Count:%d", call_count);
		printf("\n");

		printf("TOTALPROCS: %d", TOTALPROCS);
		printf("\n");
		static struct proc processes[TOTALPROCS];
		printf("processes size: %d", sizeof(processes));
		printf("\n");

		// After this call, processes holds the process table
		sys_getproctab(processes);
		printf("System call complete\n");

		/* Replace struct pi pInfo[i][] = NULL with process table information from the scheduler*/
		for ( int i = 0; i < TOTALPROCS; i++ ) {
			//So I heard you liek assigning things
			strcpy(process_info[call_count][i].p_name, processes[i].p_name);
			printf("p_name copied\n");
			process_info[call_count][i].p_endpoint = processes[i].p_endpoint;
			printf("p_endpoint copied\n");
			process_info[call_count][i].p_priority = processes[i].p_priority;
			printf("p_priority copied\n");
			process_info[call_count][i].p_cpu_time_left = processes[i].p_cpu_time_left;
			printf("p_cpu_time_left copied\n");
			process_info[call_count][i].p_rts_flags = processes[i].p_rts_flags;

			printf("p_rts_flags copied\n");

			if ( processes[i].p_nextready == NULL ) {
				printf("p_nextready is null\n");
				strcpy(process_info[call_count][i].p_nextready, "NULL");
				process_info[call_count][i].p_nextready_endpoint = 0;
			} else {
				strcpy(process_info[call_count][i].p_nextready, processes[i].p_nextready->p_name);
				process_info[call_count][i].p_nextready_endpoint = processes[i].p_nextready->p_endpoint;
			}
			printf("p_nextready copied\n");
			printf("p_nextready_endpoint copied\n");

			process_info[call_count][i].p_user_time = processes[i].p_user_time;
			printf("p_user_time copied\n");
			process_info[call_count][i].p_sys_time = processes[i].p_sys_time;
			printf("p_sys_time copied\n");
			process_info[call_count][i].p_cycles = processes[i].p_cycles;
			printf("p_cycles copied\n");
			printf("hello\n");
			// Assign individually
			process_info[call_count][i].p_times.enter_queue = processes[i].p_accounting.enter_queue;
			printf("enter_queue copied\n");
			process_info[call_count][i].p_times.time_in_queue = processes[i].p_accounting.time_in_queue;
			printf("time_in_queue copied\n");
			process_info[call_count][i].p_times.dequeues = processes[i].p_accounting.dequeues;
			printf("dequeues copied\n");
			process_info[call_count][i].p_times.ipc_sync = processes[i].p_accounting.ipc_sync;
			printf("ipc_sync copied\n");
			process_info[call_count][i].p_times.ipc_async = processes[i].p_accounting.ipc_async;
			printf("ipc_async copied\n");
			process_info[call_count][i].p_times.preempted = processes[i].p_accounting.preempted;
			printf("preempted copied\n");
			//Hour 30: The Minix code seems to be rejecting my attempts at friendship
		}
		//Annnnd it's gone.
}
