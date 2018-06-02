#include "Grid.h"
#include <math.h>
#include <pololu/3pi.h>

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
			Distance[i] = sqrt((pow(X[i], 2)) + (pow(Y[i], 2)));      //phytagoras
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
void followLine(){}                  //junkdef
void moveTurnRight(){}
void moveTurnLeft(){}
void moveForward(){}

int readGrid(int routes[4][20]){
	int i = 1, checkintersect = 0, grid = 0;
	int resultTemp;
	routes[1][0] = 5;
	do{
		if(checkintersect == 1){
			//call intersect detect function
			switch(resultTemp){
				case 1:
				routes[1][i] = 1;
				i++;
				break;
				case 2:
				routes[1][i] = 2;
				i++;
				break;
				case 3:
				routes[1][i] = 3;
				i++;
				break;
				case 4:
				routes[1][i] = 4;
				i++;
				break;
				case 5:
				grid = 1;
				routes[1][i] = 5;
				break;
			}
		}
	}while(grid == 0);
	return i;                                                                                     //returns intersect count, so amount of intersects on route
}

void driveRoute(int route[4][20], int flag, int flagReturn, int max){                             //go to or return from, grid or chargepoint
	int intersection, intersectnum = 1;                                                           // flag 1 =  from or to home, flag 2 is from or to chargepoint
	
	if(flagReturn == 1){
		intersectnum = max;
	}
	
	if(flag == 2){
		moveTurnRight();    //turn around 180 degrees
		moveTurnRight();
	}
	
	Next:
	do{
		followLine();
	}while(intersection != 1);
	
	if(intersection == 1){
		
		if(flagReturn == 0){
			switch(route[flag][intersectnum]){
				case 1:
				moveTurnRight();
				intersectnum++;
				goto Next;
				case 2:
				moveTurnLeft();
				intersectnum++;
				goto Next;
				case 3:
				moveForward();
				intersectnum++;
				goto Next;
				case 5:
				//stop
				play_from_program_space(PSTR(">g32>>c32"));
				break;
			}
		}
		else if (flagReturn == 1){
			switch(route[flag][intersectnum]){
				case 1:
				moveTurnLeft();
				intersectnum--;
				goto Next;
				case 2:
				moveTurnRight();
				intersectnum--;
				goto Next;
				case 3:
				moveForward();
				intersectnum--;
				goto Next;
				case 5:
				//stop
				play_from_program_space(PSTR(">g32>>c32"));
				break;
			}
		}
	}
}