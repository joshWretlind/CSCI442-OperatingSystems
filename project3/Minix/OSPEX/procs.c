#include "procs.h"


void procs(void){

int i;
pid_t pid, child_pid;

	for(i=0;i<PROCNUM;i++){
		pid = fork();

		if(pid == -1){
			printf("There was an error forking process: %d\n",i);
			break;
		}
		else if(pid == 0){
			switch(i){
				case(0): 
					execl("./proc1","10000000");
					break;
				case(1):
					execl("./proc2",NULL);
					break;
				case(2):
					execl("./proc3",NULL);
					break;
				case(3):
					execl("./proc4",NULL);
					break;
				case(4):
					execl("./proc5",NULL);
					break;
				case(5):
					execl("./proc6",NULL);
					break;
				case(6):
					execl("./proc7",NULL);
					break;
				case(7):
					execl("./proc8",NULL);
					break;
				case(8):
					execl("./proc9",NULL);
					break;
				case(9):
					execl("./proc10",NULL);
					break;
			}
				break;
		}	
		else{
			pid_array[i] = pid; /*Store the child's PID in the global variable for use in the scheduler GUI*/
			printf("PID stored in array position %d: %d\n",i,pid_array[i]);
		}
	}	
				
}
