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

int main(){
	
	int orderX[sizeOfOrder] = { 2, 5, 3, 4};    // replace with user input
	int orderY[sizeOfOrder] = { 3, 1, 4, 2};    // replace with user input
	sortOrder(orderX, orderY);
				
}