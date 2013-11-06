#include "ospex.h"
#include "glo.h"
#include "sched.h"

void OSSendPtab(void) {

		printf("Count:%d", call_count);
		printf("\n");

		static struct proc processes[TOTALPROCS];

		// After this call, processes holds the process table
		sys_getproctab(processes);
		printf("System call complete");

		/* Replace struct pi pInfo[i][] = NULL with process table information from the scheduler*/
		for ( int i = 0; i < TOTALPROCS; i++ ) {
			strcpy(process_info[call_count][i].p_name, processes[i].p_name);
			printf("p_name copied");
			process_info[call_count][i].p_endpoint = processes[i].p_endpoint;
			printf("p_endpoint copied");
			process_info[call_count][i].p_priority = processes[i].p_priority;
			printf("p_priority copied");
			process_info[call_count][i].p_cpu_time_left = processes[i].p_cpu_time_left;
			printf("p_cpu_time_left copied");
			process_info[call_count][i].p_rts_flags = processes[i].p_rts_flags;
			printf("p_rts_flags copied");

			strcpy(process_info[call_count][i].p_nextready, (const char*) processes[i].p_nextready);
			printf("p_nextready copied");
			process_info[call_count][i].p_nextready_endpoint = processes[i].p_nextready->p_endpoint;
			printf("p_nextready_endpoint copied");

			process_info[call_count][i].p_user_time = processes[i].p_user_time;
			printf("p_user_time copied");
			process_info[call_count][i].p_sys_time = processes[i].p_sys_time;
			printf("p_sys_time copied");
			process_info[call_count][i].p_cycles = processes[i].p_cycles;
			printf("p_cycles copied");

			// Assign individually
			process_info[call_count][i].p_times.enter_queue = processes[i].p_accounting.enter_queue;
			process_info[call_count][i].p_times.time_in_queue = processes[i].p_accounting.time_in_queue;
			process_info[call_count][i].p_times.dequeues = processes[i].p_accounting.dequeues;
			process_info[call_count][i].p_times.ipc_sync = processes[i].p_accounting.ipc_sync;
			process_info[call_count][i].p_times.ipc_async = processes[i].p_accounting.ipc_async;
			process_info[call_count][i].p_times.preempted = processes[i].p_accounting.preempted;

		}
}
