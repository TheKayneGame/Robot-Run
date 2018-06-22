/*
 * serial.h
 *
 *  Created on: 4 apr. 2018
 *      Author: nickv
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include <windows.h>
#include <stdio.h>


HANDLE openPort(char port[16]);

void closePort(HANDLE hComm);

BOOL checkPort(char port[16]);

BOOL sendByte(char bytes_to_send[8], HANDLE hComm);

BOOL readByte(void *dataString, int *length, HANDLE hComm);


#endif /* SERIAL_H_ */
