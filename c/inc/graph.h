/*
 * graph.h
 *
 *  Created on: 2015Äê1ÔÂ21ÈÕ
 *      Author: Winder
 */

#ifndef INC_GRAPH_H_
#define INC_GRAPH_H_

#include "header.h"

typedef struct _SquareGrid
{
	int width;
	int height;
	int cost[MAP_WIDTH][MAP_WIDTH];
}SquareGrid, *pSquareGrid;

typedef struct _Path
{
	int width;
	int height;
	int visited[MAP_WIDTH][MAP_WIDTH];
	Location came_from[MAP_WIDTH][MAP_WIDTH];
}Path, *pPath;

extern Location neighbours[4];
extern Location GetNeighbours(pSquareGrid graph, pLocation loc, int i);
extern int passable(pSquareGrid graph, pLocation loc);

#endif /* INC_GRAPH_H_ */
