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

direction directionCurrent;
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

void sortOrder(int X[], int Y[]) {                                                                   //Sorting algorithm, this sorts the coordinates of the given order
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



void readGrid(int routes[4][4]){
	
	//routes[0][0] = 2;                                                                         //Home to grid
	routes[0][0] = 3;
	routes[0][1] = 2;
	routes[0][2] = 5;
	
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
void fetchOrder2(int OrderX[], int orderY[], int route[4][4]){
	driveRoute(route, 0);
	print("DoneD!");
	int gridZero = 1;
	
	// 	while(checkAfslag() == 0){
	// 		followLine();
	// 		print("Here!");
	//
	// 	}
	for(int orderNum = 0; orderNum < sizeOfOrder; orderNum++){
		if(checkAfslag() != 0){
			lcd_goto_xy(0,1);
			print_long(orderNum);
			while((OrderX[orderNum] != positionCurrentX) && (orderY[orderNum] != positionCurrentY)){
				if(checkAfslag() != 0){
					if( OrderX[orderNum] == positionCurrentX){
						getInstructionsX(gridZero, OrderX[orderNum]);
					}
					else{
						getInstructionsY(gridZero, orderY[orderNum]);
					}
					if((OrderX[orderNum] == positionCurrentX) && (orderY[orderNum] == positionCurrentY)){
						motorControl(0, 'F', 0.89);
						play_from_program_space(PSTR(">f32>>a32"));
						orderNum++;
						delay(3000);
					}
				}
				followLine();
			}
		}
		
	}
}

void getInstructionsX(int gridZero, int orderX){
	if(gridZero){
		positionCurrentX = 0;
		directionCurrent = N;
	}
	
	if(orderX > positionCurrentX){
		setDirection(E, directionCurrent);
	}
	else{
		setDirection(W, directionCurrent);
	}
}

void getInstructionsY(int gridZero, int orderY){
	if(gridZero){
		positionCurrentY = 0;
		directionCurrent = N;
	}
	
	if(orderY > positionCurrentY){
		setDirection(N, directionCurrent);
	}
	else{
		setDirection(S, directionCurrent);
	}
}

void setDirection(direction directionDesired, direction directionCurrent){
	rotation orientation[4][4] ={{X, R, T, L},
	{L, X, R, T},
	{T, L, X, R},
	{R, T, L, X}};
	
	switch(orientation[directionDesired][directionCurrent]){
		case R:
		motorControl(70, 'R', 0.30);
		directionCurrent = directionDesired;
		print("R");
		delay(500);
		break;
		case L:
		motorControl(70, 'L', 0.30);
		directionCurrent = directionDesired;
		print("L");
		delay(500);
		break;
		case T:
		motorControl(70, 'R', 0.30);
		motorControl(70, 'R', 0.30);
		directionCurrent = directionDesired;
		print("B");
		delay(500);
		break;
		default:
		break;
	}
}

void driveRoute(int route[4][4], int flag){                                                //Drive the given route
	int intersectnum = 0, decision = LOW, endOfRoute = 0;            //Flag selects the route
	
	do{
		decision = checkDecision();
		
		if(checkAfslag() != 0){
			
			if(decision == HIGH){                                                          //If there is more than one turn, the robot makes a decision depending on the values in the route array
				switch(route[flag][intersectnum]){
					case 1:
					delay(150);
					motorControl(70, 'R', 0.30);
					intersectnum++;
					print("R");
					break;
					case 2:
					motorControl(70, 'L', 0.30);
					intersectnum++;
					print("R");
					break;
					case 3:
					motorControl(60, 'F', 0.89);
					intersectnum++;
					print("F");
					break;
					case 5:
					motorControl(0, 'F', 0.89);
					green_led(1);                            //Robot has reached destination
					endOfRoute = 1;

					break;
				}
				//clear();
			}
		}
	}while(endOfRoute !=  1);
	delay(500);
	motorControl(0, 'F', 0.89);

}