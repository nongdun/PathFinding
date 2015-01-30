/*
 * dijkstra_search.c
 *
 *  Created on: 2015年1月28日
 *      Author: Winder
 */

#include "header.h"

float heuristic(pLocation loc1, pLocation loc2)
{
	return (fabs(loc1->x - loc2->x) + fabs(loc1->y - loc2->y));
}

/*A star搜索*/
void a_star_search(pSquareGrid map, pLocation start, pLocation goal)
{
	pQueue frontier = queue_init();					/*初始化搜索队列*/
	frontier->push(frontier, start, 0);				/*起始坐标入队*/
	map->set_cost_so_far(map, start, 0);			/*起始搜索权值*/
	//search.cost_so_far[start->y][start->x] = 0;

	while(!frontier->empty(frontier))
	{
		int dir=0;
		Location current;
		frontier->pop(frontier, &current);

		if(current.x == goal->x && current.y == goal->y)
		{
			break;
		}

		for(dir=0; dir<4; dir++)
		{
			float new_cost=0;

			pLocation neighbour = map->get_neighbour(map, &current, dir);
			if(neighbour == NULL)
			{
				continue;
			}

			new_cost = map->get_cost_so_far(map, &current) + map->get_cost(map, neighbour);
			if(map->get_visited(map, neighbour) == 0 || new_cost < map->get_cost_so_far(map, neighbour))
			{
				float priority = 0;
				map->set_cost_so_far(map, neighbour, new_cost);

				priority = new_cost + heuristic(goal, neighbour);

				frontier->push(frontier, neighbour, priority);
				printf("push [%d,%d] priority %f\r\n", neighbour->x, neighbour->y, priority);

				map->set_came_from(map, neighbour, &current);
				map->set_visited(map, &current);
			}

			free(neighbour);
		}
	}

	frontier->destroy(frontier);
}
