#include "procs.h"
#include <stdlib.h>

void main(int argc, char *argv[]){
int i,j,files = 1000, iterations = 1000;
char *fileName = malloc(sizeof(char) * 34);
double ans = 3.0;

if (argc > 1){
	files = atoi(argv[0]);
	iterations = atoi(argv[1]);
	}

FILE *fp;
	sprintf(fileName, "/home/procout/OSPEX_PROC5"); 	
	fp = fopen(fileName, "w");

for(i=0; i<5000000; i++){
	ans = ans * 10.0;

			fprintf(fp,"The answer is: %l\n",ans);
}
	fclose(fp);
}

