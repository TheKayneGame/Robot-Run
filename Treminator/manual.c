/*
 * kayneLibs.c
 *
 *  Created on: May 11, 2018
 *      Author: Kayne
 */

#include "kayneLib.h"

int keyboard() {
	int b, key;
	while (1) {
		b = kbhit();
		if (b != 0) {

			switch (getch()) {
			case 224:
				key = getch();
				switch (key) {
				case KEY_UP:
					return 'w';
					break;
				case KEY_LEFT:
					return 'a';
					break;
				case KEY_DOWN:
					return 's';
					break;
				case KEY_RIGHT:
					return 'd';
					break;
				default:
					return 0;
					break;
				}
				break;

			case KEY_BRACKET_O:
				return '[';
				break;

			case KEY_BRACKET_C:
				return ']';
				break;

			case KEY_S:
				return 's';
				break;
			case KEY_ESC:
				return 'p';
				break;
			default:
				return 0;
				break;

			}
		}
	}
	return 0;
}

BOOL manual(char port[16]) {
	BOOL active = TRUE;
	HANDLE hComm;
	char buffer[2] = { 0, '\0' };
	char bufferPrev[2] = { 0, '\0' };

	printf("Handmatige besturing\n"
			"\n=======================================================\n"
			">1< Gebuik de pijltjes toetsen om te bewegen.\n"
			">2< Gebruik ESC om het terug te keren naar de selector\n"
			"=======================================================\n\n");
	while (active) {

		buffer[0] = keyboard();
		if (1/*buffer[0] != bufferPrev[0]*/) {

			if (portAlive(port)) {
				hComm = openPort(port);
				sendData(buffer, hComm);
				CloseHandle(hComm);
				bufferPrev[0] = buffer[0];
			}

			if (buffer[0] == 'p') {
				break;
			}
		}

	}
	return TRUE;
}

void retrieveBatteryStatus(char port[16]) {
	HANDLE hComm;
	char buffer[2] = { 0, '\0' };
	buffer[0] = 'b';
	if (portAlive(port)) {
		hComm = openPort(port);
		sendData(buffer, hComm);
		CloseHandle(hComm);
	}
	if (portAlive(port)) {
		hComm = openPort(port);
		receiveData(hComm);
		CloseHandle(hComm);
	}

}
