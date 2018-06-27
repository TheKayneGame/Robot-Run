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
	
	int orderX[sizeOfOrder] ={4, 1, 4, 2};
	int orderY[sizeOfOrder] ={4, 3, 1, 1};
	int itemsCount;
	wirCoord(orderX, orderY, &itemsCount);
	for (int i=0; i < itemsCount; i++)
	{
		
		
		lcd_goto_xy(0, 1);
		print_hex(orderX[i]);
		delay_ms(1000);
		lcd_goto_xy(0,0);
		print_hex(orderY[i]);
		delay_ms(1000);
		clear();
	}
	//sortOrder(orderX, orderY);
	
	int routes[5][8];
	readGrid(routes);
	
	int intersectnum = 0, endOfRoute = 0, orderNum = 0, xCoordinate = 0, yCoordinate = 0, x = 0;
	direction directionCurrent = N;
	
	int followLineFlag = 0;
	int productCollectedFlag = 0;
	
	
	while (orderNum != sizeOfOrder)
	{
		
		read_line_sensors(sensors,IR_EMITTERS_ON);
		
		if (checkAfslag() != 1 && productCollectedFlag == 0){
			checkDistance();
			followLine();
			followLineFlag = 1;
		}
		
		if (endOfRoute == 0 && checkAfslag() == 1){

			
			switch(routes[0][intersectnum]){
				case 1:
				set_motors(60,60);
				play_from_program_space(PSTR(">f32>>a32"));
				delay_ms(170);
				set_motors(0,0);
				
				motorControl(60, 'R', 0.25);
				
// 				set_motors(60,-60);
// 				delay_ms(270);
// 				set_motors(0,0);
				
				intersectnum++;
				break;
				case 2:
				set_motors(60,60);
				play_from_program_space(PSTR(">f32>>a32"));
				delay_ms(170);
				set_motors(0,0);
				
				motorControl(60, 'L', 0.25);
				
// 				set_motors(-60,60);
// 				delay_ms(270);
// 				set_motors(0,0);
				
				intersectnum++;
				break;
				case 3:
				motorControl(60, 'F', 0.89);
				intersectnum++;
				break;
				case 5:
				set_motors(0,0);
				delay_ms(1000);
				endOfRoute = 1;
				followLineFlag = 0;
				break;
			}
		}
		
		if ((endOfRoute == 1 && checkAfslag() == 1) || productCollectedFlag == 1){

			clear();
			lcd_goto_xy(0,0);
			print_long(xCoordinate);
			lcd_goto_xy(0,1);
			print_long(yCoordinate);
			
			if (productCollectedFlag == 0){
				set_motors(60,60);
				play_from_program_space(PSTR(">f32>>a32"));
				delay_ms(170);
				set_motors(0,0);
			}

			
			if (productCollectedFlag == 1){
				productCollectedFlag = 0;
			}
			
			if((orderX[orderNum] != xCoordinate) && (x == 0)){
				if(orderX[orderNum] > xCoordinate){

					setDirection(W, &directionCurrent);

					if (followLineFlag == 1){
						xCoordinate++;
						followLineFlag = 0;
					}
					
					clear();
					lcd_goto_xy(0,0);
					print_long(xCoordinate);
					lcd_goto_xy(0,1);
					print_long(yCoordinate);


				}
				if(orderX[orderNum] < xCoordinate){

					setDirection(E, &directionCurrent);
					
					if (followLineFlag == 1){
						xCoordinate--;
						followLineFlag = 0;
					}
					clear();
					lcd_goto_xy(0,0);
					print_long(xCoordinate);
					lcd_goto_xy(0,1);
					print_long(yCoordinate);

				}
			}
			if(orderX[orderNum] == xCoordinate){
				x = 1;
			}
			if((orderY[orderNum] != yCoordinate) && (x == 1)){
				if(orderY[orderNum] > yCoordinate){

					setDirection(N, &directionCurrent);
					
					if (followLineFlag == 1){
						yCoordinate++;
						followLineFlag = 0;
					}
					clear();
					lcd_goto_xy(0,0);
					print_long(xCoordinate);
					lcd_goto_xy(0,1);
					print_long(yCoordinate);


				}
				if(orderY[orderNum] < yCoordinate){

					setDirection(S, &directionCurrent);
					
					if (followLineFlag == 1){
						yCoordinate--;
						followLineFlag = 0;
					}
					clear();
					lcd_goto_xy(0,0);
					print_long(xCoordinate);
					lcd_goto_xy(0,1);
					print_long(yCoordinate);


				}
			}
			if((orderX[orderNum] == xCoordinate) && (orderY[orderNum] == yCoordinate)){
				set_motors(0,0);               //moeten we nog even naar kijken, hij moet gelijk stilstaan
				clear();
				print("Product");
				orderNum++;
				play_from_program_space(PSTR(">f32>>a32"));
				delay(3000);
				x = 0;
				productCollectedFlag = 1;
			}
		}
	}
}
