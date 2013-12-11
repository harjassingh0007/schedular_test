#include "schedular.h"
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

Process* createJob(int time,int priority,int size, int totalElements){
	Process *process = (Process*)calloc(1, sizeof(Process));
	process->job.starting_address = calloc(size, totalElements);
	process->job.each_size = size;
	process->job.total_elements = totalElements;
	process->job.front = 0;
	process->job.rear = 0;
	process->priority = priority;
	process->time_ = time;
	return process;
}
int isProcessFull(Process *process){
	if(process->job.rear == process->job.total_elements-1){
		return 0; 
	}
	return 1;
}

int enqueueProcess(Process* process, void* element){
	void* lastElement;
	if(isProcessFull(process) == 0)
		return 0;
	if(process->job.rear > 0){
		process->job.rear = (process->job.rear) + 1;
	}
	lastElement = (process->job.starting_address) + ((process->job.rear)*(process->job.each_size));
	memcpy(lastElement,element,process->job.each_size);
	return 1;
}