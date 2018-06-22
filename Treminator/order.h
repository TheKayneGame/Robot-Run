/*
 * kayneLibs.c
 *
 *  Created on: May 11, 2018
 *      Author: Kayne
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

void orderManual(char *data, int size);

void orderFile(char port[16], int mode);

void inputOrder(char port[16], int mode);
#endif /* ORDER_H_ */
