/*
 * order.h
 *
 *  Created on: 8 apr. 2018
 *      Author: nickv
 */

#ifndef ORDER_H_
#define ORDER_H_

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "manual.h"
#include "serial.h"

int getLine(char *prmpt, char *buff, size_t sz);

void getOrder(char *data, int size);

void inputOrder(char port[16]);

#endif /* ORDER_H_ */
