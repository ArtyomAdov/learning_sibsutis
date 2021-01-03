/*
 * hpctimer.h: High-Resolution timers library.
 *
 * Copyright (C) 2010 Mikhail Kurnosov <mkurnosov@gmail.com>
 */

#ifndef HPCTIMER_H
#define HPCTIMER_H
 
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__GNUC__)
#	define uint64_t unsigned long long int
#	define uint32_t unsigned int
#elif defined(__SUNPRO_C)
#	define uint64_t unsigned long long int
#	define uint32_t unsigned int
#endif

#define HPCTIMER_BINDTOCPU 0x00000001

enum {
	HPCTIMER_SUCCESS = 0,
	HPCTIMER_FAILURE = 1
};

typedef enum hpctimer_type {
	HPCTIMER_GETTIMEOFDAY = 0,
	HPCTIMER_TSC = 1,
	HPCTIMER_MPI_WTIME = 2
} hpctimer_type_t;

typedef uint64_t hpctimer_time_t;
typedef struct hpctimer hpctimer_t;

/* 
 * hpctimer_init: Initializes global high-resolution timer of given type.
 *                Returns HPCTIMER_FAILURE for failure.
 */
int hpctimer_init(hpctimer_type_t type, int flags);

/* hpctimer_free: Destroys gloabal timer. */
void hpctimer_free();

/* hpctimer_gettime: Returns wall clock timestamp. */
hpctimer_time_t hpctimer_gettime();

/* hpctimer_getwtime: Returns wall clock time in seconds. */
double hpctimer_getwtime();

/* hpctimer_getdiff: Returns time difference in seconds. */
double hpctimer_getdiff(hpctimer_time_t start, hpctimer_time_t stop);

/* hpctimer_get_freq: Returns timer frequency. */
uint64_t hpctimer_get_freq();

/* hpctimer_get_overhead: Returns timer access overhead. */
hpctimer_time_t hpctimer_get_overhead();

/* 
 * hpctimer_timer_create: Creates high-resolution timer of given type.
 *                        Returns pointer to created timer or NULL for failure.
 */
hpctimer_t *hpctimer_timer_create(hpctimer_type_t type, int flags);

/* hpctimer_timer_free: Destroys timer. */
void hpctimer_timer_free(hpctimer_t *timer);

/* hpctimer_timer_gettime: Returns wall clock timestamp. */
hpctimer_time_t hpctimer_timer_gettime(hpctimer_t *timer);

/* hpctimer_timer_getdiff: Returns time difference in seconds. */
double hpctimer_timer_getdiff(hpctimer_t *timer, hpctimer_time_t start,
                              hpctimer_time_t stop);

/* hpctimer_timer_get_freq: Returns timer frequency. */
uint64_t hpctimer_timer_get_freq(hpctimer_t *timer);

/* hpctimer_timer_get_overhead: Returns timer access overhead. */
hpctimer_time_t hpctimer_timer_get_overhead(hpctimer_t *timer);

#ifdef __cplusplus
}
#endif

#endif /* HPCTIMER_H */
