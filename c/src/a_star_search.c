/*
 * dijkstra_search.c
 *
 *  Created on: 2015��1��28��
 *      Author: Winder
 */

#include "header.h"

float heuristic(pLocation loc1, pLocation loc2)
{
	return (fabs(loc1->x - loc2->x) + fabs(loc1->y - loc2->y));
}

/*A star����*/
pPath a_star_search(pSquareGrid map, pLocation start, pLocation goal)
{
	pQueue frontier = queue_init();
	frontier->push(frontier, start, 0);
	search.cost_so_far[start->y][start->x] = 0;

	while(!frontier->empty(frontier))
	{
		int i=0;
		Location current;
		frontier->pop(frontier, &current);

		if(current.x == goal->x && current.y == goal->y)
		{
			break;
		}

		for(i=0; i<4; i++)
		{
			float new_cost=0;
			Location neighbour;
			neighbour = map->get_neighbour(map, &current, i);
			if(neighbour.x < 0 || neighbour.y < 0)
			{
				continue;
			}

			new_cost = search.cost_so_far[current.y][current.x] + map->get_cost(map, &neighbour);
			//if(is_in_queue(frontier, &neighbour, compare) == 0 || new_cost< search.cost_so_far[neighbour.y][neighbour.x])
			if(search.visited[neighbour.y][neighbour.x] == 0 || new_cost< search.cost_so_far[neighbour.y][neighbour.x])
			{
				float priority = 0;
				search.cost_so_far[neighbour.y][neighbour.x] = new_cost;

				priority = new_cost + heuristic(goal, &neighbour);
				//priority = heuristic(goal, &neighbour);	/*greedy*/
				//printf("heuristic %.2f\r\n",priority);

				frontier->push(frontier, &neighbour, priority);

				set_loc(&search, &neighbour, &current);
				search.visited[neighbour.y][neighbour.x] = 1;
			}
		}
	}

	frontier->destroy(frontier);
	return &search;
}
