#include <minix/endpoint.h>


/* Accounting statistics that get passed to the process' scheduler */
  struct p_accounting{
	u64_t enter_queue;	/* time when enqueued (cycles) */
	u64_t time_in_queue;	/* time spent in queue */
	unsigned long dequeues;
	unsigned long ipc_sync;
	unsigned long ipc_async;
	unsigned long preempted;
  };

struct pi {
	char p_name[PROC_NAME_LEN];
	endpoint_t p_endpoint;
	char p_priority;
	u64_t p_cpu_time_left;
	u32_t p_rts_flags;
	int queue_head;
	char p_nextready[PROC_NAME_LEN];
	endpoint_t p_nextready_endpoint;
	struct p_accounting p_times
	};

#define NOPROC "NOPROC"

/*Structure for passing the processes at the head of each queue from the kernel to the scheduler*/
struct qh{
	char p_name[PROC_NAME_LEN];
	endpoint_t p_endpoint;
};
