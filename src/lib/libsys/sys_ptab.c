#include "syslib.h"

int sys_ptab(){

int *testPtr = NULL;

int trash = sys_getproc(testPtr, 2);

return 0;
}
