if(recordSched == 1){
				struct pi sendPi[NR_PROCS + NR_TASKS];
				/*Use the following array to recover the next ready processes before we lose the addresses*/
				struct proc nextReady[NR_PROCS + NR_TASKS];
				struct proc tmpPtab[NR_PROCS +NR_TASKS];

			if(pos_count < HISTORY ){

				/*Get the current process table */
				sys_getproctab((struct proc *) &tmpPtab);
				for(i=0;i<(NR_PROCS+NR_TASKS);i++){
					strcpy(sendPi[i].p_name,tmpPtab[i].p_name);
					sendPi[i].p_endpoint = tmpPtab[i].p_endpoint;
					sendPi[i].p_priority = tmpPtab[i].p_priority;
					sendPi[i].p_cpu_time_left = tmpPtab[i].p_cpu_time_left;
					sendPi[i].p_rts_flags = tmpPtab[i].p_rts_flags;
						if(tmpPtab[i].p_nextready){
							sys_vircopy(SYSTEM,(vir_bytes) tmpPtab[i].p_nextready, SELF,(vir_bytes) &(nextReady[i]),sizeof(struct proc));
							strcpy(sendPi[i].p_nextready,nextReady[i].p_name);
							sendPi[i].p_nextready_endpoint = nextReady[i].p_endpoint;
						}
						else{
							strcpy(sendPi[i].p_nextready, NOPROC);
							sendPi[i].p_nextready_endpoint = -1;
						}
				}	
				sys_vircopy(SELF,(vir_bytes) &sendPi, srcAddr,(vir_bytes) pInfoPtrs[pos_count],sizeof(sendPi));
				int piReady = pos_count;
				sys_vircopy(SELF,(vir_bytes) &piReady, srcAddr, (vir_bytes) srcPtr2, sizeof(piReady));
				pos_count++; /* Ensure the proc history buffer does not overflow*/

			}
			else{
					/*Prevent the scheduler from continuing to record processes, and reset variables for another record cycle*/
			}
		}

