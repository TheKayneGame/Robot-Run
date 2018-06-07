#ifndef WIRELESS_H_
#define WIRELESS_H_

void wirMain(int orderX[], int orderY[]);
void wirOrder(int orderX[], int orderY[]);
void wirManual();
void menu();
void display(unsigned char i);

char functions[3][8];
static unsigned char selected = 0;

#endif