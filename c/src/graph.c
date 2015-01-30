/*
 * graph.c
 *
 *  Created on: 2015��1��21��
 *      Author: Winder
 */

#include "header.h"

Location neighbours[4];

pSquareGrid grid_init();
int 	grid_in_bounds(pSquareGrid graph, pLocation loc);
int 	grid_passable(pSquareGrid graph, pLocation loc);
float	grid_get_cost(pSquareGrid graph, pLocation loc);
pLocation grid_get_neighbour(pSquareGrid graph, pLocation loc, Direction dir);

void 	search_set_cost_so_far(pSquareGrid graph, pLocation loc, float cost);
float 	search_get_cost_so_far(pSquareGrid graph, pLocation loc);
void 	search_set_came_from(pSquareGrid graph, pLocation loc, pLocation from);
void	search_set_visited(pSquareGrid graph, pLocation loc);
int		search_get_visited(pSquareGrid graph, pLocation loc);

pLocation location_init(int x, int y)					/*��ʼ������ṹ��*/
{
	pLocation loc = (pLocation)malloc(sizeof(Location));

	if(loc!= 0)
	{
		loc->x = x;
		loc->y = y;
	}

	return loc;
}

void location_destroy(pLocation loc)		/*ע������ṹ��*/
{
	free(loc);
}

pSquareGrid grid_init()
{
	pSquareGrid grid = (pSquareGrid)malloc(sizeof(SquareGrid));
	if(grid != NULL)
	{
		memset(grid, 0, sizeof(SquareGrid));
		grid->width = MAP_WIDTH;
		grid->height = MAP_HEIGHT;

		/*�󶨺���ָ��*/
		grid->in_bounds = grid_in_bounds;			/*�жϽڵ��Ƿ��ڵ�ͼ��*/
		grid->passable = grid_passable;				/*�жϽڵ��Ƿ����ͨ��*/
		grid->get_cost = grid_get_cost;				/*���ؽڵ�Ȩֵ*/
		grid->get_neighbour = grid_get_neighbour;	/*�������ڽڵ�����*/

		grid->set_cost_so_far = search_set_cost_so_far;
		grid->get_cost_so_far = search_get_cost_so_far;
		grid->set_came_from = search_set_came_from;
		grid->set_visited = search_set_visited;
		grid->get_visited = search_get_visited;
	}

	return grid;
}


/*�жϵ��Ƿ��ڵ�ͼ��*/
int grid_in_bounds(pSquareGrid graph, pLocation loc)
{
	return (loc->x >= 0) && (loc->x < graph->width)
		&& (loc->y >= 0) && (loc->y < graph->height);
}

/*�жϵ��Ƿ���ͨ��*/
int grid_passable(pSquareGrid graph, pLocation loc)
{
	return (graph->cost[loc->y][loc->x] < 9);
}

/*�������ڵ�����*/
pLocation grid_get_neighbour(pSquareGrid graph, pLocation loc, Direction dir)
{
	pLocation neighbour = (pLocation)malloc(sizeof(Location));
	if(neighbour != NULL)
	{
		switch(dir)
		{
			case Up:
				neighbour->x = loc->x;
				neighbour->y = loc->y - 1;
				break;
			case Right:
				neighbour->x = loc->x + 1;
				neighbour->y = loc->y;
				break;
			case Down:
				neighbour->x = loc->x;
				neighbour->y = loc->y + 1;
				break;
			case Left:
				neighbour->x = loc->x - 1;
				neighbour->y = loc->y;
				break;
			default:
				free(neighbour);
				return NULL;
		}

		//neighbour->x = loc->x + (dir<2 ? dir : 2-dir);
		//neighbour->y = loc->y + (dir<3 ? dir-1 : 0);

		if((graph->in_bounds(graph, neighbour) && graph->passable(graph, neighbour)))
		{
			return neighbour;		/*���ڵ�ͼ�ڣ����ҿ�ͨ��*/
		}
	}

	free(neighbour);
	return NULL;
}

float grid_get_cost(pSquareGrid graph, pLocation loc)
{
	return graph->cost[loc->y][loc->x];
}


void search_set_cost_so_far(pSquareGrid graph, pLocation loc, float cost)
{
	graph->cost_so_far[loc->y][loc->x] = cost;
}

float search_get_cost_so_far(pSquareGrid graph, pLocation loc)
{
	return graph->cost_so_far[loc->y][loc->x];
}

void search_set_came_from(pSquareGrid graph, pLocation loc, pLocation from)
{
	graph->came_from[loc->y][loc->x].x = from->x;
	graph->came_from[loc->y][loc->x].y = from->y;
}

void search_set_visited(pSquareGrid graph, pLocation loc)
{
	graph->visited[loc->y][loc->x] = 1;
}

int search_get_visited(pSquareGrid graph, pLocation loc)
{
	return graph->visited[loc->y][loc->x];
}

void grid_destroy(pSquareGrid map)
{
	free(map);
}

#if 0



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
#endif


