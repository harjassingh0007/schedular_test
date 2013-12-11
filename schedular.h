typedef struct
{
	void* starting_address;
	int each_size;
	int total_elements;
	int rear;
	int front;
}Queue;

typedef struct
{
	int time_;
	int priority;
	Queue job;
}Process;

Process* createJob(int time, int priority,int size, int totalElements);
int enqueueProcess(Process* queue, void* element);
void *dequeue(Queue* queue);