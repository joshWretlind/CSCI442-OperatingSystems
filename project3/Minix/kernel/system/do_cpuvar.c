#include "kernel/kernel.h"
#include <minix/syslib.h>
#include <minix/pi.h>

int do_cpuvar(struct proc *caller_ptr, message *m_ptr){

char *p_pi_ptr = m_ptr->m1_p1;
int i;
struct proc **queueHeadPtr = NULL;
struct proc qh_send[NR_SCHED_QUEUES];
struct proc nullProc;

queueHeadPtr = get_cpu_var(0,run_q_head);

nullProc.p_priority = -1;

for(i=0; i<NR_SCHED_QUEUES; i++){
	qh_send[i] = nullProc;
}
for(i=0; i<NR_SCHED_QUEUES; i++){
	if(queueHeadPtr[i]){
		qh_send[i] = *queueHeadPtr[i];
	}
}

data_copy_vmcheck(caller_ptr, KERNEL,(vir_bytes) &qh_send, caller_ptr->p_endpoint,(vir_bytes) p_pi_ptr, sizeof(struct proc)*NR_SCHED_QUEUES);

return(OK);
}
