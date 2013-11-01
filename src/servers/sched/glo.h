#include <minix/pi.h> 

extern int pos_count;
extern int recordSched;
extern int srcAddr;
extern char *srcPtr;
extern char *srcPtr2;
extern char *srcPtr3;
extern char *srcPtrCpu;
extern struct pi pInfo[NR_TASKS+NR_PROCS];
extern struct pi *pInfoPtrs[HISTORY];
extern struct qh *pQhPtrs[HISTORY];
extern int debug_trigger;
