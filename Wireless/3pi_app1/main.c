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
char *functions[3]{
	{"Handmatig"},
	{"Volger"},
	{"WirCoord"}
};

int main()
{
	play_from_program_space(PSTR(">g32>>c32"));  // Play welcoming notes.

	
}

void menu(){

	lcd_init_printf();
	static unsigned char selected = 0;
	static unsigned char button = wait_for_button_press(ANY_BUTTON);
	
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
		run(selected);
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

void display(unsigned char i){
	clear();
	printf("%s",functions[i]);
}


int wirMain()
{
	play_from_program_space(PSTR(">g32>>c32"));  // Play welcoming notes.
	int mode = 0;
	unsigned char data[2]={};
	
	mode = data[0];
	switch(){
		case 1:
		wirOrder();
		break;
		case 2:
		wirManual();
		break;
	}
	
}

void wirOrder(){
	int xBuff[8];
	int yBuff[8];
	
	int items = 0;
	int count1 = 0;
	unsigned char data[2]={};
	serial_receive(data,2);
	while(!serial_receive_buffer_full());
	items = data[0];
	do {
		
		serial_receive(data,2);
		while(!serial_receive_buffer_full());
		xBuff[count1] = data[0];
		serial_receive(data,2);
		while(!serial_receive_buffer_full());
		yBuff[count1] = data[0];
		
	} while(count1 < items)
}

void wirManual(){
	char bufferRichting[10]="";
	int links = 0;
	int recht = 0;
	print("Manual Control");
	int run = 1;
	while(run){
		serial_receive_blocking(bufferRichting, 10, 50);
		if(strcmp("w", bufferRichting) == 0){
			links += 10;
			recht += 10;
		}
		if(strcmp("a", bufferRichting) == 0){
			links -= 10;
			recht -= 10;
		}
		if(strcmp("s", bufferRichting) == 0){
			links += 10;
			recht -= 10;
		}
		if(strcmp("d", bufferRichting) == 0){
			links -= 10;
			recht += 10;
		}
		if(strcmp("s", bufferRichting) == 0){
			links = 0;
			recht = 0;
		}
		if(strcmp("p", bufferRichting) == 0){
			run = 0;
			links = 0;
			recht = 0;
			clear();
		}
		if(links > 255){
			links = 250;
		}
		if(recht > 255){
			recht = 250;
		}
		set_motors(links,recht);
		bufferRichting="";
	}
}