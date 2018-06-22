/*
 * main.c
 *
 *  Created on: 3 apr. 2018
 *      Author: nickv
 */
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "serial.h"
#include "manual.h"
#include "order.h"

//Defines
#define OK				0
#define NO_INPUT		1
#define TOO_LONG		2
#define FORMAT_ERROR	3

//Global variables
HANDLE hComm;
int error;
char adjusted_port[16];


void getComm() {
	char port[7];
	char buffer[7];
	int teller;
	error = getLine("Voer de naam in van de gebruikte CommPort: ",
			port, sizeof(port));

	//Checking for the errors found during input.
	if (error != TOO_LONG || error != NO_INPUT) {
		sprintf(buffer, strupr(port));
		if (buffer[0] == 'C' && buffer[1] == 'O' && buffer[2] == 'M') {
			for (teller = 3; teller < strlen(port); teller++) {
				if (!isdigit(buffer[teller]) || buffer[3] == '0') {
					error = FORMAT_ERROR;
				}
			}
			if(strlen(port) == 3){
				error = FORMAT_ERROR;
			}
		}
		if (error != FORMAT_ERROR) {
			sprintf(adjusted_port, "\\\\.\\%s", strupr(port)); // Edits the enterd portnumber to excepted paramiters
		} 	}
}

void commSetup(){
	BOOL setupComplete = FALSE;

	system("cls");
	printf(			"CommPort instellingen\n"
					"\n=======================================================\n\n");
		while (!setupComplete) {
			getComm();
			if (error != 0) {
				//Clear console and show found error;
				system("cls");
				printf(			"Er was een error gevonden bij het invoeren van de port.\n"
								"De gevonde error was >%d<\n"
								"\n=======================================================\n"
								">1< Er was geen input gevonden.\n"
								">2< De ingevoerde was te lang.\n"
								">3< De input was niet gegeven volgens de juiste format\n"
								"=======================================================\n\n",
								error);
			} else {
				//ComPort gets checked, if it is able to be opend the program is allowed to proceed.
				printf("De port wordt gecheckt .....\n");
				setupComplete = checkPort(adjusted_port);
				Sleep(1000);
			}
			if(setupComplete){
				printf("De port is succesvol gecheckt.");
				Sleep(2000);
				system("cls");
			}
		}
}

int main() {
	BOOL active = TRUE;
	char buffer[2];
	error = OK;


	system("cls");
	while(active){
		printf(				"Wireless polulu					V0.3\n"
							"\n=======================================================\n"
							">1< Handmatige besturing\n"
							">2< Orders invoeren\n"
							">3< CommPort instelling\n"
							">4< Exit program\n"
							"=======================================================\n\n");
		if(error != OK){
			printf("Er was een error gevonde met de ingevoerde actie.\n");
		}
		error = getLine("Voer een actie in: ",
				buffer, sizeof(buffer));
		if(buffer[0] != '1' || buffer[0] != '2' || buffer[0] != '3' || buffer[0] != '4'){
			error = FORMAT_ERROR;
			system("cls");
		}
		if(buffer[0] == '1'){
			error = OK;
			manual(adjusted_port);			//Manual control function
		}
		if(buffer[0] == '2'){
			error = OK;
			inputOrder(adjusted_port);
		}
		if(buffer[0] == '3'){
			error = OK;
			commSetup();		//CommSetup function
		}
		if(buffer[0] == '4'){
			system("cls");
			active = FALSE;		//Exit the complete program
		}
	}
	return 0;
}

