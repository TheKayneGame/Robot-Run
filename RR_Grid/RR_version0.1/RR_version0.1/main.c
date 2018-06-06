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

#include "Grid.h"
#include <pololu/3pi.h>
#include <avr/pgmspace.h>
#include "wireless.h"
#include "sensoren.h"
#include "motoren.h"

int main(){
	initialize();
	int amountOfIntersects = 0;
	int routes[2][20];
    amountOfIntersects = readGrid(routes);
	int orderX[sizeOfOrder];
	int orderY[sizeOfOrder];
	wirMain(orderX, orderY);
	sortOrder(orderX, orderY);
	driveRoute(routes, 1, 0, amountOfIntersects);
	fetchOrder(orderX, orderY, routes);	
				
}