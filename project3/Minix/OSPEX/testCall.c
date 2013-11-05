#include "student.h"
#include <stdio.h>
int main(int argc, char** args) {
	struct pi pInfo[HISTORY][ALL_PROCS];
	int i = obtain_proctable((char*) &pInfo);
	return 0;
}