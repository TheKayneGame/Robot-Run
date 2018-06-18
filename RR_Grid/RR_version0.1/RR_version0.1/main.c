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

long i = 0;

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
	motorControl(100, 'F', 0.86);
	delay(3000);
	motorControl(0, 'F', 0.86);
	//int routes[4][4];
	//readGrid(routes);
	/*int orderX[sizeOfOrder];
	int orderY[sizeOfOrder];
	wirCoord();
	wirMain(orderX, orderY);
	sortOrder(orderX, orderY);
	clear();*/
	//driveRoute(routes, 1);
	//fetchOrder(orderX, orderY, routes);
	
}