/*
 * serial.c
 *
 *  Created on: 4 apr. 2018
 *      Author: nickv
 */
#include "serial.h"
#include <windows.h>
#include <stdio.h>


//Function to open ports
HANDLE openPort(char port[16]) {
	HANDLE hComm;
	//Opening the commPort and creating the handle
	hComm = CreateFile(port,            //port name
			GENERIC_READ | GENERIC_WRITE, //Read/Write
			0,                            //No Sharing
			NULL,                         //No Security
			OPEN_EXISTING,				  //Open existing port only
			0,            				  //Non Overlapped I/O
			NULL);        				  //Null for Comm Devices

	if (hComm == INVALID_HANDLE_VALUE) {
		system("cls");
		printf(		"Er was een error tijdens het openen van de port\n"
					"\n=======================================================\n"
					">1< De ComPort is niet in staat geopend te worden.\n"
					"=======================================================\n\n");
		CloseHandle(hComm);
		return hComm;
	} else {
		return hComm;
	}
}

//Function to close the port
void closePort(HANDLE hComm) {
	CloseHandle(hComm);
}

//function to check connection with the CommPort
BOOL checkPort(char port[16]){
	BOOL result = FALSE;
	HANDLE hComm;
	hComm = openPort(port);
	if(hComm != INVALID_HANDLE_VALUE){
		result = TRUE;
	}
	closePort(hComm);
	return result;
}

//function to send bytes
BOOL sendByte(char bytes_to_send[8], HANDLE hComm) {
	DWORD bytes_written = 0;
	int size = strlen(bytes_to_send); //Gets the amount of bytes in the array

	if (!WriteFile(hComm, bytes_to_send, size, &bytes_written, NULL)) {
		printf("Error\n");
		return FALSE;
	} else {
		return TRUE;
	}
}

//function to read bytes
BOOL readByte(void *dataString, int *length, HANDLE hComm) {
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

