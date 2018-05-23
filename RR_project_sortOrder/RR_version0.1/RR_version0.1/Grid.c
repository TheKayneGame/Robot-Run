#include "Grid.h"
#include <math.h>

void swapTwo( int *a, int *b, int *c, int *d){
	int temp;

	temp = *b;                                                                               //swap X-coordinates
	*b = *a;
	*a = temp;

	temp = *d;                                                                               //swap Y-coordinates
	*d = *c;
	*c = temp;
}

void swapOne(float *a, float *b) {
	float temp;

	temp = *b;
	*b = *a;
	*a = temp;
}

void sortOrder(int X[], int Y[]) {
	int a, b, check = 0, orderCorrect;
	float D[sizeOfOrder];

	while (check != 1) {
		orderCorrect = 1;

		for (int i = 0; i < (sizeOfOrder - 1); i++) {
			D[i] = sqrt((pow(X[i], 2)) + (pow(Y[i], 2)));      //phytagoras
			a = D[i];
			b = D[i + 1];

			if (D[i] > D[i + 1]) {
				swapOne(&D[i], &D[i + 1]);
				swapTwo(&X[i], &X[i + 1], &Y[i], &Y[i + 1]);
				orderCorrect = 0;
				} else if ((a == b) && (Y[i] == Y[i + 1])) {
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