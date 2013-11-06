#include "ospex.h"
#include "glo.h"
#include "sched.h"

void OSSendPtab(void) {

		printf("Count:%d", call_count);
		printf("\n");

		struct proc processes[TOTALPROCS];

		// After this call, processes holds the process table
		sys_getproctab(&processes);

		/* Replace struct pi pInfo[i][] = NULL with process table information from the scheduler*/
		for ( int i = 0; i < TOTALPROCS; i++ ) {
			strcpy(process_info[call_count][i].p_name, processes[i].p_name);
			process_info[call_count][i].p_endpoint = processes[i].p_endpoint;
			process_info[call_count][i].p_priority = processes[i].p_priority;
			process_info[call_count][i].p_cpu_time_left = processes[i].p_cpu_time_left;
			process_info[call_count][i].p_rts_flags = processes[i].p_rts_flags;

			strcpy(process_info[call_count][i].p_nextready, (const char*) processes[i].p_nextready);
			process_info[call_count][i].p_nextready_endpoint = processes[i].p_nextready->p_endpoint;
			
			process_info[call_count][i].p_user_time = processes[i].p_user_time;
			process_info[call_count][i].p_sys_time = processes[i].p_sys_time;
			process_info[call_count][i].p_cycles = processes[i].p_cycles;

			// Assign individually
			process_info[call_count][i].p_times.enter_queue = processes[i].p_accounting.enter_queue;
			process_info[call_count][i].p_times.time_in_queue = processes[i].p_accounting.time_in_queue;
			process_info[call_count][i].p_times.dequeues = processes[i].p_accounting.dequeues;
			process_info[call_count][i].p_times.ipc_sync = processes[i].p_accounting.ipc_sync;
			process_info[call_count][i].p_times.ipc_async = processes[i].p_accounting.ipc_async;
			process_info[call_count][i].p_times.preempted = processes[i].p_accounting.preempted;

		}
}
