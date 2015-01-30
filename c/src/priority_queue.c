/*
 * priority_queue.c
 *
 *  Created on: 2015年1月27日
 *      Author: Winder
 */


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
int queue_push(pQueue queue, pItem item, float priority)
{
	pNode this = queue->head;
	pNode last = queue->head;
	pNode new_node = (pNode)malloc(sizeof(Node));

	if(new_node != NULL)	/*若内存分配成功*/
	{
		/*新节点赋值*/
		new_node->priority = priority;
		new_node->data = *item;
		new_node->next = NULL;

		if(queue_is_empty(queue) == 1)		/*若队列为空*/
		{
			queue->head = new_node;			/*头指向第一个节点*/
			queue->tail = new_node;			/*尾指向新节点*/
		}
		else	/*队列不为空*/
		{
			if(new_node->priority < queue->head->priority)	/*与队列第一个节点比较*/
			{
				/*若新节点比第一个节点小，把新节点放到队首*/
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

				/*新节点最大，排到队列尾部*/
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

/*元素出列 返回：1成功 0失败*/
int queue_pop(pQueue queue, pItem item)
{
	int success = 0;
	pNode node = queue->head;

	if(queue_is_empty(queue) != 1 && node != NULL)
	{
		if(item != NULL)
		{
			*item = node->data;		/*取出数据*/
			printf("pop  [%d,%d] priority %.2f length %d\r\n", node->data.x, node->data.y, node->priority, queue->length);
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

