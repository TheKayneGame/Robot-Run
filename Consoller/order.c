/*
 * kayneLibs.c
 *
 *  Created on: May 11, 2018
 *      Author: Kayne
 */

#include "kayneLib.h"

//Function to return value of a read
int getLine(char *prmpt, char *buff, size_t sz) {
	int ch, extra;

	// Get line with buffer overrun protection.
	if (prmpt != NULL) {
		printf("%s", prmpt);
		fflush(stdout);
	}
	if (fgets(buff, sz, stdin) == NULL || buff[0] == '\n') {
		return IN_NULL;
	}

	// If it was too long, there'll be no newline. In that case, we flush
	// to end of line so that excess doesn't affect the next call.
	if (buff[strlen(buff) - 1] != '\n') {
		extra = 0;
		while (((ch = getchar()) != '\n') && (ch != EOF)) {
			extra = 1;
		}
		return (extra == 1) ? IN_OVF : OK;
	}

	// Otherwise remove newline and give string back to caller.
	buff[strlen(buff) - 1] = '\0';
	return OK;
}

void inputOrder(char port[16], int mode) {
	char *data;
	char data_to_send[2] = { '0', '\0' };
	int tel;
	HANDLE hComm;
	char readBuff[2024];
	FILE* stream = fopen("input.csv", "r");
	system("cls");

	int items = 0;

	switch (mode) {
	case 1:
		printf("Order invoer\n"
				"\n=======================================================\n"
				">1< Voer aantal Producten in\n"
				">2< Voer X Positie in\n"
				">3< Voer Y Positie in\n"
				"=======================================================\n\n");
		printf("Voer aantal Producten in: ");
		items = leesInteger();
		data = (char *) malloc(items * 2 + 1);
		orderManual(data, items * 2);
		break;
	case 2:

		while (fgets(readBuff, 1024, stream)) {
			items++;
		}
		data = (char *) malloc(items * 2 + 1);
		orderFile(data, items * 2);
		break;

	}
	data[0] = items;

	for (tel = 0; tel < (items * 2 + 1); tel++) {
		data_to_send[0] = data[tel];
		if (portAlive(port)) {
			hComm = openPort(port);
			sendByte(data_to_send, hComm);
			closePort(hComm);
		} else {
			Sleep(2000);
			tel = (items * 2);
		}
	}
	free(data);
	fclose(stream);
}

void orderManual(char *data, int size) {
	int coordIndex = 1;
	int item = 1;
	char buffer;
	while (coordIndex < size) {

		system("cls");
		printf("Order invoer\n"
				"\n=======================================================\n"
				">1< Voer aantal Producten in\n"
				">2< Voer X Positie in\n"
				">3< Voer Y Positie in\n"
				"=======================================================\n\n");
		printf("Voer aantal Producten in: %d\n", (size / 2));
		printf("Item >%d<\n", item);

		printf("\nX [%d]: ", item);
		buffer = leesInteger();

		data[coordIndex] = buffer;
		coordIndex++;

		printf("\nY [%d]: ", item);
		buffer = leesInteger();

		data[coordIndex] = buffer;
		coordIndex++;
	}
}

void orderFile(char *data, int size) {
	printfln("reading input.csv");
	fflush(stdout);
	FILE* stream = fopen("input.csv", "r");
	int coordIndex = 1;
	char line[1024];
	char buffX;
	char buffY;
	while (fgets(line, 1024, stream)) {

		char* tmp = strdup(line);

		buffX = atoi(getfield(tmp, 1));
		free(tmp);
		tmp = strdup(line);
		buffY = atoi(getfield(tmp, 2));
		free(tmp);

		data[coordIndex] = buffX;
		coordIndex++;
		data[coordIndex] = buffY;
		coordIndex++;

		printfln("X: %d; Y: %d", buffX, buffY);
		fflush(stdout);
	}

	fclose(stream);
	char key[1];
	fgets(key, 1, stdin);
}
