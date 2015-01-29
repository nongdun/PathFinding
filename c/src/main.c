/*
 * main.c
 *
 *  Created on: 2015年1月28日
 *      Author: Winder
 */


#include "header.h"

Queue frontier;
Path search = {20,20,{}};
Path path = {20,20,{}};
Path cost_so_far = {20,20,{}};

//Location start = {4,3};
Location start = {4,15};
Location goal  = {17,15};

SquareGrid map = {20, 20,
	{
 // 0001020304050607080910111213141516171819
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},   // 00
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},   // 01
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},   // 02
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},   // 03
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},   // 04
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},   // 05
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},   // 06
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},   // 07
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},   // 08
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},   // 09
	{1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1},   // 10
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},   // 11
	{1,1,1,1,1,1,1,1,1,5,1,1,1,1,1,1,1,1,1,1},   // 12
	{1,1,1,1,1,1,1,1,1,5,1,1,1,1,1,1,1,1,1,1},   // 13
	{1,1,1,1,1,1,1,1,1,5,1,1,1,1,1,1,1,1,1,1},   // 14
	{1,1,1,1,1,1,1,1,2,3,1,1,1,1,1,1,1,1,1,1},   // 15
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},   // 16
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},   // 17
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},   // 18
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}    // 11
	}
};

SquareGrid map2 = {20, 20,
	{
 // 0001020304050607080910111213141516171819
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},   // 00
	{1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,1},   // 01
	{1,9,9,1,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1},   // 02
	{1,9,9,1,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1},   // 03
	{1,9,1,1,1,1,9,9,1,9,1,9,1,1,1,1,9,9,1,1},   // 04
	{1,9,1,1,9,1,1,1,1,9,1,1,1,1,9,1,1,1,1,1},   // 05
	{1,9,9,9,9,1,1,1,1,1,1,9,9,9,9,1,1,1,1,1},   // 06
	{1,9,9,9,9,9,9,9,9,1,1,1,9,9,9,9,9,9,9,1},   // 07
	{1,9,1,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1},   // 08
	{1,9,1,9,9,9,9,9,9,9,1,5,9,9,9,9,9,9,9,1},   // 09
	{1,9,1,1,1,1,9,1,1,9,2,1,1,1,1,1,1,1,1,1},   // 10
	{1,9,9,9,9,9,1,9,1,9,1,9,9,9,9,9,1,1,1,1},   // 11
	{1,9,1,9,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1},   // 12
	{1,9,1,9,1,9,9,9,1,9,1,9,1,9,1,9,9,9,1,1},   // 13
	{1,9,1,1,1,1,9,9,1,9,1,9,1,1,1,1,9,9,1,1},   // 14
	{1,9,1,1,9,1,1,1,1,9,1,1,1,1,9,1,1,1,1,1},   // 15
	{1,9,9,9,9,1,1,1,1,1,1,9,9,9,9,1,1,1,1,1},   // 16
	{1,1,9,9,9,9,9,9,9,1,1,1,9,9,9,1,9,9,9,9},   // 17
	{1,9,1,1,1,1,1,1,1,1,1,9,1,1,1,1,1,1,1,1},   // 18
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}    // 19
	}
};

void draw_tile(pPath path, pLocation loc)
{
	char string[4];
	int i=0;
	int width = 3;

	if(path->came_from[loc->y][loc->x].x == loc->x+1)	//右
	{
		strcpy(string,"→");
		i=1;
	}
	if(path->came_from[loc->y][loc->x].x == loc->x-1)	//左
	{
		strcpy(string,"←");
		i=1;
	}
	if(path->came_from[loc->y][loc->x].y == loc->y+1)	//下
	{
		strcpy(string,"↓");
		i=1;
	}
	if(path->came_from[loc->y][loc->x].y == loc->y-1)	//上
	{
		strcpy(string,"↑");
		i=1;
	}
	if(path->came_from[loc->y][loc->x].x == 0 && path->came_from[loc->y][loc->x].y == 0)	//空
	{
		strcpy(string,".");
		i=0;
	}

#if 1
	if(passable(&map, loc) == 0)
	{
		strcpy(string,"#");
		i=0;
	}

	if((loc->x == start.x) && (loc->y == start.y))
	{
		strcpy(string,"S");
		i=0;
	}
	if(loc->x == goal.x && loc->y == goal.y)
	{
		strcpy(string,"G");
		i=0;
	}
#endif
	if(i)
	{
		printf("%*s",width+1,string);
	}
	else
	{
		printf("%*s",width,string);
	}

}

void DrawMap(pPath path, int style)
{
	int i=0, j=0;
	for(i=0; i<path->width; i++)
	{
		printf("%2d: ", i);
		for(j=0; j<path->height; j++)
		{
			Location loc;
			loc.x = j;
			loc.y = i;
			if(style == 1)
			{
				printf("(%2d,%2d)", path->came_from[i][j].x, path->came_from[i][j].y);
			}
			else if(style == 0)
			{
				draw_tile(path, &loc);
			}
			else
			{
				if(path->visited[i][j] == 1)
				{
					printf("* ");
				}
				else
				{
					printf(". ");
				}
			}
		}
		printf("\r\n");
	}
}

int main()
{
	int i=0, j=0;
	for(i=0;i<20;i++)
	{
		for(j=0;j<20;j++)
		{
			printf("%d ", map.cost[i][j]);
		}
		printf("\r\n");
	}

#if 1
	//breadth_first_search(&map, &start, &goal);
	dijkstra_search(&map, &start, &goal);
	DrawMap(&search, 0);
	printf("\r\n");

	RestructPath(&search, &start, &goal);
	DrawMap(&path, 0);
	printf("\r\n");

	memset(&search, 0, sizeof(search));
	search.width = 20;
	search.height = 20;
	memset(&path, 0, sizeof(search));
	path.width = 20;
	path.height = 20;

	queue_clear(&frontier);
#endif
	a_star_search(&map, &start, &goal);
	DrawMap(&search, 0);
	printf("\r\n");

	RestructPath(&search, &start, &goal);
	DrawMap(&path, 0);
	printf("\r\n");

	return 0;
}

