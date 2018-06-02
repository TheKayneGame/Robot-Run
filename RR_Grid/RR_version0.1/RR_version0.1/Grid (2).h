#ifndef GRID_H_

#define GRID_H_
#define sizeOfOrder 4                            //replace with size of order 

void swapTwo( int *firstXValue, int *secondXValue, int *firstYValue, int *secondYValue);
void sortOrder(int X[], int Y[]);
void swapOne(float *firstValue, float *secondValue);
void driveRoute(int route[4][20], int flag, int flagReturn, int max);
int readGrid(int routes[4][20]);

#endif