/*
 * kayneLibs.c
 *
 *  Created on: May 11, 2018
 *      Author: Kayne
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include <windows.h>
#include <stdio.h>


HANDLE openPort(char port[16]);

void closePort(HANDLE hComm);

BOOL portAlive(char port[16]);

BOOL sendData(char bytes_to_send[8], HANDLE hComm);

BOOL readData(void *dataString, int *length, HANDLE hComm);

HANDLE openPort(char port[16]);

void getComm();

void setupCOM();

extern char currPort[16];

extern int status;


#endif /* SERIAL_H_ */
