#include "Grid.h"

void swapTwo( int *a, int *b, int *c, int *d){
	int temp;

	temp = *b;                                                                               //swap X-coordinates
	*b = *a;
	*a = temp;

	temp = *d;                                                                               //swap Y-coordinates
	*d = *c;
	*c = temp;
}

void sortOrder(int X[], int Y[]) {
	int check = 0, orderCorrect, toggle = 0;

	while (check != 1) {                                                                     //sort on Y-coordinates (ascending)
		orderCorrect = 1;
		for (int i = 0; i < (sizeOfOrder - 1); i++) {
			if (Y[i] > Y[i + 1]) {
				swapTwo(&X[i], &X[i + 1], &Y[i], &Y[i + 1]);
				orderCorrect = 0;
			}
		}
		if (orderCorrect == 1) {
			check = 1;
		}
	}
	check = 0;
	while (check != 1) {
		orderCorrect = 1;
		for (int i = 0; i < (sizeOfOrder - 1); i++) {                                       //check if Y is even or odd
			if (Y[i] % 2 == 0) {
				toggle = 0;
			}
			else {
				toggle = 1;
			}
			if ((toggle == 1) && (Y[i] == Y[i + 1]) && (X[i] < X[i + 1])) {                 //if Y is odd put X-coordinates in descending order
				swapTwo(&X[i], &X[i + 1], &Y[i], &Y[i + 1]);
				orderCorrect = 0;
			}
			else if((toggle == 0) && (Y[i] == Y[i + 1]) && (X[i] > X[i + 1])){              //if Y is even put X-coordinates in ascending order
				swapTwo(&X[i], &X[i + 1], &Y[i], &Y[i + 1]);
				orderCorrect = 0;
			}
		}
		if (orderCorrect == 1) {
			check = 1;
		}
	}
}