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
	
	int orderX[sizeOfOrder] ={1, 1, 1, 1};
	int orderY[sizeOfOrder] ={4, 3, 3, 3};
	//wirMain(orderX, orderY);
	sortOrder(orderX, orderY);
	
	int routes[4][8];
	readGrid(routes);
	
	int intersectnum = 0, endOfRoute = 0, orderNum = 0, xCoordinate = 0, yCoordinate = 0, x = 0;
	direction directionCurrent = N;
	
	/*while(1){
	read_line_sensors(sensors,IR_EMITTERS_ON);
	lcd_goto_xy(0,0);
	print_long(SENSOR_L);
	lcd_goto_xy(0,1);
	print_long(SENSOR_R);
	delay_ms(1000);
	clear();
	}*/
	
	
	while (orderNum != sizeOfOrder)
	{
		read_line_sensors(sensors,IR_EMITTERS_ON);
		if (!checkAfslag()){
			followLine();
		}
		
		else if (!endOfRoute){
			set_motors(60,60);
			play_from_program_space(PSTR(">f32>>a32"));
			delay_ms(190);
			set_motors(0,0);
			
			switch(routes[0][intersectnum]){
				case 1:
				motorControl(60, 'R', 0.25);
				intersectnum++;
				break;
				case 2:
				motorControl(60, 'L', 0.25);
				intersectnum++;
				break;
				case 3:
				//motorControl(60, 'F', 0.89);
				intersectnum++;
				break;
				case 5:
				motorControl(0, 'F', 0.40);
				green_led(1);                            //Robot has reached destination
				play_from_program_space(PSTR(">f32>>a32"));
				delay_ms(1000);
				endOfRoute = 1;
				break;
			}
		}
		if(endOfRoute){
			if((orderX[orderNum] != xCoordinate) && (x == 0)){
				if(orderX[orderNum] > xCoordinate){
					setDirection(W, directionCurrent);
					delay_ms(250);
				}
				if(orderX[orderNum] < xCoordinate){
					setDirection(E, directionCurrent);
					delay_ms(250);
				}
				followStraightLine(&xCoordinate, orderX[orderNum]);
			}
			if(orderX[orderNum] == xCoordinate){
				x = 1;
			}
			if((orderY[orderNum] != yCoordinate) && (x == 1)){
				if(orderY[orderNum] > yCoordinate){
					setDirection(N, directionCurrent);
					delay_ms(250);
				}
				if(orderY[orderNum] < yCoordinate){
					setDirection(S, directionCurrent);
					delay_ms(250);
				}
				followStraightLine(&yCoordinate, orderY[orderNum]);
			}
			if((orderX[orderNum] == xCoordinate) && (orderY[orderNum] == yCoordinate)){
				set_motors(0,0);               //moeten we nog even naar kijken, hij moet gelijk stilstaan
				orderNum++;
				play_from_program_space(PSTR(">f32>>a32"));
				delay(3000);
			}			
		}
	}	
}
