/* RR_version0.1 - an application for the Pololu 3pi Robot
*
* This application uses the Pololu AVR C/C++ Library.  For help, see:
* -User's guide: http://www.pololu.com/docs/0J20
* -Command reference: http://www.pololu.com/docs/0J18
*
* Created: 4/17/2018 6:33:30 PM
*  Author: Madita

A = licht sensor 1               1
B = licht sensor 2             2   3
C = licht sensor 3
D = licht sensor 4           4       5
E = licht sensor 5
F = afstands sensor

X = motor 1
Y = motor 2
*/

//long i = 0;
//
#include "Grid.h"
#include "wireless.h"
#include "sensoren.h"
#include "motoren.h"
#include <pololu/3pi.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>

int main(){
	initialize();
	//warehouseMode();	
	
	while(1){
		menu();
	}
}

char *functions[3] = {"Handm.","WirC.","Volger"}; //menu texts


void run(int i){
	switch(i){
		case 0:
		wirManual();
		break;
		case 1:
		warehouseMode();
		break;
		case 2:
		break;

	}
}
void menu(){

	unsigned char button = (button_is_pressed(ANY_BUTTON));

	switch(button)
	{
		case (BUTTON_A) :
		clear();

		if(--selected < 0){selected = 2;}
		print(functions[selected]);
		play_frequency(400, 100, 15);// Beep
		delay_ms(200);
		break;
		case (BUTTON_B) :
		play_frequency(660, 100, 15);// Beep
		delay_ms(150);
		play_frequency(660, 100, 15);
		delay_ms(50);
		run(selected);
		break;

		case (BUTTON_C) :
		clear();
		if(++selected > 2){selected = 0;}
		print(functions[selected]);
		play_frequency(800, 100, 15);// Beep
		delay_ms(200);
		break;

		default:
		break;
	}
}
