/*
 * graph.c
 *
 *  Created on: 2015年1月21日
 *      Author: Winder
 */

#include "header.h"

Location neighbours[4];

/*判断点是否在地图内*/
int in_bounds(pSquareGrid graph, pLocation loc)
{
	return (loc->x >= 0) && (loc->x < graph->width)
		&& (loc->y >= 0) && (loc->y < graph->height);
}

/*判断点是否能通过*/
int passable(pSquareGrid graph, pLocation loc)
{
	return (graph->cost[loc->y][loc->x] < 9);
}

/*返回相邻点坐标*/
Location GetNeighbours(pSquareGrid graph, pLocation loc, int i)
{
	Location neighbour;

	neighbour.x = loc->x + (i<2 ? i : 2-i);
	neighbour.y = loc->y + (i<3 ? i-1 : 0);

	if(!(in_bounds(graph, &neighbour) && passable(graph, &neighbour)))
	{
		neighbour.x = -1;
		neighbour.y = -1;
	}

	return neighbour;
}

float get_cost(pSquareGrid graph, pLocation loc)
{
	return graph->cost[loc->y][loc->x];
}

void loc_copy(pLocation dest, pLocation source)
{
	dest->x = source->x;
	dest->y = source->y;
}

pLocation get_loc(pPath path, pLocation loc)
{
	return &path->came_from[loc->y][loc->x];
}

void set_loc(pPath path, pLocation loc, pLocation value)
{
	loc_copy(&path->came_from[loc->y][loc->x], value);
}


#if 0
/*返回相邻点坐标*/
pLocation GetNeighbours(pSquareGrid graph, pLocation loc)
{
	int i=0;
	printf("get neighbours:");
	for(i=0; i<4; i++)
	{
		neighbours[i].x = loc->x + (i<2 ? i : 2-i);
		neighbours[i].y = loc->y + (i<3 ? i-1 : 0);

		printf("[%d,%d]",neighbours[i].x,neighbours[i].y);
		if(!(in_bounds(graph, &neighbours[i]) && passable(graph, &neighbours[i])))
		{
			//neighbours[i].x = loc->x;
			//neighbours[i].y = loc->y;
			neighbours[i].x = 0;
			neighbours[i].y = 0;
		}
	}
	printf("\r\n");
	return neighbours;
}
#endif

