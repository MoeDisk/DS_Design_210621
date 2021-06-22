#ifndef PARKING_H_INCLUDE
#define PARKING_H_INCLUDE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

//时间节点
typedef struct time{
	int hour;
	int min;
}Time;

//详情节点
typedef struct node{
	char num[10];
	Time reach;
	Time leave;
}CarNode;

//停车场堆栈
typedef struct NODE{
	CarNode *stack[4];
	int top;
}SeqStackCar;

//等车的车 
typedef struct car{
	CarNode *data;
	struct car *next;	//停车场切便道用
}QueueNode;

//便道堆栈 
typedef struct Node{
	QueueNode *head;
	QueueNode *rear;
}LinkQueueCar;

//函数初始化
void InitStack(SeqStackCar *);	//栈
int InitQueue(LinkQueueCar *);	//便道
int arrival(SeqStackCar *, LinkQueueCar *);	//到达
void leave(SeqStackCar *, SeqStackCar *,LinkQueueCar *);	//离开
void list(SeqStackCar,LinkQueueCar);	//详情

#endif