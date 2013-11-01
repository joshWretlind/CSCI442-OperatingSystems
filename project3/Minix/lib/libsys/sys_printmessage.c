#include "lib.h"
#include "unistd.h"
#include "syslib.h"

int printmessage(void) {
	message m;
	return _syscall(PM_PROC_NR, 69, &m);
}