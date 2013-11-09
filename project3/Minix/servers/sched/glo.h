#include <minix/pi.h> 
#ifndef _SCHED_GLO_H
#define _SCHED_GLO_H

struct sjf{
	char p_name[PROC_NAME_LEN];
	endpoint_t p_endpoint;
	unsigned long predBurst;
	};
#define PROCNUM 10 
#define ALPHA 0.5
#endif
extern int pos_count;
extern int recordSched;
extern int srcAddr;
extern char *srcPtr;
extern char *srcPtr2;
extern char *srcPtr3;
extern struct pi pInfo[NR_TASKS+NR_PROCS];
extern struct pi *pInfoPtrs[HISTORY];
extern struct qh *pQhPtrs[HISTORY];
extern int debug_trigger;
extern struct sjf sjf[PROCNUM];
