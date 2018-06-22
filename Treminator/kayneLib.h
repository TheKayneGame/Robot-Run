/*
 * kayneLibs.h
 *
 *  Created on: May 11, 2018
 *      Author: Kayne
 */

#ifndef KAYNELIB_H_
#define KAYNELIB_H_

#include "serial.h"
#include "order.h"
#include "manual.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <conio.h>
#include <Windows.h>
#include <time.h>

#define TRUE 			1
#define FALSE 			0

#define KEY_ARROW		224
#define KEY_ESC			27
#define KEY_UP			72
#define KEY_DOWN		80
#define KEY_LEFT		75
#define KEY_RIGHT		77
#define KEY_S			115

#define OK				0x0
#define IN_NULL			0x1
#define IN_OVF			0x2
#define IN_ERR			0x3

int leesInteger();
void printfln(const char*,...);
const char* getfield(char* line, int num);


#endif /* KAYNELIB_H_ */
