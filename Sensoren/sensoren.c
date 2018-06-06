/*
 * sensoren.c
 *
 * Created: 3-6-2018 23:15:43
 *  Author: 2125228
 */ 
#include <pololu/3pi.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include "sensoren.h"
#include "motoren.h"


void initialize()
{
	unsigned int counter;
	pololu_3pi_init(2000);
	
	while(!button_is_pressed(BUTTON_B))
	{
		int bat = read_battery_millivolts();
		clear();
		print_long(bat);
		print("mV");
		lcd_goto_xy(0,1);
		print("druk B");
		delay_ms(100);
	}
	
	wait_for_button_release(BUTTON_B);
	delay_ms(1000);
	
	for(counter=0;counter<80;counter++)
	{
		if(counter < 20 || counter >= 60)
		set_motors(40,-40);
		else
		set_motors(-40,40);
		calibrate_line_sensors(IR_EMITTERS_ON);
		delay_ms(20);
	}
	
	set_motors(0,0);
	
	while(!button_is_pressed(BUTTON_B))
	{
		red_led(1);
		unsigned int position = read_line(sensors,IR_EMITTERS_ON);
		clear();
		print("  ");
		print_long(position);
		lcd_goto_xy(0,1);
		print(" ");
		delay_ms(100);
	}
	
	wait_for_button_release(BUTTON_B);
	clear();
	print("Go!");
}


void followLine()
{
	
	unsigned int pos = read_line(sensors,IR_EMITTERS_ON);
	clear();
	checkDistance();
	
	if(checkAfslag() == 0)
	{
		if(pos < 1950)
		{
			// We are far to the right of the line: turn left.
			green_led(1);

			if(pos < 1800)
			{
				set_motors(0, SPEED);
			}
			else
			{
				set_motors(SLOW, FAST);
			}
			
		}
		
		else if (pos > 2050)
		
		{
			// We are far to the left of the line: turn right.
			red_led(1);
			
			if(pos > 2200)
			{
				set_motors(SPEED,0);
			}
			else
			{
				set_motors(FAST, SLOW);
			}
		}
		else
		{
			red_led(0);
			green_led(0);
			set_motors(SPEED,SPEED);
		
		}
	}
	else if(checkAfslag()!= 0 || )
	{
		motorControl(0,F,0.89);
	}
	
}


int checkAfslag()
{
	read_line(sensors,IR_EMITTERS_ON);
	
	if(SENSOR_L > high_range && SENSOR_C_L < low_range && SENSOR_C_C < low_range && SENSOR_C_R < low_range && SENSOR_R < low_range)
	{
		return LEFT; //afslag naar links
	}
	else if(SENSOR_L < low_range && SENSOR_C_L < low_range && SENSOR_C_C < low_range && SENSOR_C_R < low_range && SENSOR_R > high_range)
	{
		return RIGHT; //afslag naar rechts
	}
	else if(SENSOR_L > high_range && SENSOR_C_L < low_range && SENSOR_C_C > high_range && SENSOR_C_R < low_range && SENSOR_R > high_range)
	{
		return FOUR_WAY_JOINT; //kruispunt
	}
	else if(SENSOR_L > high_range && SENSOR_C_L > high_range && SENSOR_C_C < low_range && SENSOR_C_R > high_range && SENSOR_R > high_range)
	{
		return T_LEFT_RIGHT; //t-splitsing rechtdoor
	}
	else if(SENSOR_L > high_range && SENSOR_C_L < low_range && SENSOR_C_C > high_range && SENSOR_C_R < low_range && SENSOR_R < low_range)
	{
		return T_LEFT; //t-splitsing linksaf
	}
	else if(SENSOR_L < low_range && SENSOR_C_L < low_range && SENSOR_C_C > high_range && SENSOR_C_R < low_range && SENSOR_C_R > high_range)
	{
		return T_RIGHT; //t-splitsing rechtsaf
	}
	else if(SENSOR_L < low_range && SENSOR_C_L < low_range && SENSOR_C_C < low_range && SENSOR_C_R < low_range && SENSOR_R < low_range)
	{
		return DEAD_END; //doodlopende straat
	}
	else if(SENSOR_L > high_range && SENSOR_C_L > high_range && SENSOR_C_C > high_range && SENSOR_C_R > high_range && SENSOR_R > high_range)
	{
		return GRID_HOME; //entry grid/home
	}
	return 0;
}


int checkDistance(int sensor)
{
	
	sensorDistance = analog_read(sensor);
	
	distance = (2076/(sensorDistance - 11));
	
	clear();
	
	
	if(distance < dichtbij && distance > heelDichtbij)
	{
		clear();
		play_from_program_space(PSTR(">g32>>c32"));
		print("dichtbij");
		delay_ms(200)';
	}
	else if(distance < heelDichtbij && distance > 0)
	{
		clear();
		play_from_program_space(PSTR(">f32>>a32"));
		print("heeeel");
		lcd_goto_xy(0,1);
		print("dichtbij");
		delay_ms(100);
		wachtenOpMedewerker();
	}
	else
	{
		clear();
		print_long(distance);
	}

	return 0;

}

void objectOmzeilen()
{
	motorControl(SLOW, L, 0.89);
	motorControl(SLOW, F, 0.89);
	
	
	if (distance2 < heelDichtbij)
	{
		motorControl(SLOW, F, 0.89);
	}
	else
	{
		motorControl(SLOW,F,0.89);
		delay(100);
		motorControl(SLOW,R,0.89);
	}
	
};

void wachtenOpMedewerker()
{
	while(!button_is_pressed(BUTTON_B))
	{
		play_from_program_space(PSTR(">f32>>a32"));
		lcd_goto_xy(1,0);
		print("druk B");
		delay_ms(100);
		clear();
	}
	
	wait_for_button_release(BUTTON_B);
	delay_ms(1000);
}