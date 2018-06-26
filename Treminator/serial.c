/*
 * kayneLibs.c
 *
 *  Created on: May 11, 2018
 *      Author: Kayne
 *      Tanks to: http://xanthium.in/Serial-Port-Programming-using-Win32-API
 */

#include "kayneLib.h"

int status;
HANDLE hComm;
char currPort[16];
BOOL portStatus;

BOOL portAlive(char port[16]) {
	BOOL result = FALSE;
	HANDLE hComm;
	hComm = openPort(port);

	if (hComm != INVALID_HANDLE_VALUE) {
		result = TRUE;
	}
	closePort(hComm);
	return result;
}

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
			NULL);        				  //Null for COM Devices

	if (hComm == INVALID_HANDLE_VALUE) {
		system("cls");
		printf("Fout bij openen COM port\n"
				"\n=======================================================\n"
				">1< Kan %s port niet openen\n"
				"=======================================================\n\n", port);
		CloseHandle(hComm);
	}

	DCB dcbSerialParams = { 0 };                   // Initializing DCB structure
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	portStatus = GetCommState(hComm, &dcbSerialParams); //retreives the current settings

	if (portStatus == FALSE) {
		printf("COM State Retrieval error");
		return 0;
	}

	dcbSerialParams.BaudRate 	= CBR_9600;      // Setting BaudRate = 9600
	dcbSerialParams.ByteSize	= 8;             // Setting ByteSize = 8
	dcbSerialParams.StopBits 	= ONESTOPBIT;    // Setting StopBits = 1
	dcbSerialParams.Parity 		= NOPARITY;      // Setting Parity = None

	portStatus = SetCommState(hComm, &dcbSerialParams); //Configuring the port according to settings in DCB

	if (portStatus == FALSE) {
		printf("DCB \n");
		return 0;
	}

	COMMTIMEOUTS timeouts = { 0 };

	timeouts.ReadIntervalTimeout         = 50; // in milliseconds
	timeouts.ReadTotalTimeoutConstant    = 50; // in milliseconds
	timeouts.ReadTotalTimeoutMultiplier  = 10; // in milliseconds
	timeouts.WriteTotalTimeoutConstant   = 50; // in milliseconds
	timeouts.WriteTotalTimeoutMultiplier = 10; // in milliseconds

	if (SetCommTimeouts(hComm, &timeouts) == FALSE) {
		printf("Error Setting timeout");
		return 0;
	}

	return hComm;
}

//Function to close the port
void closePort(HANDLE hComm) {
	CloseHandle(hComm);
}

//function to send bytes
void sendData(char *lpBuffer, HANDLE hComm) {
	DWORD dNoOFBytestoWrite;              	// PAckage size
	DWORD dNoOfBytesWritten = 0;          	// Package index
	dNoOFBytestoWrite = sizeof(&lpBuffer); 	// Define package size
	portStatus = WriteFile(hComm, lpBuffer, dNoOFBytestoWrite,
			&dNoOfBytesWritten,
			NULL); // Send the data
	printf("%s\n", lpBuffer);
}

//function to read bytes
void receiveData(HANDLE hComm) {
	DWORD dwEventMask;                     // Event mask to trigger
		char TempChar;                        // Temporary Buffer Character
		char SerialBuffer[10];               // Buffer Containing Rxed Data
		DWORD NoBytesRead;                     // Bytes read by ReadFile()
		int i = 0;

		portStatus = SetCommMask(hComm, EV_RXCHAR);

		if (portStatus == FALSE)
			printf("\n\n    Error! in Setting CommMask");

		portStatus = WaitCommEvent(hComm, &dwEventMask, NULL); //Wait for the character to be received
		printf("\nKOM HIER");
		/*-------------------------- Program will Wait here till a Character is received ------------------------*/

		if (portStatus == FALSE) {
			printf("\n    Error! in Setting WaitCommEvent()\n");
		} else {
			do {
				portStatus = ReadFile(hComm, &TempChar, sizeof(TempChar), &NoBytesRead,
				NULL);
				SerialBuffer[i] = TempChar;
				i++;
			} while (NoBytesRead > 0);

			/*------------Printing the RX Buffer----------------------*/
			//SerialBuffer[2] = '\0';
			printf("%s\n", SerialBuffer);
		}
}

void getComm() {
	char port[7];
	char buffer[7];
	status = getLine("Voer COM Poort in: ", port, sizeof(port));

	//Checking for the errors found during input.
	if (status != IN_OVF || status != IN_NULL) {
		sprintf(buffer, strupr(port));
		if (buffer[0] == 'C' && buffer[1] == 'O' && buffer[2] == 'M') {
			for (int i = 3; i < strlen(port); i++) {
				if (!isdigit(buffer[i]) || buffer[3] == '0') {
					status = IN_ERR;
				}
			}
			if (strlen(port) == 3) {
				status = IN_ERR;
			}
		}
		if (status != IN_ERR) {
			sprintf(currPort, "\\\\.\\%s", strupr(port)); // Edits the enterd portnumber to excepted paramiters
		}
	}
}

void commSetup() {
	BOOL setupComplete = FALSE;

	system("cls");
	printf("CommPort instellingen\n"
			"\n=======================================================\n\n");
	while (!setupComplete) {
		getComm();
		if (status != 0) {
			//Clear console and show found error;
			system("cls");
			printf(
					"Er was een error gevonden bij het invoeren van de port.\n"
							"De gevonde error was >%d<\n"
							"\n=======================================================\n"
							">1< Er was geen input gevonden.\n"
							">2< De ingevoerde was te lang.\n"
							">3< De input was niet gegeven volgens de juiste format\n"
							"=======================================================\n\n",
					status);
		} else {
			//ComPort gets checked, if it is able to be opend the program is allowed to proceed.
			printf("De port wordt gecheckt .....\n");
			setupComplete = portAlive(currPort);
			Sleep(1000);
		}
		if (setupComplete) {
			printf("De port is succesvol gecheckt.");
			Sleep(2000);
			system("cls");
		}
	}
}

void receive(char port[16]){
	if (portAlive(port)) {
					hComm = openPort(port);
					receiveData(hComm);
					closePort(hComm);}

}

