/* RR_version0.1 - an application for the Pololu 3pi Robot
*
* This application uses the Pololu AVR C/C++ Library.  For help, see:
* -User's guide: http://www.pololu.com/docs/0J20
* -Command reference: http://www.pololu.com/docs/0J18
*
* Created: 4/17/2018 6:33:30 PM
*  Author: Madita

A = licht sensor 1               1
B = licht sensor 2             2   3
C = licht sensor 3
D = licht sensor 4           4       5
E = licht sensor 5
F = afstands sensor

X = motor 1
Y = motor 2
*/

//long i = 0;
//
#include "Grid.h"
#include "wireless.h"
#include "sensoren.h"
#include "motoren.h"
#include <pololu/3pi.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>

int main(){
	initialize();
	
	int orderX[sizeOfOrder] ={4, 1, 4, 2, 4};
	int orderY[sizeOfOrder] ={4, 3, 1, 1, 0};

	int xCoordinate = 0, yCoordinate = 0, x = 0;
	direction directionCurrent = N;
	direction directionLast;
	
	//wirOrder(&orderX, &orderY);
	//Hoi
	
	sortOrder(orderX, orderY);
	
	int routes[5][8];
	int intersectNum = 0;
	readGrid(routes);
	
	int orderNum = 0;
	
	while (orderNum != sizeOfOrder)
	{
		
		read_line_sensors(sensors,IR_EMITTERS_ON);

		if (checkAfslag() != 1 && productCollectedFlag == 0){
			//checkDistance();
			followLine();
			followLineFlag = 1;

		}
		
		if (endOfRouteFlag == 0 && checkAfslag() == 1){

			driveRoute(routes, 0, &intersectNum);
			
		}
		
		if ((endOfRouteFlag == 1 && checkAfslag() == 1) || productCollectedFlag == 1){
			
			getProduct(orderX, orderY, &orderNum, &xCoordinate, &yCoordinate, &x, &directionCurrent, &directionLast);

		}
	}

	homeFlag = 0;
	intersectNum = 0;
	
	while (homeFlag != 1){

		read_line_sensors(sensors,IR_EMITTERS_ON);		

		if (checkAfslag() != 1){
			//checkDistance();
			followLine();

		}
		else if (checkAfslag() == 1){
			driveRoute(routes, 3, &intersectNum);
		}

	}
	
}
