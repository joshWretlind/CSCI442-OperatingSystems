#include <sys/cdefs.h>
#include "namespace.h"
#include <lib.h>

#include <unistd.h>

#ifdef __weak_alias
__weak_alias(printmessage, _printmessage)
#endif

int printmessage() {
	message m;

  	return(_syscall(PM_PROC_NR, PRINTMESSAGE, &m));
}