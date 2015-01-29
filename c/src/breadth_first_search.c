
#include "header.h"

void RestructPath(pPath search, pLocation start, pLocation goal)
{
	Location current;

	loc_copy(&current, goal);
	printf("start [%d,%d]\r\n", current.x,current.y);

	while(!(current.x == start->x && current.y == start->y))
	{
		//loc_copy(&path.came_from[current.y][current.x], &search->came_from[current.y][current.x]);
		//loc_copy(&current, &search->came_from[current.y][current.x]);

		set_loc(&path, &current, get_loc(search, &current));
		loc_copy(&current, get_loc(search, &current));
	}
}

/*¹ã¶ÈËÑË÷*/
pPath breadth_first_search(pSquareGrid graph, pLocation start, pLocation goal)
{
	queue_push(&frontier, start, 0);
	while(!queue_is_empty(&frontier))
	{
		int i=0;
		Location current;
		queue_pop(&frontier, &current);
		//printf("current:%d,%d count of queue:%d\r\n",current.x,current.y,frontier.Count);

		if(current.x == goal->x && current.y == goal->y)
		{
			break;
		}

		for(i=0; i<4; i++)
		{
			Location neighbour;
			neighbour = GetNeighbours(graph, &current, i);
			if(neighbour.x < 0 || neighbour.y < 0)
			{
				continue;
			}

			//if(is_in_queue(&frontier, &neighbour, compare) == 0)
			if(search.visited[neighbour.y][neighbour.x] == 0)
			{
				queue_push(&frontier, &neighbour, 0);
				set_loc(&search, &neighbour, &current);
				search.visited[neighbour.y][neighbour.x] = 1;
			}
		}
	}
	return &search;
}

