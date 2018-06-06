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

	temp = *secondXValue;                                                                               //swap X-coordinates
	*secondXValue = *firstXValue;
	*firstXValue = temp;

	temp = *secondYValue;                                                                               //swap Y-coordinates
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

void turn(char direction){
	motorControl(70, direction, 0.89);
	delay_ms(50);
	motorControl(0, direction, 0.89);
}

void fetchOrder(int OrderX[], int orderY[], int route[2][20]){
	int crossCountX = 0, crossCountY = 0, flagY = 0, flagX = 0, endX = 5, endY = 0, endFlag = 0;
	int amountOfIntersects = readGrid(route);
	driveRoute(route, 1, 0, amountOfIntersects);    //Drive to grid entrance
	motorControl(70, 'R', 0.89);
	delay(50);
	motorControl(0, 'R', 0.89);
	for(int i = 0; i < sizeOfOrder + 1; i ++){
		if(i == sizeOfOrder){
			endFlag = 1;
		}
		if((crossCountX > OrderX[i]) || (endFlag == 1 && (crossCountX > endX))){
			turn('L');
			flagX = 1;
		}
		else if((crossCountX < OrderX[i]) || (endFlag == 1 && (crossCountX < endX))){
			turn('R');
			flagX = 2;
		}
		while((crossCountX != OrderX[i]) || (endFlag == 1 && (crossCountX != endX))){
			if(flagX == 1){
				//if intersection detected crossCountX++
			}
			else if(flagX == 2){
				//if intersection detected crossCountX--
			}
			motorControl(90, 'F', 0.89);
			// if intersection detected crossCountX++
		}
		motorControl(0, 'F', 0.89);
		if((crossCountY > orderY[i]) || (endFlag == 1 && (crossCountY > endY))){
			turn('L');
			flagY = 1;
		}
		else if((crossCountY < orderY[i]) || (endFlag == 1 && (crossCountY < endY))){
			turn('R');
			flagY = 2;
		}
		while((crossCountY != orderY[i]) || (endFlag == 1 && (crossCountY != endY))){
			if(flagY == 1){
				//if intersection detected crossCountY++
			}
			else if(flagY == 2){
				//if intersection detected crossCountY--
			}
			motorControl(90, 'F', 0.89);
		}
		play_from_program_space(PSTR(">g32>>c32"));
		delay(200);
	}
	driveRoute(route, 1, 1, amountOfIntersects);    //Drive back to home
	play_from_program_space(PSTR(">g32>>c32"));
}

int readGrid(int routes[4][20]){
	int i = 1, grid = 0, numOfIntersects, crossing = 0, routeNum = 1;
	int resultTemp;
	routes[1][0] = 5;                    //Marks beginning of route
	do{
		resultTemp = checkAfslag();	
		switch(resultTemp){
			case 1:                  //It is a corner to the right
			routes[0][i] = 1;
			turn('R');
			i++;
			break;
			case 2:                 //It is a corner to the left
			routes[0][i] = 2;
			turn('L');
			i++;
			break;
			case 3:                 //It is a T-crossing    L R
			turn('L');
			routes[0][i] = 3;
			i++;
			break;
			case 4:                //R
			routes[0][i] = 4;
			motorControl(80, 'F', 0.89);
			break;
			case 5:               //L
			routes[0][i] = 5;
			motorControl(80, 'F', 0.89);
			break;
			case 6:              //It is a crossing
			turn('L');
			i++;
			routes[0][i] = 6;
			break;
			case 7:         //Dead end
			routes[0][i] = 7;
			turn('R');
			turn('R');
			break;
			case 8:
			grid = 1;
			routes[0][i] = 8; //Marks end of route
			routes[0][20] = { 0 };
		}
	}while(grid == 0);
	numOfIntersects = i;
	
	for(i = 0; i < numOfIntersects; i++){   //Writing route towards X
		switch(routes[0][i]){
			case 1:
			routes[routeNum][i] = 1;
			break;
			case 2:
			routes[routeNum][i] = 2;
			break;
			case 3:
			if(routes[0][i + 1] == 7){
				routes[routeNum][i] = 1;
			}
			else if(routes[0][i + 1] != 7){
				routes[routeNum][i] = 2;
			}
			break;
			case 4:
			if(routes[0][i + 1] == 7){
				routes[routeNum][i] = 1;
			}
			else if(routes[0][i] != 7){
				routes[routeNum][i] = 3;
			}
			break;
			case 5:
			if(routes[0][i + 1] == 7){
				routes[routeNum][i] = 1;
			}
			else if(routes[0][i] != 7){
				routes[routeNum][i] = 2;
			}
			break;
			case 6:
			crossing++;
			routes[routeNum][i] = 6;
			if((crossing == 2) && (routes[routeNum][i - 1] == 6)){
				crossing = 0;
				routes[1][i - 1] = 3;
			}
			break;
			case 8:                                                      //case 7 isn't part of a route
			routes[1][i] = 8;  //Marks end of route
			for(int j = 0; j < 20; j++){                                //reset decoy array
				routes[0][i] = 0;
			}
			routeNum++;
			break;
			
		}
	}
	
	return numOfIntersects;                                                       //returns intersect count, so amount of intersects on route
}

void driveRoute(int route[2][20], int flag, int flagReturn, int max){             //go to or return from, grid or chargepoint
	int intersectnum = 1;                                       // flag 1 =  from or to home, flag 2 is from or to chargepoint
	
	if(flagReturn == 1){
		intersectnum = max;
	}
	
	if(flag == 2){
		turn('R');
	}
	
	Next:
	do{
		followLine();
	}while(checkAfslag() == 0);
	
	if(checkAfslag() != 0){
		
		if(flagReturn == 0){
			switch(route[flag][intersectnum]){
				case 1:
				turn('R');
				intersectnum++;
				goto Next;
				case 2:
				turn('L');
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
