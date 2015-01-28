/*
 * PathFinding.h
 *
 *  Created on: 2015年1月21日
 *      Author: Winder
 */

#ifndef INC_COMMON_H_
#define INC_COMMON_H_

#define MAP_WIDTH  (20)
#define MAP_HEIGHT (20)

#define TRUE  (1)
#define FALSE (0)

/*坐标结构体*/
typedef struct _Location
{
	int x;
	int y;
}Location, *pLocation;

typedef Location Item, *pItem;

#endif /* INC_COMMON_H_ */
