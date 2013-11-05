#include <sys/cdefs.h>
#include <lib.h>

#include <unistd.h>

static inline int obtain_proctable(char* proc) {
	message m;

	m.m1_p1 = proc;

  	return(_syscall(PM_PROC_NR, OBTAIN_PROCTABLE, &m));
}