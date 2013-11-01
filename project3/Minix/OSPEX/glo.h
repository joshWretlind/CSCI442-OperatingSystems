#include <minix/pi.h>

/* Do not modify this file */
extern struct pi *pInfoPtrs[HISTORY];
extern struct pi pInfo[HISTORY][ALL_PROCS];
extern u64_t cpuFreq;
extern struct qh *pQhPtrs[HISTORY];
extern struct qh pQh[HISTORY][NR_SCHED_QUEUES];
