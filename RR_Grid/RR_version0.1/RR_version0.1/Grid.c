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
	int firstDistanceValue, secondDistanceValue, check = 0, orderCorrect;
	float Distance[sizeOfOrder];

	while (check != 1) {
		orderCorrect = 1;

		for (int i = 0; i < (sizeOfOrder - 1); i++) {
			Distance[i] = sqrt((pow(X[i], 2)) + (pow(Y[i], 2)));                                    //Pythagoras
			firstDistanceValue =  Distance[i];
			secondDistanceValue =  Distance[i + 1];

			if ( Distance[i] >  Distance[i + 1]) {                                                  //Compare the distance of two points to each other
				swapOne(& Distance[i], & Distance[i + 1]);                                          //Place the biggest one further behind in the array
				swapTwo(&X[i], &X[i + 1], &Y[i], &Y[i + 1]);                                        //Swap the coordinates accordingly
				orderCorrect = 0;
				} else if ((firstDistanceValue == secondDistanceValue) && (Y[i] == Y[i + 1])) {     //If the distance is the same and the Y values are the same
				if (X[i] < X[i + 1]) {                                                              //Compare the X values
					swapOne(& Distance[i], & Distance[i + 1]);
					swapTwo(&X[i], &X[i + 1], &Y[i], &Y[i + 1]);
					} else if (Y[i] > Y[i + 1]) {
					swapOne(& Distance[i], & Distance[i + 1]);
					swapTwo(&X[i], &X[i + 1], &Y[i], &Y[i + 1]);
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
	routes[3][3] = 5;
	
	routes[4][0] = 3;                                                                       //Charge point to grid
	routes[4][1] = 2;
	routes[4][2] = 3;
	routes[4][3] = 5;
	
}

// void fetchOrder4(int orderX[], int orderY[], int route[4][8]){
// 	int afslag = 0;
// 	do{
// 		read_line_sensors(sensors,IR_EMITTERS_ON);
// 		clear();
// 		if(!checkAfslag()){
// 			followLine();
// 		}
// 		if(checkAfslag()){
// 			afslag++;
// 			print_long(afslag);
// 			delay_ms(500);
// 		}
// 	}while(afslag != 4);
// 	set_motors(0,0);
// 	delay_ms(10000);
// }
//
// void fetchOrder3(int orderX[], int orderY[], int route[4][8]){
// 	clear();
// 	do{
// 		read_line_sensors(sensors,IR_EMITTERS_ON);
// 		followLine();
// 	}while(!checkAfslag());
//
// 	int xCoordinate = 0, yCoordinate = 0;
//
// 	for(int orderNum = 0; orderNum < sizeOfOrder; orderNum++){
// 		clear();
// 		if(orderX[orderNum] != xCoordinate){
// 			if(orderX[orderNum] > xCoordinate){
// 				setDirection(W, directionCurrent);
// 				delay_ms(200);
// 			}
// 			if(orderX[orderNum] < xCoordinate){
// 				setDirection(E, directionCurrent);
// 				delay_ms(200);
// 			}
// 			followStraightLine(&xCoordinate, orderX[orderNum]);
// 		}
// 		if(orderY[orderNum] != yCoordinate){
// 			if(orderY[orderNum] > yCoordinate){
// 				setDirection(N, directionCurrent);
// 				delay_ms(200);
// 			}
// 			if(orderY[orderNum] < yCoordinate){
// 				setDirection(S, directionCurrent);
// 				delay_ms(200);
// 			}
// 			followStraightLine(&yCoordinate, orderY[orderNum]);
// 		}
// 		set_motors(0,0);               //moeten we nog even naar kijken, hij moet gelijk stilstaan
// 		play_from_program_space(PSTR(">f32>>a32"));
// 		delay(3000);
// 	}
// }

void followStraightLine(int *coordinate, int coordinateDesired){
	int biggerThan = 2;
	//print_long(*coordinate);
	if(*coordinate > coordinateDesired){
		biggerThan = 0;
	}
	else{
		biggerThan = 1;
	}
	while(*coordinate != coordinateDesired){
		do{
			followLine();
		}while(!checkAfslag());
		if(biggerThan == 1){
			*coordinate = *coordinate + 1;
			//print_long(*coordinate);
			//play_from_program_space(PSTR(">f32>>a32"));
			//print_long(*coordinate);
			//delay(200);
			//clear();
		}
		else if(biggerThan == 0){
			*coordinate = *coordinate - 1;
			//print_long(*coordinate);
			//play_from_program_space(PSTR(">f32>>a32"));
			//print_long(*coordinate);
			//delay(200);
			//clear();
		}
		set_motors(60,60);
		play_from_program_space(PSTR(">f32>>a32"));
		delay_ms(170);
		set_motors(0,0);      //moet korte stoot geven zodat de robot over kruispunt heen komt, nog kijken hoe hard / lang
	}
}

// void fetchOrder2(int OrderX[], int orderY[], int route[4][4]){
// 	driveRoute(route, 0);
// 	print("DoneD!");
// 	int gridZero = 1;
//
// 	while(checkAfslag() == 0){   //geen probleem
// 		followLine();
// 		print("Here!");
//
// 	}
// 	for(int orderNum = 0; orderNum < sizeOfOrder; orderNum++){
// 		lcd_goto_xy(0,1);
// 		print_long(orderNum);
// 		while((OrderX[orderNum] != positionCurrentX) || (orderY[orderNum] != positionCurrentY)){
// 			if(checkAfslag() != 0){
// 				if( OrderX[orderNum] == positionCurrentX){
// 					getInstructionsX(gridZero, OrderX[orderNum]);
// 				}
// 				else{
// 					getInstructionsY(gridZero, orderY[orderNum]);
// 				}
// 				if((OrderX[orderNum] == positionCurrentX) && (orderY[orderNum] == positionCurrentY)){
// 					motorControl(0, 'F', 0.89);
// 					play_from_program_space(PSTR(">f32>>a32"));
// 					orderNum++;
// 					delay(3000);
// 				}
// 			}
// 			followLine();
// 		}
// 	}
// }
//
// void getInstructionsX(int gridZero, int orderX){
// 	if(gridZero){
// 		positionCurrentX = 0;
// 		directionCurrent = N;
// 	}
//
// 	if(orderX > positionCurrentX){
// 		setDirection(E, directionCurrent);
// 	}
// 	else{
// 		setDirection(W, directionCurrent);
// 	}
// }
//
// void getInstructionsY(int gridZero, int orderY){
// 	if(gridZero){
// 		positionCurrentY = 0;
// 		directionCurrent = N;
// 	}
//
// 	if(orderY > positionCurrentY){
// 		setDirection(N, directionCurrent);
// 	}
// 	else{
// 		setDirection(S, directionCurrent);
// 	}
// }

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
			//clear();
			//print("Right!");
			*directionCurrent = directionDesired;
			break;
			case L:
			set_motors(-60,60);
			delay_ms(270);
			set_motors(0,0);
			
			//motorControl(60, 'L', 0.25);
			//clear();
			//print("Left!");
			*directionCurrent = directionDesired;
			break;
			case T:
			set_motors(60,-60);
			delay_ms(540);
			set_motors(0,0);
			
			//motorControl(60, 'R', 0.25);
			//delay_ms(2000);
			//motorControl(60, 'R', 0.25);
			//clear();
			//print("Turn!");
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