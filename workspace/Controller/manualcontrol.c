/*
 * manualcontrol.c
 *
 *  Created on: May 12, 2018
 *      Author: Kayne
 */
#include "kayneLib.h"

void manualControl() {
	printf("inpunt234234234");
	int b, key;
	while (TRUE) {
		b = kbhit();
		//DONT FORGET TO TURN THIS INTO CASE SWITCH WHEN ITS GETTING TO LARGE... NVM NEEDS TO BE CASE SWITCH
		if (b != 0) {
			switch (getch()) {
			case 224:
				key = getch();
				switch (key) {
				case KEY_UP:
					printfln("up");
					break;
				case KEY_LEFT:
					printfln("left");
					break;
				case KEY_DOWN:
					printfln("down");
					break;
				case KEY_RIGHT:
					printfln("right");
					break;
				default:
					printf("%i \n", key);
					break;
				}
				break;

			case KEY_ESC:
				return;
				break;

			}

		}
	}

	/*while (TRUE) {
	 if (getch() == '\033') {
	 getch();
	 switch (getch()) {
	 case 'A':
	 printfln("up");
	 break;
	 case 'B':
	 printfln("up");
	 break;
	 case 'C':
	 printfln("up");
	 break;
	 case 'D':
	 printfln("up");
	 break;
	 }
	 }

	 if (getch() == 'E') {
	 break;
	 }
	 }*/
}


