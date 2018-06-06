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

			case KEY_S:

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
	buffer[1] = 2;
	char sleep = '1';
	if (portAlive(port)) {
		hComm = openPort(port);
		sendByte("1", hComm);
		closePort(hComm);
	}


	printf("Handmatige besturing\n"
			"\n=======================================================\n"
			">1< Gebuik de pijltjes toetsen om te bewegen.\n"
			">2< Gebruik ESC om het terug te keren naar de selector\n"
			"=======================================================\n\n");
	while (active) {
		buffer[1] = keyboard();
		if (buffer[0] == 'p') {
			system("cls");
			hComm = openPort(port);
			sendByte(buffer, hComm);
			closePort(hComm);
			return FALSE;
		}

		else if (buffer[0] == 'w' || buffer[0] == 'a' || buffer[0] == 's'
				|| buffer[0] == 'd') {

			if (portAlive(port)) {
				hComm = openPort(port);
				sendByte(buffer, hComm);
				closePort(hComm);
			} else {
				Sleep(2000);
				return FALSE;
			}
		}

		else if (buffer[0] == '-') {
			if (sleep == '1') {
				printf(
						"Er is te lang geen invoer gedetecteerd wilt u stoppen met handmatige besturing?\n"
								"Enter >1< om te stoppen met handmatige besturing.\n"
								"Enter >2< om dese melding niet meer weer te geven.\n");
				sleep = getch();
				printf("%c\n", sleep);
				if (sleep == '1') {
					system("cls");
					return FALSE;
				} else {
					system("cls");
					printf(
							"Handmatige besturing\n"
									"\n=======================================================\n"
									">1< Gebuik de pijltjes toetsen om te bewegen.\n"
									">2< Gebruik ESC om het terug te keren naar de selector\n"
									"=======================================================\n\n");
				}
			}
		}
	}
	return TRUE;
}
