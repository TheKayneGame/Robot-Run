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
	char buffer;
	char *data;
	char data_to_send[2] = { '0', '\0' };
	int tel;
	HANDLE hComm;

	system("cls");
	printf("Voer aantal Producten in: ");
	buffer = leesInteger();
	char items = buffer;
	data = (char *) malloc(items * 2 + 1);
	data[0] = buffer;

	switch (mode) {
	case 1:
		orderManual(data, items * 2);
		break;
	case 2:
		orderFile(data, items * 2);
		break;

	}
	printf("Orders versturen");
	for (tel = 0; tel < ((int) items * 2 + 1); tel++) {
		data_to_send[0] = data[tel];
		if (portAlive(port)) {
			hComm = openPort(port);
			sendData(data_to_send, hComm);
			closePort(hComm);
		} else {
			Sleep(2000);
			tel = (items * 2);
		}
	}

	free(data);

}

void orderManual(char *data, int size) {
	int coordIndex = 0;
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
		buffer = leesInteger() + '0';

		data[coordIndex + 1] = buffer;
		coordIndex++;

		printf("\nY [%d]: ", item);
		buffer = leesInteger() + '0';

		data[coordIndex + 1] = buffer;
		coordIndex++;
	}
}

int firstLine = TRUE;
void fixLine(char* line) {
	if (firstLine == TRUE) {
		for (int c = 0; c < sizeof(&line); c++) {
			if (c == sizeof(&line) - 1) {
				line[c] = 0;
			} else {
				line[c] = line[c + 3];
			}
		}
	}
	firstLine = FALSE;
}

void orderFile(char *data, int size) {
	printf("reading input.csv\n");
	fflush(stdout);
	FILE* stream = fopen("input.csv", "r");
	int coordIndex = 0;
	char line[1024];
	char buffX;
	char buffY;
	if (stream != NULL) {
		while (fgets(line, 1024, stream)) {
			char* tmp = _strdup(line);

			fixLine(tmp);
			buffX = atoi(getfield(tmp, 1));
			tmp = _strdup(line);
			fixLine(tmp);
			buffY = atoi(getfield(tmp, 2));

			data[coordIndex + 1] = buffX + '0';
			coordIndex++;
			data[coordIndex + 1] = buffY + '0';
			coordIndex++;

			printf("X: %d; Y: %d\n", buffX, buffY);
			free(tmp);
		}
		fclose(stream);
		char key[1];
		fgets(key, 1, stdin);
		printf("Bestand gesloten");
		return;
	}
	printf("*breathes in* boi");
}

