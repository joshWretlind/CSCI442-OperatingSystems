#include "procs.h"
#include <stdlib.h>

void main(int argc, char *argv[]){
int i,j,files = 1000, iterations = 1000;
char *fileName = malloc(sizeof(char) * 100);
double ans = 300.0;

if (argc > 1){
	files = atoi(argv[0]);
	iterations = atoi(argv[1]);
	}

for(i=0; i<5000000; i++){
	ans = ans + 0.5;
	}

for(i=0; i<files;i++){
	FILE *fp;
	sprintf(fileName, "/home/procout/OSPEX_IO_INTENSIVE_OUTFILE_PROC5_%d",i); 	
	fp = fopen(fileName, "w");
	for(j=0;j<iterations;j++){
		fprintf(fp,"Writing to a file to make the OS scheduler wait for the hard drive\n");
	}
	fclose(fp);
}
}

