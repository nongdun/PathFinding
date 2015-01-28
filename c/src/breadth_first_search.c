
#include "header.h"

Queue frontier;
Path search = {20,20,{}};
Path path = {20,20,{}};

Location start = {4,3};
Location goal  = {17,15};

SquareGrid map = {20, 20,
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
	{1,9,1,9,9,9,9,9,9,9,1,1,9,9,9,9,9,9,9,1},   // 09
	{1,9,1,1,1,1,9,1,1,9,1,1,1,1,1,1,1,1,1,1},   // 10
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

/*广度搜索*/
pPath breadth_first_search(pSquareGrid graph, pLocation start, pLocation goal)
{
	queue_push(&frontier, start);
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
				queue_push(&frontier, &neighbour);
				set_loc(&search, &neighbour, &current);
				search.visited[neighbour.y][neighbour.x] = 1;
			}
		}
	}
	return &search;
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

	breadth_first_search(&map, &start, &goal);
	RestructPath(&search, &start, &goal);
	DrawMap(&search, 0);
	printf("\r\n");
	DrawMap(&path, 0);
	printf("\r\n");

	return 0;
}

