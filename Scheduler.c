#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <ctype.h>
#include <math.h>
#include "Scheduler.h"

#define NUM_TASKS (10)
#define _GNU_SOURCE

Task* tasks[NUM_TASKS];

Task* (*algorithm)();

Task* EDF(){
	Task* earliestTask = NULL;
	int i;
	for (i=0;i<NUM_TASKS;i++){
		Task* task = tasks[i];
		if(!task->completed){
			if (earliestTask == NULL || (earliestTask->deadline > task->deadline)) {
				earliestTask = task;
			}
		}
	}
	return earliestTask;
}

Task* SCT(){
	Task* earliestTask = NULL;
	int i;
	for (i=0;i<NUM_TASKS;i++){
		Task* task = tasks[i];
		if(!task->completed){
			if (earliestTask == NULL || (earliestTask->rem_exec_time > task->rem_exec_time)) {
				earliestTask = task;
			}
		}
	}
	return earliestTask;
}

Task* LST(){
	Task* earliestTask = NULL;
	int i;
	for (i=0;i<NUM_TASKS;i++){
		Task* task = tasks[i];
		if(!task->completed){
			if (earliestTask == NULL || (earliestTask->deadline - earliestTask->rem_exec_time > task->deadline - task->rem_exec_time)) {
				earliestTask = task;
			}
		}
	}
	return earliestTask;
}
/*
 * Method run by a task during execution
 */
void* execute(void* task) {
	return NULL;
}

void createThread(pthread_t* thread, Task* task) {
	pthread_attr_t attributes;
	pthread_attr_init(&attributes);
	int priority = 1; // Default starting priority for all tasks
	struct sched_param param;
	pthread_attr_getschedparam(&attributes, &param);
	param.sched_priority = priority;
	pthread_attr_setschedparam(&attributes, &param);
	pthread_create(thread, &attributes, execute, (void*)task);
}

void setPriority(Task* task, int priority){
	pthread_setschedprio(*((*task).thread), priority);
	//For testing purposes
	struct sched_param* param;
	pthread_getschedparam(*((*task).thread), NULL, param);
	printf(*(task->name)+"%d", param->sched_priority);
}

int main(int argc, char *argv[]) {
	char input;

	while(input != 'a' && input != 'b' && input != 'c'){
		printf("Select one scheduling algorithm (enter letter of choice followed by a newline): \n\t(a) Earliest Deadline First\n\t(b)Shortest Completion Time\n\t(c)Least Slack Time\n");
		input = getchar();
	}
	if (input == 'a') {
		algorithm = &EDF;
	} else if (input == 'b'){
		algorithm = &SCT;
	} else {
		algorithm = &LST;
	}


	int cpd[3] = {0};
	printf("Tasks to schedule:\n");
	int taskCount = 0;
	bool done = false;

	/*
	 * SECTION TO ASK FOR THE USER INPUT OF THE THREADS
	 *
	while(!done) {
		char name[MAX_NAME_LENGTH];
		printf("Enter task name, followed by a newline:\n");
		char input = getchar();
		input = getchar();
		int counter = 0;

		// Get name
		while(!isspace(input) && counter < MAX_NAME_LENGTH-1) {
			name[counter++] = input;
			input = getchar();
		}
		printf("Enter execution time, period, and deadline, separated by newlines:\n");
		input = getchar();
		input = getchar();
		counter = 0;
		int i;
		for (i=0;i<3;i++) {
			int multiplier = 1;
			while (!isspace(input)) {
				if (isdigit(input)) {
					cpd[i] += input*multiplier;
					multiplier *= 10;
				}
				input = getchar();
			}
			multiplier = 1;
			input = getchar();
		}

		// Create the task
		pthread_t* taskThread = NULL;
		Task newTask = {name, cpd[0], cpd[0], cpd[1], cpd[2], taskThread, false};
		createThread(taskThread, &newTask);
		tasks[taskCount++] = &newTask;
		cpd[0] = 0;
		cpd[1] = 0;
		cpd[2] = 0;
	}
	*/

	int set1[12] = {1,3,3,2,5,5,1,10,10};
	char names[3][3] = {{'o','n','e'},{'t','w','o'},{'t','h','r'}};
	int i;

	for (i = 0 ; i<12; i+=3){
		pthread_t* taskThread = NULL;
		Task newTask = {names[i], set1[i], set1[i], set1[i+1], set1[i+2], &taskThread, false};
		createThread(taskThread, &newTask);
		tasks[taskCount++] = &newTask;
	}

	setPriority(tasks[0], 5);

	return EXIT_SUCCESS;
}
