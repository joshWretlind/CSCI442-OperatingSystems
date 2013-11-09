#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <minix/syslib.h>
#include <minix/callnr.h>
#include <unistd.h>
#include <minix/ipc.h>
#include <minix/safecopies.h>
#include <minix/vm.h>
#include <minix/u64.h>
#include <minix/endpoint.h>
#include <minix/param.h>
#include <minix/com.h>
#include <minix/type.h>

#define ALL_PROCS (NR_PROCS+NR_TASKS) 
#define HISTORY 50 

/* Bits for the runtime flags. A process is runnable iff p_rts_flags == 0. */
#define RTS_SLOT_FREE	0x01	/* process slot is free */
#define RTS_PROC_STOP	0x02	/* process has been stopped */
#define RTS_SENDING	0x04	/* process blocked trying to send */
#define RTS_RECEIVING	0x08	/* process blocked trying to receive */
#define RTS_SIGNALED	0x10	/* set when new kernel signal arrives */
#define RTS_SIG_PENDING	0x20	/* unready while signal being processed */
#define RTS_P_STOP	0x40	/* set when process is being traced */
#define RTS_NO_PRIV	0x80	/* keep forked system process from running */
#define RTS_NO_ENDPOINT	0x100	/* process cannot send or receive messages */
#define RTS_VMINHIBIT	0x200	/* not scheduled until pagetable set by VM */
#define RTS_PAGEFAULT	0x400	/* process has unhandled pagefault */
#define RTS_VMREQUEST	0x800	/* originator of vm memory request */
#define RTS_VMREQTARGET	0x1000	/* target of vm memory request */
#define RTS_PREEMPTED	0x4000	/* this process was preempted by a higher
				   priority process and we should pick a new one
				   to run. Processes with this flag should be
				   returned to the front of their current
				   priority queue if they are still runnable
				   before we pick a new one
				 */
#define RTS_NO_QUANTUM	0x8000	/* process ran out of its quantum and we should
				   pick a new one. Process was dequeued and
				   should be enqueued at the end of some run
				   queue again */
#define RTS_BOOTINHIBIT	0x10000	/* not ready until VM has made it */

int startsim(void);
