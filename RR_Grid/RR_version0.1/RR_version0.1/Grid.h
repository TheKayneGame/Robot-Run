/*
 * Grid.c
 *
 * Created: 8-5-2018 18:35:38
 *  Author: Madita
 */ 
#ifndef GRID_H_

#define GRID_H_

int sizeOfOrder;                            //replace with size of order 

extern int followLineFlag;
extern int productCollectedFlag;
extern int endOfRouteFlag;
extern int homeFlag;

void wirOrder();
void swapTwo( int *firstXValue, int *secondXValue, int *firstYValue, int *secondYValue);
void sortOrder(int X[10], int Y[10]);
void swapOne(int *firstValue, int *secondValue);
void driveRoute(int routes[5][8], int route, int *intersectNum);
void fetchOrder(int OrderX[10], int orderY[10], int route[5][8]);
void readGrid(int routes[5][8]);

typedef enum { T, R, L, X} rotation;
typedef enum { N, E, S, W} direction;

void fetchOrder2(int OrderX[10], int orderY[10], int route[5][8]);
void getInstructionsX(int gridZero, int orderX);
void getInstructionsY(int gridZero, int orderY);
void setDirection(direction directionDesired, direction *directionCurrent);

void fetchOrder3(int OrderX[10], int orderY[10], int route[5][8]);
void followStraightLine(int *coordinate, int coordinateDesired);

void getProduct(int orderX[10], int orderY[10], int *orderNum, int *xCoordinate, int *yCoordinate, int *x, direction *directionCurrent, direction *directionLast);

void warehouseMode();
#endif