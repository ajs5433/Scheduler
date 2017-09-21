#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "Scheduler.h"

#define NUM_TASKS (10)

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


int main(int argc, char *argv[]) {
	char input;

	while(input != 'a' && input != 'b' && input != 'c'){
		printf("Select one scheduling algorithm: \n\t(a) Earliest Deadline First\n\t(b)Shortest Completion Time\n\t(c)Least Slack Time\n");
		input = getchar();
	}
	if (input == 'a') {
		algorithm = &EDF;
	} else if (input == 'b'){
		algorithm = &SCT;
	} else {
		algorithm = &LST;
	}

	int c;
	int p;
	int d;
	char name[MAX_NAME_LENGTH];
	printf("Enter tasks:\n");
	int taskCount = 0;
	bool done = false;
	while(!done) {
		scanf("%d",&c);
		if (d == 0) {
			done = true;
			break;
		}
		scanf("%d",&p);
		scanf("%d",&d);
		scanf("%s",name);

		pthread_t* taskThread = NULL;
		Task newTask = {name, c, c, p, d, taskThread, false};
		createThread(taskThread, &newTask);
		tasks[taskCount] = &newTask;
	}

	return EXIT_SUCCESS;
}
