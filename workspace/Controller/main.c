/*
 * main.c
 *
 *  Created on: May 11, 2018
 *      Author: Kayne
 */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "kayneLib.h"

#define TRUE 1
#define FALSE 0

int main() {
	setvbuf(stdout, NULL, _IONBF, 0);
	// Menu
	while (TRUE) {
		printfln("1. Manual Control");
		printfln("2. Queue Article");
		printfln("3. List Articles");
		printfln("4. Send instructions");
		printfln("5. Battery Level");
		printfln("6. Action Monitoring");
		int selection = leesInteger();

		switch (selection) {
		case 1:

			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
		case 5:

			break;
		case 6:

			break;

		default:
			printfln("Enter Valid Option");
			break;
		}
		system("cls");
	}
}

