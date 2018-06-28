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
#include <pololu/orangutan.h>
#include "wireless.h"

int speed = 50;


//obsolete
/*
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
}*/

//start accepting DATA  for coords
void wirCoord(int orderX[], int orderY[], int *numItems){
	clear();
	//declare working values
	int numItemCount = 0;
	
	//start loop
	do{
		//redeclare and reinitialize looping values
		int x = 10;
		int y = 10;
		
		char data[1];
		data[0] = 'e'; //set to unused variable
		do
		{
			
			serial_receive( data, 1 );// Start receiving data
			
			if(*numItems == 0 && data[0] != 'e'){//first byte is number items
				
				*numItems = data[0];
				data[0] = 'e'; //reset value
				continue;
			}
			
			if( data[0] != 'e' && data[0] != 'c' ) //all the other bytes are X/Y values
			{
				if( y == 10 ){
					y = data[0] - '0';
				}
				else if( x == 10 ){
					x = data[0] - '0';
				}
			}
			
			data[0] = 'e';
		} while ( x == 10 );//loop als x waarde oningevuld is
		orderX[numItemCount] = x; //loads value after acquisition
		orderY[numItemCount] = y; //loads value after acquisition
		numItemCount++;
	}while(numItemCount < *numItems);
	
	//debug
	
	print("Exit yes");
	delay_ms(1000);
	print(numItems);
	delay_ms(1000);
	clear();
	for (int i=0; i < *numItems; i++)
	{		
	lcd_goto_xy(0, 1);
	print_long(orderX[i]);
	delay_ms(1000);
	lcd_goto_xy(0,0);
	print_long(orderY[i]);
	delay_ms(1000);
	clear();
	}	
}

/* OBSOLETE!!!!!
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
*/
void wirMove( char data){//parse data to moving command
	switch( data )
	{
		case 'w':
		set_motors( speed, speed );//forward
		break;
		case 's':
		set_motors( -speed, -speed );//backward
		break;
		case 'a':
		set_motors( -speed, speed );//left
		break;
		case 'd':
		set_motors( speed, -speed );//right
		break;
		case '[':
		speed+=10;//decrease sped
		break;
		case ']':
		speed+=10;// inscrease speed
		break;
		case 'S':
		set_motors( 0, 0 );//emergency stop
		break;
		
		/*
		default:
		set_motors( 0, 0 );//stop as default
		*/
	}
}

void wirManual(){//manual mode init
	char data[1];
	int speed = 50;
	
	while (data[0] != 'S'){//loop as long as emergency stop is depressed
		serial_receive( data, 1 );
		clear();
		data[0] = 'e'; //reset data.		
		print_character(data);
		wirMove(data[0]);//parse data
	}
	set_motors( 0, 0 );
	serial_cancel_receive();
}
<<<<<<< HEAD


void run(int i){
	switch(i){
		case 0:
		wirManual()
		break;
		case 1:
		
		break;
		case 2:
		break;
		
	}
}


/*MOV this to main FC's*/
char *functions[3] = {"Handm.","WirC.","Volger"}; //menu texts
void menu(){

	lcd_init_printf();
	unsigned char button = (button_is_pressed(ANY_BUTTON));
	
	switch(button)
	{
		case (BUTTON_A) :
		clear();
		
		if(--selected < 0){selected = 2}
		printf("%s",functions[selected]);
		play_frequency(400, 100, 15);// Beep
		delay_ms(200);
		break;
		case (BUTTON_B) :
		play_frequency(660, 100, 15);// Beep
		delay_ms(150);
		play_frequency(660, 100, 15);
		delay_ms(50);
		//run(selected);
		break;
		
		case (BUTTON_C) :
		clear();
		if(++selected > 2){selected = 0}
		printf("%s",functions[selected]);
		play_frequency(800, 100, 15);// Beep
		delay_ms(200);
		break;
		
		default:
		break;
	}
}

=======
>>>>>>> c95a2cdec60e5a28680e1b3b4f5ee639ba1e89ad
