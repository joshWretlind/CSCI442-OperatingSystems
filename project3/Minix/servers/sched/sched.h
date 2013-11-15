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

extern struct machine machine;		/* machine info */

#define TOTALPROCS NR_TASKS + NR_PROCS 
#define HISTORY 50 
