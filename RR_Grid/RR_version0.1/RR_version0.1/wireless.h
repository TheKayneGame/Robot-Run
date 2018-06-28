#ifndef WIRELESS_H_
#define WIRELESS_H_

void wirMain(int orderX[], int orderY[]);//declare obsolete FC
void wirOrder(int orderX[], int orderY[]);//declare obsolete FC
void wirCoord(int orderX[], int orderY[], int *itemsCount);//declare coord accepting FC
void wirManual();//declare manual mode FC
void menu(); // must be moved to main
void display(unsigned char i); //must be moved to main

char *functions[3]; // must be moved
static unsigned char selected = 0;

#endif