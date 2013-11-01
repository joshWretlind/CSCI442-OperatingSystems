#include <stdio.h>
#include <unistd.h>

#ifndef PROCS_H
#define PROCS_H

void procs(void);

#define PROCNUM 10 
extern pid_t pid_array[PROCNUM];
/*Array for storing the proc numbers of forked processes. This is used to filter the procs shown by the GUI*/
pid_t pid_array[PROCNUM];
#endif
