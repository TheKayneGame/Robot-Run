/* test - an application for the Pololu 3pi Robot
 *
 * This application uses the Pololu AVR C/C++ Library.  For help, see:
 * -User's guide: http://www.pololu.com/docs/0J20
 * -Command reference: http://www.pololu.com/docs/0J18
 *
 * Created: 5/19/2018 9:02:53 PM
 *  Author: 2125228
 */

#include <pololu/3pi.h>
#include <avr/pgmspace.h>


Void calibrate()
{
	clear();
	
	for(int counter = 0; counter < 80; counter++)
	{
		if(counter = 0 || counter >= 60)
		{
			set_motors(40, -40);
		}
		else
		{
			set_motors(-40, 40);
		}
		
		calibrate_line_sensors(IR_EMITTERS_ON);
		delay_ms(20);
	}
	
	set_motors(0,0);
	clear();
	play_from_program_space(PSTR(“L16 cdegreg4”));
	while (is_playing());
}


int followLine()
{
	unsigned int sensoren[5];
	calibrate();
	pololu_3pi_init(2000);
	calibrate_line_sensors(IR_EMITTERS_ON);
	
	if(read_line(sensoren, IR_EMITTERS_ON) < 1000)
	{
		set_motors(0,50);
	}
	
	else if(read_line(sensoren, IR_EMITTERS_ON) > 3000)
	{
		set_motors(0,0);
	}
	
	else
	{
		set_motors(50,50);
	}
	return 0;
}

int main()
{
	for(;;)
	{
		followLine();
	}
	return 0;
}



int checkAfslag()
{
	return 0;
}

int checkDistance()
{
	return 0;
}