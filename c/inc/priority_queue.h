/*
 * priority_queue.h
 *
 *  Created on: 2015年1月27日
 *      Author: Winder
 */

#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include "stdio.h"
#include "stdlib.h"

/*节点结构体定义*/
typedef struct _Node
{
	Item data;
	float priority;
	struct _Node * next;
}Node, *pNode;

/*队列定义*/
typedef struct _Queue
{
	pNode head;		/*队头*/
	pNode tail;		/*队尾*/
	int length;		/*队列长度*/
}Queue, *pQueue;

extern pQueue queue_init();									/*初始化队列*/
extern int  queue_is_empty(pQueue queue);					/*判断队列是否为空*/
extern int  queue_push(pQueue queue, pItem item, float priority);		/*入列*/
extern int  queue_pop(pQueue queue, pItem item);				/*出列*/
extern void queue_traverse(pQueue queue, void (*visit)());	/*用visit函数遍历每个节点*/
extern void queue_clear(pQueue queue);						/*清空队列*/
extern void queue_destroy(pQueue queue);						/*销毁队列*/
extern int  is_in_queue(pQueue queue, pItem item, int (*compare)());	/*判断节点是否在队列中*/

extern int  compare(pItem item1, pItem item2);		/*节点数据比较函数*/

#endif /* PRIORITY_QUEUE_H_ */
