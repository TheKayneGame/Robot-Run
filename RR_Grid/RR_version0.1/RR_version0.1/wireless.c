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
void wirCoord(){
	clear();
	//declare working values
	unsigned char orderX[8];
	unsigned char orderY[8];
	int numItems = 0;
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
			
			if(numItems == 0 && data[0] != 'e'){//first byte is number items
				
				numItems = data[0];
				data[0] = 'e'; //reset value
				continue;
			}
			
			if( data[0] != 'e' && data[0] != 'c' ) //all the other bytes are X/Y values
			{
				if( y == 10 ){
					y = data[0];
				}
				else if( x == 10 ){
					x = data[0];
				}
			}
			
			data[0] = 'e';
		} while ( x == 10 );//loop als x waarde oningevuld is
		orderX[numItemCount] = x; //loads value after acquisition
		orderY[numItemCount] = y; //loads value after acquisition
		numItemCount++;
	}while(numItemCount < numItems);
	
	//debug
	/*
	print("Exit yes");
	delay_ms(1000);
	print(numItems);
	delay_ms(1000);
	clear();
	for (int i=0; i < numItems; i++)
	{
	
	
	lcd_goto_xy(0, 1);
	print_hex(orderX[i]);
	delay_ms(1000);
	lcd_goto_xy(0,0);
	print_hex(orderY[i]);
	delay_ms(1000);
	clear();
	}
	*/

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
		speed--;//decrease sped
		break;
		case ']':
		speed++;// inscrease speed
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
		data[0] = 'e'; //reset data.
		serial_receive( data, 1 );
		
		wirMove(data[0]);//parse data
		delay_ms(1);//undocumented delay
	}
	set_motors( 0, 0 );
}




char functions [3][8] = {{"Handm."},{"WeerC."},{"Volger"}}; //menu texts
/*MOV this to main FC's*/
void menu(){

	lcd_init_printf();
	unsigned char button = (wait_for_button_press(ANY_BUTTON)); //wait for user input
	
	switch(button)
	{
		case (BUTTON_A) :
		clear();
		selected--;
		display(selected);
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
		selected++;
		display(selected);
		play_frequency(800, 100, 15);// Beep
		delay_ms(200);
		break;
		
		default:
		break;
	}
}