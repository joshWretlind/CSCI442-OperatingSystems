#include "syslib.h"

int sys_cpuvar(char *qh_ptr, int sendEndpoint){

	message m;
	m.m1_i1 = sendEndpoint;
	m.m1_p1 = qh_ptr;
	
	return(_kernel_call(SYS_CPUVAR, &m));
}
