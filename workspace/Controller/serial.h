/*
 * serial.h
 *
 *  Created on: May 12, 2018
 *      Author: Kayne
 */

#ifndef SERIAL_H_
#define SERIAL_H_

HANDLE openPort(char port[16]);

void closePort(HANDLE hComm);

BOOL portAlive(char port[16]);

BOOL sendPacket(char bytesOut[8], HANDLE hComm);

BOOL readPacket(void *dataString, int *length, HANDLE hComm);


#endif /* SERIAL_H_ */
