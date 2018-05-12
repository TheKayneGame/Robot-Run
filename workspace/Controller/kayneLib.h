/*
 * kayneLibs.h
 *
 *  Created on: May 11, 2018
 *      Author: Kayne
 */

#ifndef KAYNELIB_H_
#define KAYNELIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <conio.h>
#include <Windows.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

#define KEY_ESC		27
#define KEY_UP		72
#define KEY_DOWN	80
#define KEY_LEFT	75
#define KEY_RIGHT	77

int leesInteger();
void printfln(const char*,...);


#endif /* KAYNELIB_H_ */
