#include "ospex.h"
#include "glo.h"

void OSSendPtab(void){
	int i;
	if(recordSched == 1){
				struct pi sendPi[NR_PROCS + NR_TASKS];
				/*Use the following array to recover the next ready processes before we lose the addresses*/
				struct proc nextReady[NR_PROCS + NR_TASKS];
				struct proc tmpPtab[NR_PROCS +NR_TASKS];
				struct proc queuehds[NR_SCHED_QUEUES];

			if(pos_count < HISTORY ){

				/*Get the current process table */
				sys_getproctab((struct proc *) &tmpPtab);
			  	sys_cpuvar((char *) &queuehds,SELF);	

				/* Handle the heads of each queue */
				struct qh qh_send[NR_SCHED_QUEUES];

				for(i=0;i<NR_SCHED_QUEUES;i++){
					if(queuehds[i].p_priority!=-1){
						strcpy(qh_send[i].p_name,queuehds[i].p_name);
						qh_send[i].p_endpoint = queuehds[i].p_endpoint;
					}
					else{
						qh_send[i].p_endpoint = -1;
					}
				}

				for(i=0;i<(NR_PROCS+NR_TASKS);i++){
					strcpy(sendPi[i].p_name,tmpPtab[i].p_name);
					sendPi[i].p_endpoint = tmpPtab[i].p_endpoint;
					sendPi[i].p_priority = tmpPtab[i].p_priority;
					sendPi[i].p_cpu_time_left = tmpPtab[i].p_cpu_time_left;
					sendPi[i].p_rts_flags = tmpPtab[i].p_rts_flags;
						if(tmpPtab[i].p_nextready){
							sys_vircopy(SYSTEM,(vir_bytes) tmpPtab[i].p_nextready, SELF,(vir_bytes) &(nextReady[i]),sizeof(struct proc));
							strcpy(sendPi[i].p_nextready,nextReady[i].p_name);
							sendPi[i].p_nextready_endpoint = nextReady[i].p_endpoint;
						}
						else{
							strcpy(sendPi[i].p_nextready, NOPROC);
							sendPi[i].p_nextready_endpoint = -1;
						}
					/*Copy the accounting structure. Using CPU cycles instead of times, because CPU speeds will vary*/
					sendPi[i].p_times.enter_queue = tmpPtab[i].p_accounting.enter_queue;
					sendPi[i].p_times.time_in_queue = tmpPtab[i].p_accounting.time_in_queue;
					sendPi[i].p_times.dequeues = tmpPtab[i].p_accounting.dequeues;
					sendPi[i].p_times.ipc_sync = tmpPtab[i].p_accounting.ipc_sync;
					sendPi[i].p_times.ipc_async = tmpPtab[i].p_accounting.ipc_async;
					sendPi[i].p_times.preempted = tmpPtab[i].p_accounting.preempted;
				}	
				
				sys_vircopy(SELF,(vir_bytes) &sendPi, srcAddr,(vir_bytes) pInfoPtrs[pos_count],sizeof(sendPi));
				sys_vircopy(SELF,(vir_bytes) &qh_send, srcAddr,(vir_bytes) pQhPtrs[pos_count],sizeof(qh_send));
				int piReady = pos_count;
				sys_vircopy(SELF,(vir_bytes) &piReady, srcAddr, (vir_bytes) srcPtr2, sizeof(piReady));
				pos_count++; /* Ensure the proc history buffer does not overflow*/
			}
		}
}
