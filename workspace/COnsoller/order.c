/*
 * order.c
 *
 *  Created on: 8 apr. 2018
 *      Author: nickv
 */

#include "order.h"
#include "serial.h"
#include "manual.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>

//Defines
#define OK				0
#define NO_INPUT		1
#define TOO_LONG		2
#define FORMAT_ERROR	3

//Function to return value of a read
int getLine(char *prmpt, char *buff, size_t sz) {
	int ch, extra;

	// Get line with buffer overrun protection.
	if (prmpt != NULL) {
		printf("%s", prmpt);
		fflush(stdout);
	}
	if (fgets(buff, sz, stdin) == NULL || buff[0] == '\n') {
		return NO_INPUT;
	}

	// If it was too long, there'll be no newline. In that case, we flush
	// to end of line so that excess doesn't affect the next call.
	if (buff[strlen(buff) - 1] != '\n') {
		extra = 0;
		while (((ch = getchar()) != '\n') && (ch != EOF)) {
			extra = 1;
		}
		return (extra == 1) ? TOO_LONG : OK;
	}

	// Otherwise remove newline and give string back to caller.
	buff[strlen(buff) - 1] = '\0';
	return OK;
}


void getOrder(char *data, int size){
	int tel = 0;
	int item = 1;
	char buffer;
	BOOL errorx = FALSE;
	BOOL errory = FALSE;


	while(tel < size){

		system("cls");
		printf(			"Order input\n"
						"\n=======================================================\n"
						">1< Geef het aantal items\n"
						">2< Geef de X waarde(0-5)\n"
						">3< Geef de Y waarde(0-5)\n"
						"=======================================================\n\n");
		printf("Het totaal aantal items: %d\n", (size/2));
		printf("Item >%d<\n", item);
		if(errorx || errory){
			printf("Er was een fout met het invoeren van het item, voer het item opnieuw in.\n");
		}
		errorx = FALSE;
		errory = FALSE;

		printf("\nDe X is: ");
		buffer = keyboard();
		printf("%c", buffer);
		if(isdigit(buffer)){
			data[tel+1] = buffer;
			tel++;
		}
		else{
			errorx = TRUE;
		}

		printf("\nDe Y is: ");
		buffer = keyboard();
		printf("%c", buffer);
		if(isdigit(buffer)){
			data[tel+1] = buffer;
			tel++;
		}
		else{
			errory = TRUE;
		}

		if(errory || errorx){
			if(!(errory && errorx)){
				tel --;
			}
		}

		if(!errory && !errorx){
			item++;
		}
	}
}

void inputOrder(char port[16]){
	char buffer;
	char *data;
	char data_to_send[2] = {'0', '\0'};
	int tel;
	HANDLE hComm;


	system("cls");
	printf(			"Order input\n"
					"\n=======================================================\n"
					">1< Geef het aantal items\n"
					">2< Geef de X waarde(0-6)\n"
					">3< Geef de Y waarde(0-6)\n"
					"=======================================================\n\n");
	printf("Het aantal items: ");
	buffer = getchar();
	if(isdigit(buffer)){
		int items = buffer - 48;
		data = (char *)malloc(items*2 + 1);
		data[0] = buffer;
		getOrder(data, items*2);

		for(tel = 0; tel < (items*2+1); tel++){
			data_to_send[0] = data[tel];
			if (checkPort(port)){
				hComm = openPort(port);
				sendByte(data_to_send, hComm);
				closePort(hComm);
			}
			else{
				Sleep(2000);
				tel = (items*2);
			}
		}
	}
	free(data);
}
