/*
 * kayneLibs.c
 *
 *  Created on: May 11, 2018
 *      Author: Kayne
 */

#include "kayneLib.h"

unsigned char keyboard() {
	int b, key;
	while (TRUE) {
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
					return 'o';
					break;
				}
				break;
			case KEY_SQUARE_BRACKET_OPEN:
				return '[';
				break;
			case KEY_SQUARE_BRACKET_CLOSE:
				return ']';
				break;

			case KEY_S:
				return 'S';
				break;
			case KEY_ESC:
				return 'p';
				break;

			}

		}
	}
}

BOOL manual(char port[16]) {
	BOOL active = TRUE;
	HANDLE hComm;
	char buffer[2] = { '0', '\0' };
	char sleep = '1';

	printf("Handmatige besturing\n"
			"\n=======================================================\n"
			">1< Gebuik de pijltjes toetsen om te bewegen.\n"
			">2< Gebruik ESC om het terug te keren naar de selector\n"
			"=======================================================\n\n");
	while (active) {
		buffer[0] = keyboard();
		if (buffer[0] == 'p') {
			system("cls");
			hComm = openPort(port);
			sendData(buffer, hComm);
			closePort(hComm);
			return FALSE;
		}

		else if (buffer[0] != '\0') {

			if (portAlive(port)) {
				hComm = openPort(port);
				sendData(buffer, hComm);
				closePort(hComm);
			} else {
				Sleep(2000);
				return FALSE;
			}
		}

	}

	return TRUE;
}
