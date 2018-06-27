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

void swapTwo( int *firstXValue, int *secondXValue, int *firstYValue, int *secondYValue){                //Swap function for the coordinates
	int temp;

	temp = *secondXValue;                                                                               //Swap X-Coordinates
	*secondXValue = *firstXValue;
	*firstXValue = temp;

	temp = *secondYValue;                                                                               //Swap Y-Coordinates
	*secondYValue = *firstYValue;
	*firstYValue = temp;
}

void swapOne(float *firstValue, float *secondValue) {                                                  //Swap function for the distance array
	float temp;

	temp = *secondValue;
	*secondValue = *firstValue;
	*firstValue = temp;
}

void sortOrder(int X[sizeOfOrder], int Y[sizeOfOrder]) {                                                                   //Sorting algorithm, this sorts the coordinates of the given order
	
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
	routes[3][3] = 5;
	
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
			
// 			set_motors(60,-60);
// 			delay_ms(270);
// 			set_motors(0,0);
			
			motorControl(60, 'R', 0.25);

			*directionCurrent = directionDesired;
			break;
			case L:
			
// 			set_motors(-60,60);
// 			delay_ms(270);
// 			set_motors(0,0);
			
			motorControl(60, 'L', 0.25);

			*directionCurrent = directionDesired;
			break;
			case T:
			
// 			set_motors(60,-60);
// 			delay_ms(540);
// 			set_motors(0,0);
			
			motorControl(60, 'R', 0.25);
			motorControl(60, 'R', 0.25);

			*directionCurrent = directionDesired;
			break;
			default:
			break;
			clear();
		}
	}
	
}

void driveRoute(int route[4][8], int flag){                          //Drive the given route
	int intersectnum = 0, decision = LOW, endOfRoute = 0;            //Flag selects the route
	
	set_motors(60,60);
	play_from_program_space(PSTR(">f32>>a32"));
	delay_ms(190);
	set_motors(0,0);
	
	switch(route[0][intersectnum]){
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
		motorControl(0, 'F', 0.30);
		green_led(1);                            //Robot has reached destination
		play_from_program_space(PSTR(">f32>>a32"));
		delay_ms(1000);
		endOfRoute = 1;
		break;
	}
}