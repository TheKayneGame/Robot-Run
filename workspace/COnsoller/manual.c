/*
 * manual.c
 *
 *  Created on: 7 apr. 2018
 *      Author: nickv
 */

#define ESC		27
#define UP		72
#define DOWN	80
#define LEFT	75
#define RIGHT	77

#include "manual.h"
#include "serial.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

unsigned char keyboard() {
	int b, key;
	int time;

	for (time = 0; time <= 2000; time++) {	//waits 2000ms for an input
		b = kbhit();
		if (b != 0) {
			break;
		}
		Sleep(1);
	}
	if (b != 0) {
		key = getch();
		switch (key) {			// Returns a workable char when a key is pressed
		case ESC:
			return 'p';

		case UP:
			return 'w';

		case LEFT:
			return 'a';

		case DOWN:
			return 's';

		case RIGHT:
			return 'd';

		case 48:
			return '0';

		case 49:
			return '1';

		case 50:
			return '2';

		case 51:
			return '3';

		case 52:
			return '4';

		case 53:
			return '5';

		case 13:
			return 'i';

		default:
			return 'o';			// Invalid key returns a '0'
		}
	}
	return '-';					// In case of a key not being pressed returns '-'
}

BOOL manual(char port[16]) {
	BOOL active = TRUE;
	HANDLE hComm;
	char buffer[2] = {'0','\0'};
	char sleep = '1';


	printf( 		"Handmatige besturing\n"
					"\n=======================================================\n"
					">1< Gebuik de pijltjes toetsen om te bewegen.\n"
					">2< Gebruik ESC om het terug te keren naar de selector\n"
					"=======================================================\n\n");
	while (active) {
		buffer[0] = keyboard();
		if (buffer[0] == 'p') {
			system("cls");
			hComm =  openPort(port);
			sendByte(buffer, hComm);
			closePort(hComm);
			return FALSE;
		}

		else if (buffer[0] == 'w' || buffer[0] == 'a' || buffer[0] == 's' || buffer[0] == 'd') {
			//position to send the bytes and check connection;
			if (checkPort(port)){
				hComm = openPort(port);
				sendByte(buffer, hComm);
				closePort(hComm);
			}
			else{
				Sleep(2000);
				return FALSE;
			}
		}

		else if (buffer[0] == '-') {
			if (sleep == '1') {
				printf(	"Er is te lang geen invoer gedetecteerd wilt u stoppen met handmatige besturing?\n"
						"Enter >1< om te stoppen met handmatige besturing.\n"
						"Enter >2< om dese melding niet meer weer te geven.\n");
				sleep = getch();
				printf("%c\n", sleep);
				if(sleep == '1'){
					system("cls");
					return FALSE;
				}
				else{
					system("cls");
					printf( 		"Handmatige besturing\n"
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
