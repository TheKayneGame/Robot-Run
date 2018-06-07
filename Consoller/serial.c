/*
 * kayneLibs.c
 *
 *  Created on: May 11, 2018
 *      Author: Kayne
 *      Commented: True
 */

#include "kayneLib.h"

int status;
HANDLE hComm;
char currPort[16];


//Controleert of de port nog levend is.
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

//Port open
HANDLE openPort(char port[16]) {
	HANDLE hComm;

	//Open port en maak handel aan
	hComm = CreateFile(port,            	//Port Naam
			GENERIC_READ | GENERIC_WRITE, 	//Lezen/Schrijven
			0,                            	//Niet delen
			NULL,                         	//Geen veiligheid
			OPEN_EXISTING,				  	//Open Bestaande poort
			0,            				  	//Niet-Overlappend I/O
			NULL);        				  	//NULL voor COM Apparaten

	//Controleert of de poort geopent kan wordern en sluit deze indien niet mogelijk
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

//Functie om port te sluiten
void closePort(HANDLE hComm) {
	CloseHandle(hComm);
}

//Functie om data te versturen
BOOL sendData(char buffByte[8], HANDLE hComm) {
	DWORD byteWritten = 0;
	int buffLen = strlen(buffByte); //Gets length of array

	//Probeert data in de handle te schrijven en geeft een foutmelding terug als deze mislukt is.
	if (!WriteFile(hComm, buffByte, buffLen, &byteWritten, NULL)) {
		printf("Err\n");
		return FALSE;
	} else {
		return TRUE;
	}
}

//function to read bytes NOT IN USE!!!!!!!!!!!!!!
BOOL readData(void *dataString, int *length, HANDLE hComm) {
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
///\/\/\/\/\/\/\/\/\/\/\NOT IN USE!!!!!!/\/\/\/\/\

void getCOM() {
	char port[7];
	char buffer[7];
	status = getLine("Voer COM Poort in: ", port, sizeof(port));

	//Checking for the errors found during input.
	if (status != IN_OVF || status != IN_NULL) {//gaat na of de situsatie normaal is
		sprintf(buffer, strupr(port));//Converteert alle karakters naar hoofdletter als zij dat niet waren
		if (buffer[0] == 'C' && buffer[1] == 'O' && buffer[2] == 'M') {
			//Controleert of COM port geldig is
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
			sprintf(currPort, "z\\\\.\\%s", strupr(port)); //Formateert de COM poort invoer naar geldige handle invoer
		}
	}
}

//functie om COM port invoer te accepteren
void setupCOM() {
	BOOL setupComplete = FALSE;

	system("cls");
	printf("COM Port instellingen\n"
			"\n=======================================================\n\n");
	while (!setupComplete) {
		getCOM();
		if (status != 0) {
			system("cls");
			printf(
					"Fout bij invoer COM port.\n"
							"De gevonden fout is >%d<\n"
							"\n=======================================================\n"
							">1< Geen Invoer.\n"
							">2< Invoer te lang.\n"
							">3< Invoer voldoet niet aan eisen\n"
							"=======================================================\n\n",
					status);
		} else {
			//Verificatie van COM Port
			printf("COM port wordt gecontroleerd\n");
			setupComplete = portAlive(currPort);
			Sleep(1000);
		}
		if (setupComplete) {
			printf("COM Port ingesteld en geinitialiseerd");
			Sleep(2000);
			system("cls");
		}
	}
}

