#include <minix/config.h>
#include <minix/endpoint.h>
#include <paths.h>
#include <minix/procfs.h>
#include <limits.h>
#include <sys/types.h>

#include <minix/const.h>
#include <minix/type.h>
#include <minix/dmap.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <ttyent.h>
#include "mproc.h"
#include "proto.h"

struct pstat {			/* structure filled by pstat() */
  struct pstat *ps_next;	/* next in process list */
  int ps_task;			/* is this process a task or not? */
  int ps_endpt;			/* process endpoint (NONE means unused slot) */
  dev_t ps_dev;			/* major/minor of controlling tty */
  uid_t ps_ruid;		/* real uid */
  uid_t ps_euid;		/* effective uid */
  pid_t ps_pid;			/* process id */
  pid_t ps_ppid;		/* parent process id */
  int ps_pgrp;			/* process group id */
  char ps_state;		/* process state */
  char ps_pstate;		/* sleep state */
  char ps_fstate;		/* VFS block state */
  int ps_ftask;			/* VFS suspend task (endpoint) */
  vir_bytes ps_memory;		/* memory usage */
  int ps_recv;			/* process number to receive from (endpoint) */
  time_t ps_utime;		/* accumulated user time */
  time_t ps_stime;		/* accumulated system time */
  char ps_name[PROC_NAME_LEN+1];/* process name */
  char *ps_args;		/* concatenated argument string */
};

struct pstat *ptable;

/* Function declerations*/
static void getkinfo(void);
void err(const char *s );

int nr_tasks, nr_procs;

void getMProc(){

struct mproc *tmpBuf;

getkinfo();
tmpBuf = find_proc(1);
}

void plist(void)
{
  DIR *p_dir;
  struct dirent *p_ent;
  struct pstat pbuf;
  pid_t pid;
  char *end;
  unsigned int slot;

  /* Allocate a table for process information. Initialize all slots' endpoints
   * to NONE, indicating those slots are not used.
   */
  if ((ptable = malloc((nr_tasks + nr_procs) * sizeof(struct pstat))) == NULL)
	err("Out of memory!");

  for (slot = 0; slot < nr_tasks + nr_procs; slot++)
	ptable[slot].ps_endpt = NONE;

  /* Fill in the table slots for all existing processes, by retrieving all PID
   * entries from the /proc directory.
   */
  p_dir = opendir(".");

  if (p_dir == NULL) err("Can't open " _PATH_PROC);

  p_ent = readdir(p_dir);
  while (p_ent != NULL) {
	pid = strtol(p_ent->d_name, &end, 10);

	if (!end[0] && pid != 0 && !pstat(&pbuf, pid)) {
		slot = SLOT_NR(pbuf.ps_endpt);

		if (slot < nr_tasks + nr_procs)
			memcpy(&ptable[slot], &pbuf, sizeof(pbuf));
	}

	p_ent = readdir(p_dir);
  }

  closedir(p_dir);
}


static void getkinfo(void)
{
	FILE *fp;

	if ((fp = fopen("kinfo", "r")) == NULL)
		err("Unable to open " _PATH_PROC "kinfo");

	if (fscanf(fp, "%u %u", &nr_procs, &nr_tasks) != 2)
		err("Unable to read from " _PATH_PROC "kinfo");

	fclose(fp);
}


void err(const char *s)
{
  extern int errno;

  if (errno == 0)
	fprintf(stderr, "ps: %s\n", s);
  else
	fprintf(stderr, "ps: %s: %s\n", s, strerror(errno));

  exit(2);
}
