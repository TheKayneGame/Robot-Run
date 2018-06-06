/* 3pi_app1 - an application for the Pololu 3pi Robot
*
* This application uses the Pololu AVR C/C++ Library.  For help, see:
* -User's guide: http://www.pololu.com/docs/0J20
* -Command reference: http://www.pololu.com/docs/0J18
*
* Created: 6/6/2018 1:11:27 PM
*  Author: Kayne
*/

#include <pololu/3pi.h>
#include "wireless.h"

void wirMain(int orderX[], int orderY[]){
	play_from_program_space(PSTR(">g32>>c32"));  // Play welcoming notes.
	int mode = 0;
	unsigned char data[2]={};
	
	mode = data[0];
	switch(mode){
		case 1:
		wirOrder(orderX, orderY);
		break;
		case 2:
		wirManual();
		break;
	}	
}

void wirOrder(int orderX[], int orderY[]){
	int items = 0;
	int count1 = 0;
	char data[2]={};
	serial_receive(data,2);
	while(!serial_receive_buffer_full());
	items = data[0];
	do {
		serial_receive(data,2);
		while(!serial_receive_buffer_full());
		orderX[count1] = data[0];
		serial_receive(data,2);
		while(!serial_receive_buffer_full());
		orderY[count1] = data[0];
		count1++;
		
	} while(count1 < items);	
}

void wirManual(){
	char data[2]={};
	int status = 1;
	char charBuff = 0;
	do {
		
		serial_receive(data,2);
		while(!serial_receive_buffer_full());
		
		switch (charBuff)
		{
			case 'w':
			
			break;
			case 'a':
			
			break;
			case 's':
			
			break;
			case 'd':
			
			break;
			case 'p':
			status = 0;
			break;
			default:
			break;
		}
		
		serial_receive(data,2);
		while(!serial_receive_buffer_full());
		
	} while(status);
}