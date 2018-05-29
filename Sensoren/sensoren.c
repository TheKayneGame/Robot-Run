/* sensoren - an application for the Pololu 3pi Robot
 *
 * This application uses the Pololu AVR C/C++ Library.  For help, see:
 * -User's guide: http://www.pololu.com/docs/0J20
 * -Command reference: http://www.pololu.com/docs/0J18
 *
 * Created: 5/1/2018 8:55:52 PM
 *  Author: 2125228
 */


#include <pololu/3pi.h>
#include <stdio.h>
#include "sensoren.h"

#define lastError 0
#define speedMax 0
#define highRange 700
#define lowRange 1800
#define KD 0.01
#define KP 0.02
unsigned int sensor[5];



int main()
{
	for(;;)
	{
		followLine();
	}
	return 0;
}



void calibrate()
{
	clear();
	
	for(int counter = 0; counter < 80; counter++)
	{
		if(counter == 0 || counter >= 60)
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
}

int followLine()
{
	int position;
	int err;
	
	calibrate();
	pololu_3pi_init(2000);
	calibrate_line_sensors(IR_EMITTERS_ON);
	
	
	position = read_line(sensor, IR_EMITTERS_ON);
	
	err = position - 1000;
	int speed = KP*err + KD*(err-lastError);				//KP = position		KD= Destination
	int speedRight = speedMax - speed;
	int speedLeft = speedMax + speed;
	
	
	if (err == -2000 || err == 2000) //end of the line
	{
		set_motors(speedMax, -speedMax);	//turn 180
	}
	return 0;
}




int checkAfslag()
{
	if(sensor[0] > highRange && sensor[1] > highRange && sensor[2] > highRange)
	{
		set_motors(0, 0);
		delay_ms(10);
		set_motors(speedMax, -speedMax);							//turn right until sensors detect line
	}
	
	if(sensor[2] > highRange && sensor[3] > highRange && sensor[4] > highRange && sensor[0] < lowRange)				//kijkt of hij alleen links kan
	{
		set_motors(0,0);
		delay(10);
		set_motors(-speedMax, speedMax);							//turn left
	}
	return 0;
}
