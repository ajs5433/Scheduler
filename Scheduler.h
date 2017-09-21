/*
 * Scheduler.h
 *
 *  Created on: Sep 19, 2017
 *      Author: ajs5433
 */
#include <pthread.h>

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

typedef int bool;
enum { false, true };

struct TaskStruct {
	int total_exec_time;
	int rem_exec_time;
	int deadline;
	int period;
	pthread_t thread;
	bool completed;				// completed during this period
} new_task = {0,0,0,0,0,0};

typedef struct TaskStruct Task;

#endif /* SCHEDULER_H_ */
