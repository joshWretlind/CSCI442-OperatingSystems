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

int pos_count;
int recordSched = 0; /*Tells the scheduler when to start recording ptabs */
/* The following variables are used to notify the user process GUI that the scheduler has recorded enough proc record */
int srcAddr,i;
char *srcPtr;
char *srcPtr2;
char *srcPtr3;
char *srcPtrQH;
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
		case START_RECORDING:
			if(m_in.m1_i3 == -1)
				recordSched = 0;
			else{
				srcAddr = m_in.m1_i2;
				srcPtr = m_in.m1_p1;	
				sys_vircopy(srcAddr,(vir_bytes) srcPtr, SELF,(vir_bytes) &pInfoPtrs, sizeof(pInfoPtrs));
				srcPtr2 = m_in.m1_p2;
				srcPtr3 = m_in.m1_p3;
				srcPtrQH = m_in.m2_p1;
				sys_vircopy(srcAddr,(vir_bytes) srcPtrQH, SELF,(vir_bytes) &pQhPtrs, sizeof(pQhPtrs));
				recordSched = 1;
				pos_count =0;

			}
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
