/* Menu - an application for the Pololu 3pi Robot
*
* This application uses the Pololu AVR C/C++ Library.  For help, see:
* -User's guide: http://www.pololu.com/docs/0J20
* -Command reference: http://www.pololu.com/docs/0J18
*
* Created: 6/7/2018 2:09:26 AM
*  Author: Kayne
*/

#include <pololu/3pi.h>
#include <stdio.h>

char functions[3][8]{
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