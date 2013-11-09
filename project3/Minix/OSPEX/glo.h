#include <minix/pi.h>

extern struct pi *pInfoPtrs[HISTORY];
extern struct pi pInfo[HISTORY][ALL_PROCS];
struct qh *pQhPtrs[HISTORY];
struct qh pQh[HISTORY][NR_SCHED_QUEUES];
