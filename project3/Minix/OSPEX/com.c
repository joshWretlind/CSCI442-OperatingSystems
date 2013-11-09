#include "com.h"
#include <minix/u64.h>
#include "glo.h"
#include "procs.h"

struct pi *pInfoPtrs[HISTORY];
/* qh is queue heads and will hold the process at the top of each priority queue*/
struct qh *pQhPtrs[HISTORY];
struct pi pInfo[HISTORY][ALL_PROCS];
struct qh pQh[HISTORY][NR_SCHED_QUEUES];

/*Recursive function decleration */
void printQ (struct pi *procPtr,
	     int endpoint,
	     FILE *fp);

int startsim(void){

message m;
int i,j=0,piReady = -1;
FILE *fp;
fp = fopen("/home/out","w");

for(i=0;i<HISTORY;i++){
	pInfoPtrs[i] = (struct pi *) &pInfo[i][0]; 
}
for(i=0;i<HISTORY;i++){
	pQhPtrs[i] = (struct qh*) &pQh[i][0];
}

/* Copy the pointer arrays so that you can go backward and forward through the history */
struct pi *pInfoPtrsCopy[HISTORY];
struct qh *pQhPtrsCopy[HISTORY];
for(i=0;i<HISTORY;i++){
	pInfoPtrsCopy[i] = pInfoPtrs[i];
	pQhPtrsCopy[i] = pQhPtrs[i];
}
m.m1_p1 = (char *) &pInfoPtrs;
m.m1_p2 = (char *) &piReady;
m.m1_i2 = SELF;
m.m1_i3 = HISTORY;
m.m2_p1 = (char *) &pQhPtrs;

int error = _syscall(PM_PROC_NR,STARTRECORD,&m);
procs();
for(j;j<HISTORY;j++){
		while(piReady < j){
		}
		printf("Simulation is %d%% complete\n",(j*2)+2);
		fprintf(fp,"Proc Table %d\n\n",j);
		fprintf(fp,"Queue heads: ");
		for(i=0;i<NR_SCHED_QUEUES;i++){
				if(pQhPtrsCopy[j]->p_endpoint!=-1){
					fprintf(fp,"Queue: %d %d ",i,pQhPtrsCopy[j]->p_endpoint);
				}
				pQhPtrsCopy[j]++;
		}
		fprintf(fp,"\n\n");
		pQhPtrsCopy[j] = pQhPtrs[j];
	
	/*Write out the runable queues in order */
	for(i=0; i<NR_SCHED_QUEUES; i++){
			fprintf(fp,"Priority Queue %d: ",i);
			if(pQhPtrsCopy[j]->p_endpoint != -1){
				printQ(pInfoPtrsCopy[j],pQhPtrsCopy[j]->p_endpoint,fp);
			}
			else{
				fprintf(fp,"\n");
			}
			pQhPtrsCopy[j]++;
	}
	pQhPtrsCopy[j] = pQhPtrs[j]; /* Reset the Qh Pointers */

	for (i=0;i<ALL_PROCS;i++){ 
		if (!(pInfoPtrsCopy[j]->p_rts_flags == RTS_SLOT_FREE)) 
		fprintf(fp,"Process: %s, Endpoint: %d, Enter queue: %lu%lu, Time in Queue: %lu%lu, Dequeues: %lu, IPC Sync: %lu, IPC Async: %lu,Preempted: %lu,RTS: %x\n\t\t, Priority: %d, Next: %s Endpoint: %d\n",
				pInfoPtrsCopy[j]->p_name,pInfoPtrsCopy[j]->p_endpoint,ex64hi(pInfoPtrsCopy[j]->p_times.enter_queue),ex64lo(pInfoPtrsCopy[j]->p_times.enter_queue),
				ex64hi(pInfoPtrsCopy[j]->p_times.time_in_queue),ex64lo(pInfoPtrsCopy[j]->p_times.time_in_queue),
				pInfoPtrsCopy[j]->p_times.dequeues,pInfoPtrsCopy[j]->p_times.ipc_sync,pInfoPtrsCopy[j]->p_times.ipc_async,
				pInfoPtrsCopy[j]->p_times.preempted,pInfoPtrsCopy[j]->p_rts_flags,pInfoPtrsCopy[j]->p_priority, pInfoPtrsCopy[j]->p_nextready,
				pInfoPtrsCopy[j]->p_nextready_endpoint);
		pInfoPtrsCopy[j]++;
	}
	
}

m.m1_i3 = -1;
_syscall(PM_PROC_NR,STARTRECORD,&m);
return(0);
}

void printQ (struct pi *procPtr,
	     int endpoint,
	     FILE *fp){

/*This is probably unnecessary, but I'm creating a copy of the pointer to the head of the list */
struct pi *start = procPtr;
struct pi *cpy = procPtr;

/*Find the process that was the nextready process in the proc table*/
	while(cpy->p_endpoint != endpoint){
		cpy++;
	}

/* Print the process to the file, then see if there is another process in the nextready spot. If yes, recursively call this routine. If no, write a line feed for the next queue */
fprintf(fp,"Process: %s, enpoint %d -> ",cpy->p_name,cpy->p_endpoint);
	if(cpy->p_nextready_endpoint != -1){
		/*printf("Start pointer: %p, copy pointer: %p\n",start,cpy);*/
		printQ(start,cpy->p_nextready_endpoint,fp);
	}
	else{
		fprintf(fp,"\n");
	}
}
