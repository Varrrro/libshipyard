#define _GNU_SOURCE
#include "shipyard.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/unistd.h>
#include <linux/types.h>
#include <linux/sched.h>

#define gettid() syscall(__NR_gettid)

struct sched_attr
{
    __u32 size;

    __u32 sched_policy;
    __u64 sched_flags;

    /* SCHED_NORMAL, SCHED_BATCH */
    __s32 sched_nice;

    /* SCHED_FIFO, SCHED_RR */
    __u32 sched_priority;

    /* SCHED_DEADLINE (nsec) */
    __u64 sched_runtime;
    __u64 sched_deadline;
    __u64 sched_period;
};

int sched_setattr(pid_t pid,
                  const struct sched_attr *attr,
                  unsigned int flags)
{
    return syscall(__NR_sched_setattr, pid, attr, flags);
}

int sched_getattr(pid_t pid,
                  struct sched_attr *attr,
                  unsigned int size,
                  unsigned int flags)
{
    return syscall(__NR_sched_getattr, pid, attr, size, flags);
}

int set_sched()
{
    struct sched_attr attr;
    int runtime;
    int deadline;
    int period;
    int ret;

    runtime = atoi(getenv("TASK_RUNTIME"));
    deadline = atoi(getenv("TASK_DEADLINE"));
    period = atoi(getenv("TASK_PERIOD"));

    attr.size = sizeof(attr);
    attr.sched_flags = 0;
    attr.sched_nice = 0;
    attr.sched_priority = 0;
    attr.sched_policy = SCHED_DEADLINE;
    attr.sched_runtime = runtime;
    attr.sched_deadline = deadline;
    attr.sched_period = period;

    ret = sched_setattr(gettid(), &attr, 0);
    if (ret < 0)
    {
        return -1;
    }

    return 0;
}
