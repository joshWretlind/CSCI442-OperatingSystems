/* This file contains the main program of the SCHED scheduler. It will sit idle
 * until asked, by PM, to take over scheduling a particular process.
 */

/* The _MAIN def indicates that we want the schedproc structs to be created
 * here. Used from within schedproc.h */
#define _MAIN
#include "sched.h"
#include "glo.h"
#include "schedproc.h"
/* Declare some local functions. */
static void reply(endpoint_t whom, message *m_ptr);
static void sef_local_startup(void);

struct machine machine;		/* machine info */

int call_count = 0; // Counts how many times OSSendPtab has been called
int pc_requested = 0; // Is true if the system call has been received, false after 50 iterations.
vir_bytes address_of_process_info; // Holds the address of pInfo from student.c
struct pi process_info[HISTORY][TOTALPROCS]; // holds the info gathered by sys_getproctab
char* p_info_pointers[HISTORY]; // holds the address of p_info_pointers, which is used by sys_vircopy
int user_proc_id = 0; // holds the process id of the user process

int pos_count;
int recordSched = 0; /*Tells the scheduler when to start recording ptabs */
/* The following variables are used to notify the user process GUI that the scheduler has recorded enough proc record */
int srcAddr,i;
char *srcPtr;
char *srcPtr2;
char *srcPtr3;
char *srcPtrQH;
char *srcPtrCpu;
struct pi *pInfoPtrs[HISTORY];	
struct qh *pQhPtrs[HISTORY];
/*===========================================================================*
 *				main					     *
 *===========================================================================*/
int main(void)
{
	/* Main routine of the scheduler. */
	message m_in;	/* the incoming message itself is kept here. */
	int call_nr;	/* system call number */
	int who_e;	/* caller's endpoint */
	int result;	/* result to system call */
	int rv;
	int s;

	/* SEF local startup. */
	sef_local_startup();

	if (OK != (s=sys_getmachine(&machine)))
		panic("couldn't get machine info: %d", s);
	/* Initialize scheduling timers, used for running balance_queues */
	init_scheduling();

	/* This is SCHED's main loop - get work and do it, forever and forever. */
	while (TRUE) {
		int ipc_status;

		/* Wait for the next message and extract useful information from it. */
		if (sef_receive_status(ANY, &m_in, &ipc_status) != OK)
			panic("SCHED sef_receive error");
		who_e = m_in.m_source;	/* who sent the message */
		call_nr = m_in.m_type;	/* system call number */

		/* Check for system notifications first. Special cases. */
		if (is_ipc_notify(ipc_status)) {
			switch(who_e) {
				case CLOCK:
					expire_timers(m_in.NOTIFY_TIMESTAMP);
					continue;	/* don't reply */
				default :
					result = ENOSYS;
			}

			goto sendreply;
		}

		switch(call_nr) {
		case SCHEDULING_INHERIT:
		case SCHEDULING_START:
			result = do_start_scheduling(&m_in);
			break;
		case SCHEDULING_STOP:
			result = do_stop_scheduling(&m_in);
			break;
		case SCHEDULING_SET_NICE:
			result = do_nice(&m_in);
			break;
		case SCHEDULING_NO_QUANTUM:
			/* This message was sent from the kernel, don't reply */
			if (IPC_STATUS_FLAGS_TEST(ipc_status,
				IPC_FLG_MSG_FROM_KERNEL)) {
				if ((rv = do_noquantum(&m_in)) != (OK)) {
					printf("SCHED: Warning, do_noquantum "
						"failed with %d\n", rv);
				}
				continue; /* Don't reply */
			}
			else {
				printf("SCHED: process %d faked "
					"SCHEDULING_NO_QUANTUM message!\n",
						who_e);
				result = EPERM;
			}
			break;
		case SCHED_TASK_CALL:

			printf("Hello from Sched Server\n");

			pc_requested = 1;
			address_of_process_info = (vir_bytes) m_in.m1_p1;
			user_proc_id = m_in.m1_i1;
			/**
/* For the brave souls who get this far: You are the chosen ones,
 * the valiant knights of programming who toil away, without rest,
 * fixing our most awful code. To you, true saviors, kings of men,
 * I say this: never gonna give you up, never gonna let you down,
 * never gonna run around and desert you. Never gonna make you cry,
 * never gonna say goodbye. Never gonna tell a lie and hurt you.
 */
			break;
		default:
			result = no_sys(who_e, call_nr);
		}

sendreply:
		/* Send reply. */
		if (result != SUSPEND) {
			m_in.m_type = result;  		/* build reply message */
			reply(who_e, &m_in);		/* send it away */
		}
 	}
	return(OK);
}

/*===========================================================================*
 *				reply					     *
 *===========================================================================*/
static void reply(endpoint_t who_e, message *m_ptr)
{
	int s = send(who_e, m_ptr);    /* send the message */
	if (OK != s)
		printf("SCHED: unable to send reply to %d: %d\n", who_e, s);
}

/*===========================================================================*
 *			       sef_local_startup			     *
 *===========================================================================*/
static void sef_local_startup(void)
{
	/* No init callbacks for now. */
	/* No live update support for now. */
	/* No signal callbacks for now. */

	/* Let SEF perform startup. */
	sef_startup();
}
