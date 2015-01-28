/*
 * queue.c
 *
 *  Created on: 2015年1月21日
 *      Author: Winder
 */

#include "header.h"

/*初始化队列*/
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

/*判断队列是否为空 队列空返回1 非空返回队列长度*/
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

/*元素入列 返回：1成功 0失败*/
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
			queue->head = node;			/*若队列为空，头指向第一个节点*/
		}
		else
		{
			queue->tail->next = node;	/*队列不空，最后一个节点的指针指向新节点*/
		}
		queue->tail = node;		/*队列尾指向新结点*/
		queue->length++;		/*队列长度+1*/

		return 1;
	}
	else
	{
		return 0;
	}
}

/*元素出列 返回：1成功 0失败*/
int queue_pop(pQueue queue, pItem item)
{
	int success = 0;
	pNode node = queue->head;

	if(queue_is_empty(queue) != 1 && node != NULL)
	{
		if(item != NULL)
		{
			item->x = node->data.x;		/*取出数据*/
			item->y = node->data.y;		/*取出数据*/
		}

		queue->head = node->next;	/*队头指向下一个节点*/
		queue->length--;			/*队列长度-1*/
		free(node);					/*释放节点*/

		if(queue->length == 0)
		{
			queue->tail = NULL;		/*若出队的是最后一个元素，清空队尾指针*/
		}
		success = 1;				/*成功*/
	}
	return success;
}

/*遍历队列中的每一个节点*/
void queue_traverse(pQueue queue, void (*visit)())
{
	pNode node = queue->head;	/*访问头节点*/

	while(node != NULL)
	{
		visit(node->data);		/*访问每个节点*/
		node = node->next;		/*指针指向下一个节点*/
	}
}

/*清空队列*/
void queue_clear(pQueue queue)
{
	while(queue_is_empty(queue) != 1)
	{
		queue_pop(queue, NULL);
	}
}

/*销毁队列*/
void queue_destroy(pQueue queue)
{
	if(queue_is_empty(queue) != 1)
	{
		queue_clear(queue);			/*清空队列*/
	}

	free(queue);					/*释放空间*/
}

/*比较函数*/
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

/*判断节点是否已经在队列中 返回：1在队列中 0不在队列中*/
int is_in_queue(pQueue queue, pItem item, int (*compare)())
{
	pNode node = queue->head;			/*访问头节点*/

	while(node != NULL)
	{
		if(compare(&node->data, item))	/*比较每个节点*/
		{
			return 1;					/*在队列中*/
		}
		node = node->next;				/*指针指向下一个节点*/
	}
	return 0;
}

