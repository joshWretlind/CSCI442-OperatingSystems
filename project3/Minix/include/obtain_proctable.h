#include <sys/cdefs.h>
#include <lib.h>

#include <unistd.h>

static inline int obtain_proctable() {
	message m;
  	return(_syscall(PM_PROC_NR, PRINTMESSAGE, &m));
}