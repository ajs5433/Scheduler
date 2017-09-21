#include <stdlib.h>
#include <stdio.h>

#include "Scheduler.h"

int numThreads = 10;

Task tasks[numThreads];

Task (*algorithm)();

Task EDF(){
	Task earliestTask;
	for (int i=0;i<numThreads;i++){
		Task task = tasks[i];
		if(!task.completed){
			if (earliestTask == 0 || (earliestTask.deadline > task.deadline)) {
				earliestTask = task;
			}
		}
	}
	return earliestTask;
}

Task SCT(){
	Task earliestTask;
	for (int i=0;i<numThreads;i++){
		Task task = tasks[i];
		if(!task.completed){
			if (earliestTask == 0 || (earliestTask.rem_exec_time > task.rem_exec_time)) {
				earliestTask = task;
			}
		}
	}
	return earliestTask;
}

Task LST(){
	Task earliestTask;
	for (int i=0;i<numThreads;i++){
		Task task = tasks[i];
		if(!task.completed){
			if (earliestTask == 0 || (earliestTask.deadline - earliestTask.rem_exec_time > task.deadline - task.rem_exec_time)) {
				earliestTask = task;
			}
		}
	}
	return earliestTask;
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
		TaskThread newTask = TaskThread();
		newTask.total_exec_time = c;
		newTask.rem_exec_time = c;
		newTask.period = p;
		newTask.deadline = d;
		tasks[taskCount] = newTask;
	}

	return EXIT_SUCCESS;
}
