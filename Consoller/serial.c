/*
 * kayneLibs.c
 *
 *  Created on: May 11, 2018
 *      Author: Kayne
 */

#include "kayneLib.h"

int status;
HANDLE hComm;
char currPort[16];

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
				">1< Kan COM port niet openen\n"
				"=======================================================\n\n");
		CloseHandle(hComm);
	}
	return hComm;
}

//Function to close the port
void closePort(HANDLE hComm) {
	CloseHandle(hComm);
}

//function to send bytes
BOOL sendByte(char buffByte[8], HANDLE hComm) {
	DWORD byteWritten = 0;
	int buffLen = strlen(buffByte); //Gets length of array

	if (!WriteFile(hComm, buffByte, buffLen, &byteWritten, NULL)) {
		printf("Err\n");
		return FALSE;
	} else {
		return TRUE;
	}
}

//function to read bytes
BOOL readByte(void *dataString, int *length, HANDLE hComm) {
	BOOL active = TRUE;
	byte dataout[2048] = { 0 };
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

