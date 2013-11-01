#ifndef _MINIX_GETPROC_H
#define _MINIX_GETPROC_H

#include<servers/pm/mproc.h>

struct mproc getMProc(pid_t mp_pid);

#endif
