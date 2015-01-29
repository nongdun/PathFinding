/*
 * header.h
 *
 *  Created on: 2015��1��21��
 *      Author: Winder
 */

#ifndef INC_HEADER_H_
#define INC_HEADER_H_

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

#include "common.h"
#include "priority_queue.h"
#include "graph.h"

extern Queue frontier;
extern Path search;
extern Path path;
extern Path cost_so_far;

extern Location start;
extern Location goal;

extern SquareGrid map;

#endif /* INC_HEADER_H_ */
