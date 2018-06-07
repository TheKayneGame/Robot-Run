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


void swapTwo( int *firstXValue, int *secondXValue, int *firstYValue, int *secondYValue){
	int temp;

	temp = *secondXValue;                                                                               //Verwissel X-coordinaten
	*secondXValue = *firstXValue;
	*firstXValue = temp;

	temp = *secondYValue;                                                                               //Verwissel Y-coordinaten
	*secondYValue = *firstYValue;
	*firstYValue = temp;
}

void swapOne(float *firstValue, float *secondValue) {
	float temp;

	temp = *secondValue;
	*secondValue = *firstValue;
	*firstValue = temp;
}

void sortOrder(int X[], int Y[]) {
	int firstDistanceValue, secondDistanceValue, check = 0, orderCorrect;
	float Distance[sizeOfOrder];

	while (check != 1) {
		orderCorrect = 1;

		for (int i = 0; i < (sizeOfOrder - 1); i++) {
			Distance[i] = sqrt((pow(X[i], 2)) + (pow(Y[i], 2)));      //Pythagoras
			firstDistanceValue =  Distance[i];
			secondDistanceValue =  Distance[i + 1];

			if ( Distance[i] >  Distance[i + 1]) {
				swapOne(& Distance[i], & Distance[i + 1]);
				swapTwo(&X[i], &X[i + 1], &Y[i], &Y[i + 1]);
				orderCorrect = 0;
				} else if ((firstDistanceValue == secondDistanceValue) && (Y[i] == Y[i + 1])) {
				if (X[i] < X[i + 1]) {
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

void fetchOrder(int OrderX[], int orderY[], int route[3][4]){
	int crossCountX = 0, crossCountY = 0, flagY = 0, flagX = 0, endX = 5, endY = 0, endFlag = 0;
	driveRoute(route, 1);    //Rij naar grid ingang
	motorControl(70, 'R', 0.89);
	delay(50);
	motorControl(0, 'R', 0.89);
	for(int i = 0; i < sizeOfOrder + 1; i ++){
		if(i == sizeOfOrder){
			endFlag = 1;
		}
		if((crossCountX > OrderX[i]) || (endFlag == 1 && (crossCountX > endX))){
			motorControl(70, 'L', 0.89);
			flagX = 1;
		}
		else if((crossCountX < OrderX[i]) || (endFlag == 1 && (crossCountX < endX))){
			motorControl(70, 'R', 0.89);
			flagX = 2;
		}
		while((crossCountX != OrderX[i]) || (endFlag == 1 && (crossCountX != endX))){
			if(flagX == 1){
				//Als er een splitsing gedetecteerd wordt crossCountX++
			}
			else if(flagX == 2){
				//Als er een splitsing gedetecteerd wordt crossCountX--
			}
			motorControl(90, 'F', 0.89);
			//Als er een splitsing gedetecteerd wordt crossCountX++
		}
		motorControl(0, 'F', 0.89);
		if((crossCountY > orderY[i]) || (endFlag == 1 && (crossCountY > endY))){
			motorControl(70, 'L', 0.89);
			flagY = 1;
		}
		else if((crossCountY < orderY[i]) || (endFlag == 1 && (crossCountY < endY))){
			motorControl(70, 'R', 0.89);
			flagY = 2;
		}
		while((crossCountY != orderY[i]) || (endFlag == 1 && (crossCountY != endY))){
			if(flagY == 1){
				//Als er een splitsing gedetecteerd wordt crossCountX++
			}
			else if(flagY == 2){
				//Als er een splitsing gedetecteerd wordt crossCountX--
			}
			motorControl(90, 'F', 0.89);
		}
		play_from_program_space(PSTR(">g32>>c32"));
		delay(200);
	}
	driveRoute(route, 3);    //Rij terug naar begipunt
	play_from_program_space(PSTR(">g32>>c32"));
}

void readGrid(int routes[3][4]){
	int resultTemp;
	char test;
	//test = resultTemp+'0';
	print_character(test);
	
	routes[0][0] = 2;
	routes[0][1] = 3;
	routes[0][2] = 2;
	routes[0][3] = 5;
	
	routes[1][0] = 1;
	routes[1][1] = 1;
	routes[1][2] = 5;
	
	routes[2][0] = 3;
	routes[2][1] = 3;
	routes[2][2] = 5;
	
	routes[3][0] = 3;
	routes[3][1] = 1;
	routes[3][2] = 2;
	routes[3][3] = 5;	
	                                                     //returns intersect count, so amount of intersects on route
}

void driveRoute(int route[3][4], int flag){             //go to or return from, grid or chargepoint
	int intersectnum = 0, decision, resultTemp;                                       // flag 1 =  from or to home, flag 2 is from or to chargepoint
	
	Next:
	do{
		followLine();
	}while(test() == 0);
	
	resultTemp = test();
	if(resultTemp > 1){
		decision = HIGH;
	}
	
	if(test() != 0){
		
		if(decision == HIGH){
			switch(route[flag][intersectnum]){
				case 1:
				motorControl(70, 'R', 0.30);
				intersectnum++;
				goto Next;
				case 2:
				motorControl(70, 'L', 0.30);
				intersectnum++;
				goto Next;
				case 3:
				motorControl(80, 'F', 0.89);
				intersectnum++;
				goto Next;
				case 5:
				motorControl(0, 'F', 0.89);    //stop
				break;
				play_from_program_space(PSTR(">g32>>c32"));

			}
		}
	}
}
