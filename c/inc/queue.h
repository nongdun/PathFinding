/*
 * queue.h
 *
 *  Created on: 2015��1��21��
 *      Author: Winder
 */

#ifndef QUEUE_H_
#define QUEUE_H_

//#define NULL (0)

/*�ڵ�ṹ�嶨��*/
typedef struct _Node
{
	Item data;
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
extern int  queue_push(pQueue queue, pItem item);				/*����*/
extern int  queue_pop(pQueue queue, pItem item);				/*����*/
extern void queue_traverse(pQueue queue, void (*visit)());	/*��visit��������ÿ���ڵ�*/
extern void queue_clear(pQueue queue);						/*��ն���*/
extern void queue_destroy(pQueue queue);						/*���ٶ���*/
extern int  is_in_queue(pQueue queue, pItem item, int (*compare)());	/*�жϽڵ��Ƿ��ڶ�����*/

extern int  compare(pItem item1, pItem item2);		/*�ڵ����ݱȽϺ���*/

#endif /* QUEUE_H_ */
