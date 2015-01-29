/*
 * priority_queue.h
 *
 *  Created on: 2015��1��27��
 *      Author: Winder
 */

#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include "stdio.h"
#include "stdlib.h"

/*�ڵ�ṹ�嶨��*/
typedef struct _Node
{
	Item data;
	float priority;
	struct _Node * next;
}Node, *pNode;

/*���ж���*/
typedef struct _Queue
{
	pNode head;		/*��ͷ*/
	pNode tail;		/*��β*/
	int length;		/*���г���*/
}Queue, *pQueue;

extern pQueue queue_init();									/*��ʼ������*/
extern int  queue_is_empty(pQueue queue);					/*�ж϶����Ƿ�Ϊ��*/
extern int  queue_push(pQueue queue, pItem item, float priority);		/*����*/
extern int  queue_pop(pQueue queue, pItem item);				/*����*/
extern void queue_traverse(pQueue queue, void (*visit)());	/*��visit��������ÿ���ڵ�*/
extern void queue_clear(pQueue queue);						/*��ն���*/
extern void queue_destroy(pQueue queue);						/*���ٶ���*/
extern int  is_in_queue(pQueue queue, pItem item, int (*compare)());	/*�жϽڵ��Ƿ��ڶ�����*/

extern int  compare(pItem item1, pItem item2);		/*�ڵ����ݱȽϺ���*/

#endif /* PRIORITY_QUEUE_H_ */
