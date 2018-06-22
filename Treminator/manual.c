/*
 * kayneLibs.c
 *
 *  Created on: May 11, 2018
 *      Author: Kayne
 */

#include "kayneLib.h"

char * keyboard() {
	int b, key;
	while (TRUE) {
		b = kbhit();
		if (b != 0) {
			switch (getch()) {
			case 224:
				key = getch();
				switch (key) {
				case KEY_UP:
					return "101";
					break;
				case KEY_LEFT:
					return "103";
					break;
				case KEY_DOWN:
					return "102";
					break;
				case KEY_RIGHT:
					return "104";
					break;
				default:
					return "222";
					break;
				}
				break;

			case KEY_S:

				break;
			case KEY_ESC:
				return "p";
				break;
			default:
				return "222";
				break;

			}

		}else{return "222";}
	}
}

BOOL manual(char port[16]) {
	BOOL active = TRUE;
	HANDLE hComm;
	char buffer[8] = "222";
	char bufferPrev[8] = "222";

	printf("Handmatige besturing\n"
			"\n=======================================================\n"
			">1< Gebuik de pijltjes toetsen om te bewegen.\n"
			">2< Gebruik ESC om het terug te keren naar de selector\n"
			"=======================================================\n\n");
	while (active) {
		strcpy(buffer, keyboard());
		if (!strcmp(buffer, bufferPrev)) {
			printfln("nop");
			continue;
		}
		strcpy(bufferPrev, buffer);

		if (!strcmp(buffer, "p")) {
			system("cls");
			hComm = openPort(port);
			sendData(buffer, hComm);
			closePort(hComm);
			return FALSE;
		}

		else {
			//position to send the bytes and check connection;
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
