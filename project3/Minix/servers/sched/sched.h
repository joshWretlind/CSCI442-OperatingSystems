/* This is the master header for the Scheduler.  It includes some other files
 * and defines the principal constants.
 */
#define _POSIX_SOURCE      1	/* tell headers to include POSIX stuff */
#define _MINIX             1	/* tell headers to include MINIX stuff */
#define _SYSTEM            1	/* tell headers that this is the kernel */

/* The following are so basic, all the *.c files get them automatically. */
#include <minix/config.h>	/* MUST be first */
#include <sys/types.h>
#include <minix/const.h>
#include <minix/type.h>

#include <fcntl.h>
#include <unistd.h>
#include <minix/syslib.h>
#include <minix/sysutil.h>
#include <minix/timers.h>
#include <minix/param.h>

#include <limits.h>
#include <errno.h>
#include <sys/param.h>
#include <machine/archtypes.h>

#include "proto.h"
#include "kernel/proc.h" /* for queue constants */
#include <string.h>
#include <minix/pi.h>

extern struct machine machine;		/* machine info */

#define TOTALPROCS NR_TASKS + NR_PROCS
#define HISTORY 50

/* CHANGES FOR OS CLASS */

// The following information is needed for sys_vircopy so that we can get the info from the process
// table and pass it back to the user process

extern int call_count; // Counts how many times OSSendPtab has been called
extern int pc_requested; // Is true if the system call has been received, false after 50 iterations.
extern vir_bytes address_of_process_info; // Holds the address of pInfo from student.c
extern struct pi process_info[HISTORY][TOTALPROCS]; // holds the info gathered by sys_getproctab
extern char* p_info_pointers[HISTORY]; // holds the address of p_info_pointers, which is used by sys_vircopy
extern int user_proc_id; // holds the process id of the user process
