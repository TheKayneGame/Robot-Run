/*
* Grid.c
*
* Created: 8-5-2018 18:29:21
*  Author: Madita
*/

#include "Grid.h"
#include "sensoren.h"
#include "motoren.h"
#include <math.h>
#include <pololu/3pi.h>
#include <avr/pgmspace.h>

int positionCurrentX, positionCurrentY;

int followLineFlag;
int productCollectedFlag;
int endOfRouteFlag;
int homeFlag;


void swapTwo( int *firstXValue, int *secondXValue, int *firstYValue, int *secondYValue){                //Swap function for the coordinates
	int temp;

	temp = *secondXValue;                                                                               //Swap X-Coordinates
	*secondXValue = *firstXValue;
	*firstXValue = temp;

	temp = *secondYValue;                                                                               //Swap Y-Coordinates
	*secondYValue = *firstYValue;
	*firstYValue = temp;
}

void swapOne(int *firstValue, int *secondValue) {                                                  //Swap function for the distance array
	int temp;

	temp = *secondValue;
	*secondValue = *firstValue;
	*firstValue = temp;
}

void sortOrder(int XC[sizeOfOrder], int YC[sizeOfOrder]) {                                                                   //Sorting algorithm, this sorts the coordinates of the given order
	int check = 0, orderCorrect;
	int sum[sizeOfOrder];

	for (int j = 0; j < (sizeOfOrder-1); j++) {
		sum[j] = XC[j] + YC[j];
	}
	while (check != 1) {
		orderCorrect = 1;
		for (int i = 0; i < (sizeOfOrder-1); i++) {
			if (sum[i] > sum[i + 1]) {
				swapOne(&sum[i], &sum[i + 1]);
				swapTwo(&XC[i], &XC[i + 1], &YC[i], &YC[i + 1]);
				orderCorrect = 0;
				} else if ((sum[i] == sum[i + 1]) && (YC[i] == YC[i + 1])) {
				if (XC[i] < XC[i + 1]) {
					swapOne(&sum[i], &sum[i + 1]);
					swapTwo(&XC[i], &XC[i + 1], &YC[i], &YC[i + 1]);
					orderCorrect = 0;
					} else if (YC[i] > YC[i + 1]) {
					swapOne(&sum[i], &sum[i + 1]);
					swapTwo(&XC[i], &XC[i + 1], &YC[i], &YC[i + 1]);
					orderCorrect = 0;
				}
			}
		}
		if (orderCorrect == 1) {
			check = 1;
		}

	}

}

void readGrid(int routes[5][8]){
	
	routes[0][0] = 2;                                                                         //Home to grid
	routes[0][1] = 1;
	routes[0][2] = 2;
	routes[0][3] = 1;
	routes[0][4] = 1;
	routes[0][5] = 3;
	routes[0][6] = 2;
	routes[0][7] = 5;
	
	routes[1][0] = 1;                                                                        //Home to charge point
	routes[1][1] = 1;
	routes[1][2] = 5;
	
	routes[2][0] = 3;                                                                        //Grid to charge point
	routes[2][1] = 3;
	routes[2][2] = 5;
	
	routes[3][0] = 3;                                                                        //Grid to home
	routes[3][1] = 1;
	routes[3][2] = 2;
	routes[3][3] = 1;
	routes[3][4] = 2;
	routes[3][5] = 5;
	
	routes[4][0] = 3;                                                                       //Charge point to grid
	routes[4][1] = 2;
	routes[4][2] = 3;
	routes[4][3] = 5;
	
}

void setDirection(direction directionDesired, direction *directionCurrent){
	rotation orientation[4][4] ={{X, R, T, L},
	{L, X, R, T},
	{T, L, X, R},
	{R, T, L, X}};
	
	if(*directionCurrent != directionDesired){
		switch(orientation[directionDesired][*directionCurrent]){
			case R:
			
			set_motors(60,-60);
			delay_ms(270);
			set_motors(0,0);
			
			//motorControl(60, 'R', 0.25);

			*directionCurrent = directionDesired;
			break;
			case L:
			
			set_motors(-60,60);
			delay_ms(270);
			set_motors(0,0);
			
			//motorControl(60, 'L', 0.25);

			*directionCurrent = directionDesired;
			break;
			case T:
			
			set_motors(60,-60);
			delay_ms(540);
			set_motors(0,0);
			
			//motorControl(60, 'R', 0.25);
			//motorControl(60, 'R', 0.25);

			*directionCurrent = directionDesired;
			break;
			default:
			break;
			clear();
		}
	}
	
}

void driveRoute(int routes[5][8], int route, int *intersectNum){

	switch(routes[route][*intersectNum]){
		case 1:
		set_motors(60,60);
		delay_ms(170);
		set_motors(0,0);
		
		//motorControl(60, 'R', 0.25);
		
		 				set_motors(60,-60);
						delay_ms(270);
		 				set_motors(0,0);
		
		*intersectNum = *intersectNum + 1;
		break;
		case 2:
		set_motors(60,60);
		delay_ms(170);
		set_motors(0,0);
		
		//motorControl(60, 'L', 0.25);
		
		 				set_motors(-60,60);
		 				delay_ms(270);
		 				set_motors(0,0);
		
		*intersectNum = *intersectNum + 1;
		break;
		case 3:
		set_motors(60,60);
		delay_ms(170);
		set_motors(0,0);
		*intersectNum = *intersectNum + 1;
		break;
		case 5:
		set_motors(0,0);
		endOfRouteFlag = 1;
		followLineFlag = 0;
		*intersectNum = 0;
		homeFlag = 1;

		break;
	}
}

void getProduct(int orderX[sizeOfOrder], int orderY[sizeOfOrder], int *orderNum, int *xCoordinate, int *yCoordinate, int *x, direction *directionCurrent, direction *directionLast){
	
	clear();
	lcd_goto_xy(0,0);
	print_long(*xCoordinate);
	lcd_goto_xy(0,1);
	print_long(*yCoordinate);
	
	if (productCollectedFlag == 0){
		set_motors(60,60);
		delay_ms(170);
		set_motors(0,0);
	}

	if (productCollectedFlag == 1){
		productCollectedFlag = 0;
	}

	if((orderX[*orderNum] != *xCoordinate) && (*x == 0)){
		if(orderX[*orderNum] > *xCoordinate){
			directionLast = directionCurrent;
			setDirection(W, directionCurrent);
			if (followLineFlag == 1){
				*xCoordinate = *xCoordinate + 1;
				followLineFlag = 0;
			}
			
			clear();
			lcd_goto_xy(0,0);
			print_long(*xCoordinate);
			lcd_goto_xy(0,1);
			print_long(*yCoordinate);

		}
		if(orderX[*orderNum] < *xCoordinate){
			directionLast = directionCurrent;
			setDirection(E, directionCurrent);
			
			if (followLineFlag == 1){
				*xCoordinate = *xCoordinate - 1;
				followLineFlag = 0;
			}
			clear();
			lcd_goto_xy(0,0);
			print_long(*xCoordinate);
			lcd_goto_xy(0,1);
			print_long(*yCoordinate);

		}
	}
	if(orderX[*orderNum] == *xCoordinate){
		*x = 1;
	}
	if((orderY[*orderNum] != *yCoordinate) && (*x == 1)){
		if(orderY[*orderNum] > *yCoordinate){
			directionLast = directionCurrent;
			setDirection(N, directionCurrent);
			
			if (followLineFlag == 1){
				*yCoordinate = *yCoordinate + 1;
				followLineFlag = 0;
			}
			clear();
			lcd_goto_xy(0,0);
			print_long(*xCoordinate);
			lcd_goto_xy(0,1);
			print_long(*yCoordinate);

		}
		if(orderY[*orderNum] < *yCoordinate){
			directionLast = directionCurrent;
			setDirection(S, directionCurrent);
			
			if (followLineFlag == 1){
				*yCoordinate = *yCoordinate- 1;
				followLineFlag = 0;
			}
			clear();
			lcd_goto_xy(0,0);
			print_long(*xCoordinate);
			lcd_goto_xy(0,1);
			print_long(*yCoordinate);

		}
	}

	if((orderX[*orderNum] == *xCoordinate) && (orderY[*orderNum] == *yCoordinate)){
		set_motors(0,0);               //moeten we nog even naar kijken, hij moet gelijk stilstaan
		clear();
		print("Product");
		*orderNum = *orderNum + 1;

		if (*orderNum == sizeOfOrder){
			setDirection('S', directionCurrent);
		}
		play_from_program_space(PSTR(">f32>>a32"));
		delay(1000);
		*x = 0;
		productCollectedFlag = 1;
	}
}
