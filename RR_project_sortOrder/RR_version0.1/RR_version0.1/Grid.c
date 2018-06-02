#include "Grid.h"
#include <math.h>

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
	float D[sizeOfOrder];

	while (check != 1) {
		orderCorrect = 1;

		for (int i = 0; i < (sizeOfOrder - 1); i++) {
			D[i] = sqrt((pow(X[i], 2)) + (pow(Y[i], 2)));      //phytagoras
			firstDistanceValue = D[i];
			secondDistanceValue = D[i + 1];

			if (D[i] > D[i + 1]) {
				swapOne(&D[i], &D[i + 1]);
				swapTwo(&X[i], &X[i + 1], &Y[i], &Y[i + 1]);
				orderCorrect = 0;
				} else if ((firstDistanceValue == secondDistanceValue) && (Y[i] == Y[i + 1])) {
				if (X[i] < X[i + 1]) {
					swapOne(&D[i], &D[i + 1]);
					swapTwo(&X[i], &X[i + 1], &Y[i], &Y[i + 1]);
					} else if (Y[i] > Y[i + 1]) {
					swapOne(&D[i], &D[i + 1]);
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
	
void readRoutes(int routes[4][20]){
	int i = 0, checkintersect = 0, grid = 0;
	int resultTemp;
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
}
	
void gotoGrid(int routeFromHome[], int routeFromChargepoint[], int flagBegin){                             //go to grid from home position or chargingpoint
	int intersection, intersectnum = 0;
	
Next:	
	if(flagBegin == 1){                       //from home point
		do{
			followLine();
		}while(intersection != 1);
		
		if(intersection == 1){
			switch(routeFromHome[intersectnum]){
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
			}
		}
		else if(flagBegin == 0){            // from charging point
			moveTurnRight();     			//draai 180 graden
			moveTurnRight();
			do{
				followLine();
			}while(intersection != 1);
			
			if(intersection == 1){
				switch(routeFromChargepoint[intersectnum]){
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
				}
			}
		}
	}
}