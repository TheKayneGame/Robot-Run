/*
 * serial.c
 *
 *  Created on: May 12, 2018
 *      Author: Kayne
 */
#include "kayneLib.h"

BOOL Status;
HANDLE hComm;

const char ComPortName[] = "\\\\.\\COM24";

int initSerial() {

	hComm = CreateFile(ComPortName,             // Port name
			GENERIC_READ | GENERIC_WRITE,      // R/w Access
			0,                               // Disable Sharing
			NULL,                              // Disable Security
			OPEN_EXISTING,                     // Open existing port only
			0,                                 // Non Overlapped I/O
			NULL);                             // Null for Comm Devices

	if (hComm == INVALID_HANDLE_VALUE) {
		printfln("Incorrect COM Settings");
		return 0;
	}

	DCB dcbParameters = { 0 };                   // InitDCB
	dcbParameters.DCBlength = sizeof(dcbParameters);

	Status = GetCommState(hComm, &dcbParameters); //retreives  the current settings

	if (Status == FALSE) {
		printfln("Fail at Retrieves");
		return 0;
	}

	dcbParameters.BaudRate = CBR_115200;      // Setting BaudRate to 115200
	dcbParameters.ByteSize = 8;             // Setting ByteSize to 8
	dcbParameters.StopBits = ONESTOPBIT;    // Setting StopBits = 1
	dcbParameters.Parity = NOPARITY;      // Setting Parity = None

	COMMTIMEOUTS timeouttime = { 0 };

	timeouttime.ReadIntervalTimeout = 50; //Setting ReadIntervalTimeout to 50
	timeouttime.ReadTotalTimeoutConstant = 50; //Setting ReadTotalTimeoutConstant
	timeouttime.ReadTotalTimeoutMultiplier = 10; //Setting ReadTotalTimeoutMultiplier
	timeouttime.WriteTotalTimeoutConstant = 100; //Setting WriteTotalTimeoutConstant
	timeouttime.WriteTotalTimeoutMultiplier = 100; //Setting WriteTotalTimeoutMultiplier

	if (SetCommTimeouts(hComm, &timeouttime) == FALSE) {
		printfln("Failed setting timout");
		return 0;
	}

	Status = SetCommState(hComm, &dcbParameters); //Set port settings

	if (Status == FALSE) {
		printfln("DCB");
		return 0;
	} else {
		printfln("   DCB Setup Success\n");
		printfln("       Baudrate = %lu", dcbParameters.BaudRate);
		printfln("       ByteSize = %d", dcbParameters.ByteSize);
		printfln("       StopBits = %d", dcbParameters.StopBits);
		printfln("       Parity   = %d", dcbParameters.Parity);
	}

	return 1;
}

