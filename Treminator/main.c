/*
 * kayneLibs.c
 *
 *  Created on: May 11, 2018
 *      Author: Kayne
 */
#include "kayneLib.h"

int main() {

	BOOL active = TRUE;
	char buffer[2];
	status = OK;

	system("cls");
	while (active) {
		printf("Wixel				V0.3\n"
				"\n=======================================================\n"
				">1< Handmatige besturing\n"
				">2< Orders invoeren\n"
				">3< Orders inladen\n"
				">4< COM Port\n"
				">5< Exit program\n"
				"=======================================================\n\n");
		if (status != OK) {
			printf("Foute Actie\n");
		}
		status = getLine("Voer een actie in: ", buffer, sizeof(buffer));

		switch (buffer[0] - '0') {
		case 1:
			status = OK;
			manual(currPort);
			break;
		case 2:
			status = OK;
			inputOrder(currPort, 1);
			break;
		case 3:
			status = OK;
			inputOrder(currPort, 2);
			break;
		case 4:
			status = OK;
			commSetup();
			break;

		case 5:
			status = OK;
			receive(currPort);
			break;

		case 6:
			system("cls");
			active = FALSE;
			break;
		default:
			status = IN_ERR;
			system("cls");
			break;
		}

	}
	return 0;
}

