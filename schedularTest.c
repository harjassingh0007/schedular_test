#include "testUtils.h"
#include "schedular.h"
#include <memory.h>
#include <stdio.h>
//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

Process create_ints(int length, int *array,int time,int priority){
	int i;
	Process intData = *createJob(time,priority, sizeof(int), length);
	for (i = 0; i < intData.job.total_elements; ++i)
	{
		((int *)intData.job.starting_address)[i] = array[i];
	}
	return intData;
}

Process create_chars(int length, char *array,int time, int priority){
	int i;
	Process charData = *createJob(time, priority, sizeof(char), length);
	for (i = 0; i < charData.job.total_elements; ++i)
	{
		((char *)charData.job.starting_address)[i] = array[i];
	}
	return charData;
}

typedef char string[100];
Process create_strings(int length, string array, int time, int priority){
	int i;
	Process strData = *createJob(time, priority, sizeof(string), length);
	for (i = 0; i < strData.job.total_elements; i++)
	{
		(*(string *)strData.job.starting_address)[i] = *array+i*sizeof(string);
	}
	return strData;
}



int areSizesEqual(Process u1, Process u2) {
	return u1.job.each_size == u2.job.each_size;
}

int areNumElementsEqual(Process u1, Process u2){
	return u1.job.total_elements == u2.job.total_elements;
}
int areRearEqual(Process u1, Process u2){
	return u1.job.rear == u2.job.rear;
}

int areFrontEqual(Process u1, Process u2){
	return u1.job.front == u2.job.front;
}
int areTimeEqual(Process u1, Process u2){
	return u1.time_ == u2.time_;
}
int arePriorityEqual(Process u1, Process u2){
	return u2.priority == u2.priority;
}

int size_of_aryUtil(Process a) {
	return a.job.each_size * a.job.total_elements;
}

int cmpArrays(Process u1, Process u2) {
	void *a1 = u1.job.starting_address;
	void *a2 = u2.job.starting_address;
	return memcmp(a1,a2,size_of_aryUtil(u1));
}

int areEqual(Process u1,Process u2){
    if(!(areSizesEqual(u1,u2)&&areNumElementsEqual(u1,u2)&&areRearEqual(u1,u2)&&areFrontEqual(u1,u2)&&areTimeEqual(u1,u2)&&arePriorityEqual(u1,u2)))
		return 0;
	return (0 == cmpArrays(u1,u2));
};

int areEqualStrings(Process u1,Process u2){
	int i, result;
	void *item1, *item2;
	for(i = 0; i < u1.job.total_elements; i++){
		item1 = u1.job.starting_address+(i*u1.job.each_size);
		item2 = u2.job.starting_address+(i*u2.job.each_size);
		result = strcmp(*(string*)item1,*(string*)item2);
		if(result == 1){
			return 0;
		}
	}
		return 1;
}


void test_1_create_a_job_of_int_type(){
	Process* data;
	int temp[] = {0,0,0,0,0};
	Process expected = {60,5,temp,sizeof(int),5,0,0};
	data = createJob(60,5,sizeof(int), 5);
	ASSERT(1 == areEqual(*data, expected));
}

void test_2_create_a_Job_of_char_type(){
	Process* data;
	char temp[] = {0,0,0,0,0};
	Process expected = {50,10,temp,sizeof(char),5,0,0};
	data = createJob(50,10,sizeof(char), 5);
	ASSERT(1 == areEqual(*data, expected));
}

void test_3_create_a_job_of_string_type(){
	Process* data;
	string temp[] = {"","","","",""};
	Process expected = {100,2,temp,sizeof(string),5,0,0};
	data = createJob(100,2,sizeof(string), 5);
	ASSERT(1 == areEqual(*data, expected));
}

void test_4_enProcess_an_item_into_int_type_Process(){
	Process data;
	int priority = 100;
	int time = 10;
	int result, element = 1;
	int arr[] = {0,0,0,0,0};
	int expArr[] = {1,0,0,0,0};
	Process expected = {time,priority,expArr,sizeof(int),5,0,0};
	data = create_ints(5,arr,time,priority);
	data.job.front = 0 , data.job.rear = 0;
	result = enqueueProcess(&data, &element);
	ASSERT(1 == result && areEqual(expected, data));
}

void test_5_enProcess_an_item_into_char_type_Process(){
	Process data;
	int priority = 100;
	int time = 10;
	int result;
	char element = '1';
	char arr[] = {0,0,0,0,0};
	char expArr[] = {'1',0,0,0,0};
	Process expected = {time,priority,expArr,sizeof(char),5,0,0};
	data = create_chars(5,arr,time,priority);
	data.job.front = 0 , data.job.rear = 0;
	result = enqueueProcess(&data, &element);
	ASSERT(1 == result && areEqual(expected, data));
}

void test_6_enProcess_an_item_into_string_type_Process(){
	Process data;
	int priority = 100;
	int time = 10;
	int result;
	string element = "1";
	string arr[] = {0,0,0,0,0};
	string expArr[] = {"1",0,0,0,0};
	Process expected = {time,priority,expArr,sizeof(char),5,0,0};
	data = create_chars(5,arr,time,priority);
	data.job.front = 0 , data.job.rear = 0;
	result = enqueueProcess(&data, &element);
	ASSERT(1 == result && areEqual(expected, data));
}
