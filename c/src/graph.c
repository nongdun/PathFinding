/*
 * graph.c
 *
 *  Created on: 2015年1月21日
 *      Author: Winder
 */

#include "header.h"

Location neighbours[4];

pSquareGrid grid_init();
int grid_in_bounds(pSquareGrid graph, pLocation loc);
int grid_passable(pSquareGrid graph, pLocation loc);
float grid_get_cost(pSquareGrid graph, pLocation loc);
Location grid_get_neighbour(pSquareGrid graph, pLocation loc, Direction dir);


pSquareGrid grid_init()
{
	pSquareGrid grid = (pSquareGrid)malloc(sizeof(SquareGrid));
	if(grid != NULL)
	{
		memset(grid, 0, sizeof(SquareGrid));
		grid->width = MAP_WIDTH;
		grid->height = MAP_HEIGHT;

		/*绑定函数指针*/
		grid->in_bounds = grid_in_bounds;			/*判断节点是否在地图内*/
		grid->passable = grid_passable;				/*判断节点是否可以通过*/
		grid->get_cost = grid_get_cost;				/*返回节点权值*/
		grid->get_neighbour = grid_get_neighbour;	/*返回相邻节点座标*/
	}

	return grid;
}


/*判断点是否在地图内*/
int grid_in_bounds(pSquareGrid graph, pLocation loc)
{
	return (loc->x >= 0) && (loc->x < graph->width)
		&& (loc->y >= 0) && (loc->y < graph->height);
}

/*判断点是否能通过*/
int grid_passable(pSquareGrid graph, pLocation loc)
{
	return (graph->cost[loc->y][loc->x] < 9);
}

/*返回相邻点坐标*/
Location grid_get_neighbour(pSquareGrid graph, pLocation loc, Direction dir)
{
	Location neighbour;

	neighbour.x = loc->x + (dir<2 ? dir : 2-dir);
	neighbour.y = loc->y + (dir<3 ? dir-1 : 0);

	if(!(graph->in_bounds(graph, &neighbour) && graph->passable(graph, &neighbour)))
	{
		neighbour.x = -1;
		neighbour.y = -1;
	}

	return neighbour;
}

float grid_get_cost(pSquareGrid graph, pLocation loc)
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

