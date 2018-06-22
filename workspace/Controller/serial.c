/*
 * serial.c
 *
 *  Created on: May 12, 2018
 *      Author: Kayne
 */
#include "kayneLib.h"

BOOL Status;
HANDLE hComm;

const char ComPortName[] = "\\\\.\\COM3";

HANDLE openPort(char port[16]) {
	HANDLE hComm;
	//Opening the commPort and establish the handle
	hComm = CreateFile(port,            //port name
			GENERIC_READ | GENERIC_WRITE, //Read/Write
			0,                            //No Sharing
			NULL,                         //No Security
			OPEN_EXISTING,				  //Open existing port only
			0,            				  //Non Overlapped I/O
			NULL);        				  //Null for Comm Devices

	if (hComm == INVALID_HANDLE_VALUE) {
		system("cls");
		printf(		"Fout tijdens openen poort\n"
					"\n=======================================================\n"
					">1< COM Poort niet in staat om te openen.\n"
					"=======================================================\n\n");
		CloseHandle(hComm);
		return hComm;
	} else {
		return hComm;
	}
}

void closePort(HANDLE hComm) {
	CloseHandle(hComm);
}

BOOL portAlive(char port[16]){
	BOOL result = FALSE;
	HANDLE hComm;
	hComm = openPort(port);
	if(hComm != INVALID_HANDLE_VALUE){
		result = TRUE;
	}
	closePort(hComm);
	return result;
}

BOOL sendPacket(char bytesOut[8], HANDLE hComm) {
	DWORD bytes_written = 0;
	int size = strlen(bytesOut); //Gets the amount of bytes in the array

	if (!WriteFile(hComm, bytesOut, size, &bytes_written, NULL)) {
		printf("Error\n");
		return FALSE;
	} else {
		return TRUE;
	}
}

BOOL readPacket(void *dataString, int *length, HANDLE hComm) {
	BOOL active = TRUE;
	byte dataout[4096] = { 0 };
	byte buffer = 0;
	DWORD dwBytesTransferred = 0;
	int index = 0;

	while (active == TRUE) {
		if (ReadFile(hComm, &buffer, 1, &dwBytesTransferred, 0) > 0) {
			if (dwBytesTransferred == 1) {
				dataout[index++] = buffer;
				active = TRUE;
			} else {
				active = FALSE;
			}
		} else {
			active = FALSE;
		}
	}
	memcpy(dataString, dataout, index);
	*length = index;
	return TRUE;
}
