/*
 * Grid.c
 *
 * Created: 8-5-2018 18:35:38
 *  Author: Madita
 */ 
#ifndef GRID_H_

#define GRID_H_
#define sizeOfOrder 4                            //replace with size of order 

void wirOrder();
void swapTwo( int *firstXValue, int *secondXValue, int *firstYValue, int *secondYValue);
void sortOrder(int X[], int Y[]);
void swapOne(float *firstValue, float *secondValue);
void driveRoute(int route[4][4], int flag);
void fetchOrder(int OrderX[], int orderY[], int route[4][4]);
void readGrid(int routes[4][4]);

typedef enum { T, R, L, X} rotation;
typedef enum { N, E, S, W} direction;

void fetchOrder2(int OrderX[], int orderY[], int route[4][4]);
void getInstructionsX(int gridZero, int orderX);
void getInstructionsY(int gridZero, int orderY);
void setDirection(direction directionDesired, direction directionCurrent);
#endif