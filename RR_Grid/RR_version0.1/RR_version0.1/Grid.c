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

void fetchOrder(int OrderX[], int orderY[], int route[4][4]){                                      //Function that fetches the sorted order in the grid
	int crossCountX = 0, crossCountY = 0, flagY = 0, flagX = 0, endX = 5, endY = 0, endFlag = 0;
	driveRoute(route, 1);                                                                          //Drive to grid entrance
	for(int i = 0; i < sizeOfOrder + 1; i ++){                                                     //Sets flag to enable the robot to drive to the grid exit
		if(i == sizeOfOrder){
			endFlag = 1;
		}
		if((crossCountX > OrderX[i]) || (endFlag == 1 && (crossCountX > endX))){                   //Sets flag to drive to the left
			motorControl(70, 'L', 0.30);
			flagX = 1;
		}
		else if((crossCountX < OrderX[i]) || (endFlag == 1 && (crossCountX < endX))){             //Sets flag to drive to the right
			motorControl(70, 'R', 0.30);
			flagX = 2;
		}
		while((crossCountX != OrderX[i]) || (endFlag == 1 && (crossCountX != endX))){            //Counts X intersects so the robot knows where he is
			if(flagX == 1){                                                                      //Robot is on the left side of the grid, so the crossCount gets higher
				if(checkAfslag() != 0){
					crossCountX++;
				}
			}
			else if(flagX == 2){                                                                //Robot is on the right side of the grid so the crossCount gets lower
				if(checkAfslag() != 0){
					crossCountX--;
				}
			}
			motorControl(80, 'F', 0.89);                                                        //Set motors to drive forward
		}
		motorControl(0, 'F', 0.89);                                                             //Stop motors if the right X coordinate is reached
		if((crossCountY > orderY[i]) || (endFlag == 1 && (crossCountY > endY))){                //Sets flag to drive forward over the Y-axis
			motorControl(70, 'L', 0.30);
			flagY = 1;
		}
		else if((crossCountY < orderY[i]) || (endFlag == 1 && (crossCountY < endY))){           //Sets flag to drive backwards over the Y-axis
			motorControl(70, 'R', 0.30);
			flagY = 2;
		}
		while((crossCountY != orderY[i]) || (endFlag == 1 && (crossCountY != endY))){           //Counts Y intersects so the robot knows where he is
			if(flagY == 1){
				if(checkAfslag() != 0){
					crossCountX++;
				}
			}
			else if(flagY == 2){
				if(checkAfslag() != 0){
					crossCountX--;
				}
			}
			motorControl(80, 'F', 0.89);
		}
		play_from_program_space(PSTR(">g32>>c32"));                                            //Order point reached
		delay(200);
	}
	driveRoute(route, 3);                                                                      //Drive back to home point
	play_from_program_space(PSTR(">g32>>c32"));                                                //End of order
}

void readGrid(int routes[4][4]){
	
	routes[0][0] = 2;                                                                         //Home to grid
	routes[0][1] = 3;
	routes[0][2] = 2;
	routes[0][3] = 5;
	
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

void driveRoute(int route[4][4], int flag){                                                //Drive the given route
	int intersectnum = 0, decision = LOW, resultTemp, turn = 0;                            //Flag selects the route
	
	Next:
	do{
		turn = 0;
		for(int i = 0; i < 3; i++){
			if(situations[i] == HIGH){                                                     //Counts number of possible turns
				turn++;
			}
		}
		followLine();
	}while(checkAfslag() == 0);                                                           //Keep following the line if the sensor does not detect any intersections
	
	resultTemp = turn;                                                                    //If there is more than one option, the robot has to make a decision
	if(resultTemp > 1){
		decision = HIGH;
		red_led(1);
	}
	
	checkDistance();                                                                      //Keep checking for objects on the route
	
	if(checkAfslag() != 0){
		
		if(decision == HIGH){                                                            //If there is more than one turn, the robot makes a decision depending on the values in the route array
			switch(route[flag][intersectnum]){
				case 1:
				delay(150);
				motorControl(70, 'R', 0.30);				
				intersectnum++;
				print("afslag 1");
				delay(500);
				goto Next;
				case 2:
				motorControl(70, 'L', 0.30);
				intersectnum++;
				print("afslag 2");
				delay(500);
				goto Next;
				case 3:
				motorControl(80, 'F', 0.89);
				intersectnum++;
				print("afslag 3");
				delay(500);
				goto Next;
				case 5:
				motorControl(0, 'F', 0.89);    //stop
				print("einde");
				delay(500);
				break;
				play_from_program_space(PSTR(">g32>>c32"));                            //Robot has reached destination

			}
		}
	}
}
