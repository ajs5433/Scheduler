/*
 * Scheduler.h
 *
 *  Created on: Sep 19, 2017
 *      Author: ajs5433
 */
#include <pthread.h>

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#define MAX_NAME_LENGTH (20)

typedef int bool;
enum { false, true };

typedef struct {
	char name[MAX_NAME_LENGTH];
	int total_exec_time;
	int rem_exec_time;
	int deadline;
	int period;
	pthread_t* thread;
	bool completed;				// completed during this period
} Task;

#endif /* SCHEDULER_H_ */
