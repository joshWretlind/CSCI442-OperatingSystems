#include "ospex.h"
#include "glo.h"

int count = 0;

void OSSendPtab(void) {

	if ( count < 50 ) {
		struct pi pInfo[HISTORY][ALL_PROCS];
		sys_getproctab(&pInfo[count]);

		// Copy pInfo back to the user process

		count++;
	}

}
