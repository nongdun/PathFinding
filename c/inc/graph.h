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
	float cost_so_far[MAP_WIDTH][MAP_WIDTH];
}Path, *pPath;

extern Location neighbours[4];
extern Location GetNeighbours(pSquareGrid graph, pLocation loc, int i);
extern int passable(pSquareGrid graph, pLocation loc);
extern float get_cost(pSquareGrid graph, pLocation loc);

extern void loc_copy(pLocation dest, pLocation source);
extern pLocation get_loc(pPath path, pLocation loc);
extern void set_loc(pPath path, pLocation loc, pLocation value);

extern pPath dijkstra_search(pSquareGrid graph, pLocation start, pLocation goal);
extern pPath a_star_search(pSquareGrid graph, pLocation start, pLocation goal);
extern void RestructPath(pPath search, pLocation start, pLocation goal);


#endif /* INC_GRAPH_H_ */
