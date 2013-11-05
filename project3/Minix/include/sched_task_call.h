#include <sys/cdefs.h>
#include <lib.h>
#include <minix/syslib.h>
#include <unistd.h>
#include <stdio.h>

static inline int sched_task_call() {
	message m;
	printf("inside sched_task_call()");
  	return(_taskcall(SCHED_PROC_NR, SCHED_TASK_CALL, &m));
}