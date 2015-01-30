/*
 * priority_queue.c
 *
 *  Created on: 2015��1��27��
 *      Author: Winder
 */


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

		queue->empty = queue_is_empty;
		queue->push = queue_push;
		queue->pop = queue_pop;
		queue->clear = queue_clear;
		queue->have = is_in_queue;
		queue->traverse = queue_traverse;
		queue->destroy = queue_destroy;
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
int queue_push(pQueue queue, pItem item, float priority)
{
	pNode this = queue->head;
	pNode last = queue->head;
	pNode new_node = (pNode)malloc(sizeof(Node));

	if(new_node != NULL)	/*���ڴ����ɹ�*/
	{
		/*�½ڵ㸳ֵ*/
		new_node->priority = priority;
		new_node->data = *item;
		new_node->next = NULL;

		if(queue_is_empty(queue) == 1)		/*������Ϊ��*/
		{
			queue->head = new_node;			/*ͷָ���һ���ڵ�*/
			queue->tail = new_node;			/*βָ���½ڵ�*/
		}
		else	/*���в�Ϊ��*/
		{
			if(new_node->priority < queue->head->priority)	/*����е�һ���ڵ�Ƚ�*/
			{
				/*���½ڵ�ȵ�һ���ڵ�С�����½ڵ�ŵ�����*/
				new_node->next = queue->head;
				queue->head = new_node;
			}
			else
			{
				this= queue->head->next;
				while(this != NULL)
				{
					if(new_node->priority < this->priority)
					{
						last->next = new_node;
						new_node->next = this;

						queue->length++;
						return 1;
					}
					else
					{
						last = this;
						this = this->next;
					}
				}

				/*�½ڵ�����ŵ�����β��*/
				last->next = new_node;
				queue->tail = new_node;
			}
		}

		queue->length++;
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
			*item = node->data;		/*ȡ������*/
			printf("pop  [%d,%d] priority %.2f length %d\r\n", node->data.x, node->data.y, node->priority, queue->length);
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

#if 0

void print_item(Item item)
{
	printf("data %d\t", item);
}

int main()
{
	int i=0;

	pQueue queue = queue_init();
	Node node[10];

	srand((int)time(0));

	for(i=0;i<10;i++)
	{
		Item item = 10*(rand()/(float)RAND_MAX);
		node[i].data = item;
		node[i].priority = item;
		if(queue_push(queue, &item, node[i].priority))
		{
			//printf("push data %d priority %.2f\r\n", node[i].data, node[i].priority);
			printf("push %d\t", node[i].data);
		}
	}

	printf("\r\nordered:\r\n");

	queue_traverse(queue, print_item);

	printf("\r\npop:\r\n");

	while(queue_is_empty(queue)!=1)
	{
		Item item;
		if(queue_pop(queue,&item))
		{
			printf("pop %d\t", item);
		}
	}

	return 0;
}

#endif

