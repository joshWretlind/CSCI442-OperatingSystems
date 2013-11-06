#include <sys/cdefs.h>
#include <lib.h>
#include <minix/syslib.h>
#include <unistd.h>
#include <stdio.h>

static inline int sched_task_call(char* proc, int user_proc_id) {
	message m;

	m.m1_p1 = proc;
	m.m1_i1 = user_proc_id;

  	return(_taskcall(SCHED_PROC_NR, SCHED_TASK_CALL, &m));
}