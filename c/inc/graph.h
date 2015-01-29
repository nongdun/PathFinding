/*
 * graph.h
 *
 *  Created on: 2015年1月21日
 *      Author: Winder
 */

#ifndef INC_GRAPH_H_
#define INC_GRAPH_H_

#include "header.h"

typedef enum _Direction
{
	Up	  = 0,
	Right = 1,
	Down  = 2,
	Left  = 3
}Direction, *pDirection;

/*坐标结构体*/
typedef struct _Location
{
	int x;
	int y;
}Location, *pLocation;

typedef Location Item, *pItem;

typedef struct _SquareGrid
{
	int width;
	int height;
	int cost[MAP_WIDTH][MAP_WIDTH];

	int 	 (*in_bounds)(struct _SquareGrid *graph, pLocation loc);
	int 	 (*passable)(struct _SquareGrid *graph, pLocation loc);
	float 	 (*get_cost)(struct _SquareGrid *graph, pLocation loc);
	Location (*get_neighbour)(struct _SquareGrid *graph, pLocation loc, Direction dir);
}SquareGrid, *pSquareGrid;

typedef struct _Path
{
	int width;
	int height;
	int visited[MAP_WIDTH][MAP_WIDTH];
	Location came_from[MAP_WIDTH][MAP_WIDTH];
	float cost_so_far[MAP_WIDTH][MAP_WIDTH];
}Path, *pPath;

extern Location neighbours[4];

extern pSquareGrid grid_init();		/*初始化地图结构体*/

extern void loc_copy(pLocation dest, pLocation source);
extern pLocation get_loc(pPath path, pLocation loc);
extern void set_loc(pPath path, pLocation loc, pLocation value);

extern pPath dijkstra_search(pSquareGrid graph, pLocation start, pLocation goal);
extern pPath a_star_search(pSquareGrid map, pLocation start, pLocation goal);
extern void RestructPath(pPath search, pLocation start, pLocation goal);


#endif /* INC_GRAPH_H_ */
