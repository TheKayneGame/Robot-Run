/*
 * commands.c
 *
 *  Created on: 5 Jun 2018
 *      Author: Kayne
 */

#include "kayneLib.h"

int battRequest(char port[16]) {
	HANDLE hComm;
	int* batt;
	int* length;
	length = 0;
	char* buff;
	buff = (char *) malloc(8 + 1);
	if (portAlive(port)) {
		hComm = openPort(port);
		sendData("BATTERY", hComm);
		closePort(hComm);
		readData(buff, length, hComm);
		printf("%s", buff);
	}

	return batt;
}
