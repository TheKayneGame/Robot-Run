/*
 * manualcontrol.c
 *
 *  Created on: May 12, 2018
 *      Author: Kayne
 */
#include "kayneLib.h"

void manualControl() {
	HANDLE hComm =  openPort(port);
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

			case KEY_S:

				break;
			case KEY_ESC:
				return;
				break;

			}

		}
	}

}

void composeEmergencyStop() {

	byte packet[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
	sendPacket(packet,hComm);
}

void composeMovPacket(byte action, byte speed) {

	byte packet[8] = {};
	packet[0] = 1;
	packet[1] = action;
	packet[2] = speed;
	sendPacket(packet,hComm);
}

