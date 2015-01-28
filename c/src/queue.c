/*
 * queue.c
 *
 *  Created on: 2015��1��21��
 *      Author: Winder
 */

#include "header.h"

/*��ʼ������*/
pQueue queue_init()
{
	pQueue queue = (pQueue)malloc(sizeof(Queue));
	if(queue != NULL)
	{
		queue->head = NULL;
		queue->tail = NULL;
		queue->length = 0;
	}
	return queue;
}

/*�ж϶����Ƿ�Ϊ�� ���пշ���1 �ǿշ��ض��г���*/
int  queue_is_empty(pQueue queue)
{
	if(queue->head == NULL && queue->tail == NULL && queue->length == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*Ԫ������ ���أ�1�ɹ� 0ʧ��*/
int queue_push(pQueue queue, pItem item)
{
	pNode node = (pNode)malloc(sizeof(Node));
	if(node != NULL)
	{
		node->data.x = item->x;
		node->data.y = item->y;

		node->next = NULL;

		if(queue_is_empty(queue) == 1)
		{
			queue->head = node;			/*������Ϊ�գ�ͷָ���һ���ڵ�*/
		}
		else
		{
			queue->tail->next = node;	/*���в��գ����һ���ڵ��ָ��ָ���½ڵ�*/
		}
		queue->tail = node;		/*����βָ���½��*/
		queue->length++;		/*���г���+1*/

		return 1;
	}
	else
	{
		return 0;
	}
}

/*Ԫ�س��� ���أ�1�ɹ� 0ʧ��*/
int queue_pop(pQueue queue, pItem item)
{
	int success = 0;
	pNode node = queue->head;

	if(queue_is_empty(queue) != 1 && node != NULL)
	{
		if(item != NULL)
		{
			item->x = node->data.x;		/*ȡ������*/
			item->y = node->data.y;		/*ȡ������*/
		}

		queue->head = node->next;	/*��ͷָ����һ���ڵ�*/
		queue->length--;			/*���г���-1*/
		free(node);					/*�ͷŽڵ�*/

		if(queue->length == 0)
		{
			queue->tail = NULL;		/*�����ӵ������һ��Ԫ�أ���ն�βָ��*/
		}
		success = 1;				/*�ɹ�*/
	}
	return success;
}

/*���������е�ÿһ���ڵ�*/
void queue_traverse(pQueue queue, void (*visit)())
{
	pNode node = queue->head;	/*����ͷ�ڵ�*/

	while(node != NULL)
	{
		visit(node->data);		/*����ÿ���ڵ�*/
		node = node->next;		/*ָ��ָ����һ���ڵ�*/
	}
}

/*��ն���*/
void queue_clear(pQueue queue)
{
	while(queue_is_empty(queue) != 1)
	{
		queue_pop(queue, NULL);
	}
}

/*���ٶ���*/
void queue_destroy(pQueue queue)
{
	if(queue_is_empty(queue) != 1)
	{
		queue_clear(queue);			/*��ն���*/
	}

	free(queue);					/*�ͷſռ�*/
}

/*�ȽϺ���*/
int compare(pItem item1, pItem item2)
{
	if(item1->x == item2->x && item1->y == item2->y)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*�жϽڵ��Ƿ��Ѿ��ڶ����� ���أ�1�ڶ����� 0���ڶ�����*/
int is_in_queue(pQueue queue, pItem item, int (*compare)())
{
	pNode node = queue->head;			/*����ͷ�ڵ�*/

	while(node != NULL)
	{
		if(compare(&node->data, item))	/*�Ƚ�ÿ���ڵ�*/
		{
			return 1;					/*�ڶ�����*/
		}
		node = node->next;				/*ָ��ָ����һ���ڵ�*/
	}
	return 0;
}

