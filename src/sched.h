#ifndef _SHIPYARD_SCHED_H
#define _SHIPYARD_SCHED_H

#define _GNU_SOURCE
#include <unistd.h>
#include <pthread.h>
#include <linux/unistd.h>
#include <linux/types.h>

#define gettid() syscall(__NR_gettid)

#define SCHED_DEADLINE 6

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
                  unsigned int flags);

int sched_getattr(pid_t pid,
                  struct sched_attr *attr,
                  unsigned int size,
                  unsigned int flags);

#endif /* _SHIPYARD_SHED_H */