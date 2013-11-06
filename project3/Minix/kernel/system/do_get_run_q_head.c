#include "kernel/system.h"
#include <minix/endpoint.h>

// 
// Dear maintainer:
// 
// Once you are done trying to 'optimize' this routine,
// and have realized what a terrible mistake that was,
// please increment the following counter as a warning
// to the next guy:
// 
// total_hours_wasted_here = 42
// 

/*=================================================================*
 *                          do_get_run_q_head                      *
 * ================================================================*/
int do_get_run_q_head(struct proc *caller, message *m_ptr){
    return(OK);
}
