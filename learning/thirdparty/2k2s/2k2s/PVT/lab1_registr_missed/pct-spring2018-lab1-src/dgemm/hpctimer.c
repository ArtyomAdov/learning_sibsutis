/*
 * hpctimer.c: High-Resolution timers library.
 *
 * Copyright (C) 2010 Mikhail Kurnosov <mkurnosov@gmail.com>
 *
 * TODO:
 * - gettimeofday timer
 * - doxygen
 * - add rdtscp for core2duo
 */

#if defined(__gnu_linux__) || defined(linux)
#if 0
#define __USE_GNU
#define _GNU_SOURCE
#include <sched.h>	/* for sched_*() */
#include <utmpx.h>	/* for sched_getcpu() */
#endif
#endif

#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>

#include "hpctimer.h"

#if defined(__GNUC__)
#	define __inline__ __inline__
#	define __asm__ __asm__
#	define __volatile__ __volatile__
#elif defined(__SUNPRO_C)
#	define __inline__ __inline__
#	define __asm__ __asm__
#	define __volatile__ __volatile__
#endif

typedef hpctimer_time_t (*gettime_func_t)();

struct hpctimer {
	hpctimer_type_t type;
	int flags;
	hpctimer_time_t overhead;	/* Overhead of reading timer */
	uint64_t freq;              /* Timer frequency (ticks per usec) */
	gettime_func_t gettime;
#if 0
	cpu_set_t cpuset;			/* Original cpuset of the current process */
#endif
};

static hpctimer_t hpctimer_global_timer;
static int hpctimer_is_global_timer_initialized = 0;

static __inline__ hpctimer_time_t hpctimer_gettsc();
static int hpctimer_tsctimer_init(hpctimer_t *timer);
static int hpctimer_set_cpuaffinity(hpctimer_t *timer);
static int hpctimer_restore_cpuaffinity(hpctimer_t *timer);
static int hpctimer_timer_initialize(hpctimer_t *timer,
                                     hpctimer_type_t type, int flags);
static int hpctimer_timer_finalize(hpctimer_t *timer);

/* 
 * hpctimer_timer_create: Creates high-resolution timer of given type.
 *                        Returns pointer to created timer or NULL for failure.
 */
hpctimer_t *hpctimer_timer_create(hpctimer_type_t type, int flags)
{
	hpctimer_t *timer;
	
	if ( (timer = (hpctimer_t *)malloc(sizeof(*timer))) == NULL) {
		return NULL;
	}
	
	if (hpctimer_timer_initialize(timer, type, flags) == HPCTIMER_FAILURE) {
		free(timer);
		return NULL;
	}
	return timer;
}

/* hpctimer_timer_free: Destroys timer. */
void hpctimer_timer_free(hpctimer_t *timer)
{
	if (timer) {
		hpctimer_timer_finalize(timer);
		free(timer);
	}
}

/* hpctimer_timer_initialize: Initializes timer. */
static int hpctimer_timer_initialize(hpctimer_t *timer, hpctimer_type_t type,
                                     int flags)
{
	timer->type = type;
	timer->flags = flags;
	timer->overhead = 0;
	timer->freq = 0;	
	
	if (timer->flags & HPCTIMER_BINDTOCPU) {
		hpctimer_set_cpuaffinity(timer);
	}

	if (timer->type == HPCTIMER_TSC) {
		timer->gettime = hpctimer_gettsc;
		hpctimer_tsctimer_init(timer);
	} else {
		return HPCTIMER_FAILURE;
	}	
	return HPCTIMER_SUCCESS;
}

/* hpctimer_timer_finalize: Finalizes timer. */
static int hpctimer_timer_finalize(hpctimer_t *timer)
{
	if (timer->flags & HPCTIMER_BINDTOCPU) {
		return hpctimer_restore_cpuaffinity(timer);
	}
	return HPCTIMER_SUCCESS;
}

/* hpctimer_timer_gettime: Returns wall clock timestamp. */
hpctimer_time_t hpctimer_timer_gettime(hpctimer_t *timer)
{
	return timer->gettime();
}

/* hpctimer_timer_getdiff: Returns time difference in seconds. */
double hpctimer_timer_getdiff(hpctimer_t *timer, hpctimer_time_t start,
                              hpctimer_time_t stop)
{
	hpctimer_time_t timediff = stop - start;

	if (timediff >= timer->overhead) {
		return (timediff - timer->overhead) / (double)timer->freq * 1E-6;
	} else {
		return 0.0;
	}
}

/* hpctimer_timer_get_freq: Returns timer frequency. */
uint64_t hpctimer_timer_get_freq(hpctimer_t *timer)
{
	return timer->freq;
}

/* hpctimer_timer_get_overhead: Returns timer access overhead. */
hpctimer_time_t hpctimer_timer_get_overhead(hpctimer_t *timer)
{
	return timer->overhead;
}

/* 
 * hpctimer_init: Initializes global high-resolution timer of given type.
 *                Returns HPCTIMER_FAILURE for failure.
 */
int hpctimer_init(hpctimer_type_t type, int flags)
{
	int rc;
	
	rc = hpctimer_timer_initialize(&hpctimer_global_timer, type, flags);
	hpctimer_is_global_timer_initialized = 1;
	return rc;
}

/* hpctimer_free: Destroys timer. */
void hpctimer_free()
{
	hpctimer_timer_finalize(&hpctimer_global_timer);
	hpctimer_is_global_timer_initialized = 0;
}

/* hpctimer_gettime: Returns wall clock timestamp. */
hpctimer_time_t hpctimer_gettime()
{
	if (!hpctimer_is_global_timer_initialized)
		hpctimer_init(HPCTIMER_TSC, 0);
	return hpctimer_global_timer.gettime();
}

/* hpctimer_getwtime: Returns wall clock time in seconds. */
double hpctimer_getwtime()
{
	return (double)hpctimer_gettime() / 
	       (double)hpctimer_global_timer.freq * 1E-6;
}

/* hpctimer_getdiff: Returns time difference in seconds. */
double hpctimer_getdiff(hpctimer_time_t start, hpctimer_time_t stop)
{
	return hpctimer_timer_getdiff(&hpctimer_global_timer, start, stop);
}

/* hpctimer_get_freq: Returns timer frequency. */
uint64_t hpctimer_get_freq()
{
	return hpctimer_timer_get_freq(&hpctimer_global_timer);
}

/* hpctimer_get_overhead: Returns timer access overhead. */
hpctimer_time_t hpctimer_get_overhead()
{
	return hpctimer_timer_get_overhead(&hpctimer_global_timer);
}

/* hpctimer_gettsc: Returns value of TSC. */
static __inline__ hpctimer_time_t hpctimer_gettsc()
{
#if defined(__x86_64__)
	uint32_t low, high;
	
	__asm__ __volatile__(
		"xorl %%eax, %%eax\n"
		"cpuid\n"
		:::	"%rax", "%rbx", "%rcx", "%rdx"
	);
	__asm__ __volatile__(
		"rdtsc\n"
		: "=a" (low), "=d" (high)
	);
			
	return ((uint64_t)high << 32) | low;
#elif defined(__i386__)
	uint64_t val;
	
	__asm__ __volatile__(
		"xorl %%eax, %%eax\n"
		"cpuid\n"
		:::	"%eax", "%ebx", "%ecx", "%edx"
	);
	__asm__ __volatile__(
		"rdtsc\n"
		: "=A" (val)
	);
		
	return val;
#else
#	error "Unsupported platform"
#endif
}

/* hpctimer_tsttimer_init: Initializes TSC-based timer. */
static int hpctimer_tsctimer_init(hpctimer_t *timer)
{
	hpctimer_time_t start, stop, overhead;
	struct timeval t1, t2;
	int i, j;
	
	/* Make warm-up passes and determine timer overhead */
	start = hpctimer_gettsc();
	stop = hpctimer_gettsc();
	overhead = stop - start;

	start = hpctimer_gettsc();
	stop = hpctimer_gettsc();
	overhead = stop - start;

	start = hpctimer_gettsc();
	stop = hpctimer_gettsc();
	overhead = stop - start;

	start = hpctimer_gettsc();
	stop = hpctimer_gettsc();
	overhead = stop - start;

	start = hpctimer_gettsc();
	stop = hpctimer_gettsc();
	overhead = stop - start;

	timer->overhead = (overhead > 0) ? overhead : 0;
	
	/* Calibrate and determine number of ticks per calibration time */	
	for (i = 0; i < 3; i++) {
		start = hpctimer_gettsc();
		gettimeofday(&t1, NULL);		
		for (j = 0; j < 100000; j++) {
			__asm__ __volatile__("nop\n");
		}
		stop = hpctimer_gettsc();
		gettimeofday(&t2, NULL);
	}
	
	timer->freq = (stop - start - timer->overhead) / 
	              (t2.tv_sec * 1000000 + t2.tv_usec - 
                   t1.tv_sec * 1000000 - t1.tv_usec);
#ifdef _DEBUG
	printf("hpctimer: calibrate: calibrartion time (gettimeofday): %ld usec.\n", 
	       (t2.tv_sec * 1000000 + t2.tv_usec - 
            t1.tv_sec * 1000000 - t1.tv_usec));
	printf("hpctimer: calibrate: ticks per calibration time: %lld\n",
	        (long long int)(stop - start - timer->overhead));
#endif
	return HPCTIMER_SUCCESS;	
}

/* hpctimer_set_cpuaffinity: Binds current process to current cpu. */
static int hpctimer_set_cpuaffinity(hpctimer_t *timer)
{
#if defined(__gnu_linux__) || defined(linux)
#if 0
	cpu_set_t newcpuset;
	int cpu;
	
	/* Save current cpu affinity */
	CPU_ZERO(&timer->cpuset);
	if (sched_getaffinity(0, sizeof(timer->cpuset), &timer->cpuset) == -1) {
		return HPCTIMER_FAILURE;
	}
	
	/* Bind process to its current cpu */
	CPU_ZERO(&newcpuset);
	if ( (cpu = sched_getcpu() == -1)) {
		return HPCTIMER_FAILURE;
	}
	CPU_SET(cpu, &newcpuset);
	if (sched_setaffinity(0, sizeof(newcpuset), &newcpuset) == -1) {
		return HPCTIMER_FAILURE;
	}
#endif
	return HPCTIMER_SUCCESS;
#else
#	error "Unsupported platform"
#endif		
}

/* hpctimer_restore_cpuaffinity: Resore cpu afinity of current process. */
static int hpctimer_restore_cpuaffinity(hpctimer_t *timer)
{
#if 0
	return (sched_setaffinity(0, sizeof(timer->cpuset), &timer->cpuset) != 1) ?
	       HPCTIMER_SUCCESS : HPCTIMER_FAILURE;
#endif
	return HPCTIMER_SUCCESS;
}

