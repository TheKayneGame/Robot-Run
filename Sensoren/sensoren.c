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

const char welcome_line1[] PROGMEM = " Pololu";
const char welcome_line2[] PROGMEM = "3\xf7 Robot";
const char demo_name_line1[] PROGMEM = "Line";
const char demo_name_line2[] PROGMEM = "follower";
const char welcome[] PROGMEM = ">g32>>c32";
const char go[] PROGMEM = "L16 cdegreg4";


const char levels[] PROGMEM =
{
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111
};
// This function loads custom characters into the LCD. Up to 8
// characters can be loaded; we use them for 7 levels of a bar graph.
void load_custom_characters()
{
	lcd_load_custom_character(levels+0,0); // no offset, e.g. one bar
	lcd_load_custom_character(levels+1,1); // two bars
	lcd_load_custom_character(levels+2,2); // etc...
	lcd_load_custom_character(levels+3,3);
	lcd_load_custom_character(levels+4,4);
	lcd_load_custom_character(levels+5,5);
	lcd_load_custom_character(levels+6,6);
	clear(); // the LCD must be cleared for the characters to take effect
}
// This function displays the sensor readings using a bar graph.
void display_readings(const unsigned int *calibrated_values)
{
	unsigned char i;
	for(i=0;i<5;i++)
	{
		
		const char display_characters[10] = {' ',0,0,1,2,3,4,5,6,255};
		char c = display_characters[calibrated_values[i]/101];
		print_character(c);
	}
}

void display_reading(const unsigned int *calibrated_values)
{
	unsigned char i;
	for(i=0;i<5;i++)
	{
		const char display_characters[10] = {' ',0,0,1,2,3,4,5,6,255};
		char c = display_characters[calibrated_values[i]/101];
		print_character(c);
	}
}

void initialize()
{
	unsigned int counter;
	pololu_3pi_init(2000);
	load_custom_characters();
	print_from_program_space(welcome_line1);
	lcd_goto_xy(0,1);
	print_from_program_space(welcome_line2);
	play_from_program_space(welcome);
	delay_ms(1000);
	clear();
	print_from_program_space(demo_name_line1);
	lcd_goto_xy(0,1);
	print_from_program_space(demo_name_line2);
	delay_ms(1000);
	
	while(!button_is_pressed(BUTTON_B))
	{
		int bat = read_battery_millivolts();
		clear();
		print_long(bat);
		print("mV");
		lcd_goto_xy(0,1);
		print("Press B");
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
		display_reading(sensors);
		delay_ms(100);
	}
	
	wait_for_button_release(BUTTON_B);
	clear();
	print("Go!");
	red_led(0);
}



void followLine()
{
	
	unsigned int pos = read_line(sensors,IR_EMITTERS_ON);
	clear();
	display_reading(sensors);
	
	if(checkAfslag() != 0)
	{
		//verwerken van kruising/t-splitsing/afslag etc
		set_motors(0,0);
		
	}
	
	else if(checkAfslag() == 0)
	{
		if(pos < 1950)
		{
			// We are far to the right of the line: turn left.
			green_led(1);
			clear();
			print_long(pos);
			display_reading(sensors);

			if(pos < 1800)
			{
				set_motors(0, SPEED);
			}
			else
			{
				set_motors(SLOW,FAST);
			}
			

		}
		
		else if (pos > 2050)
		{
			// We are far to the left of the line: turn right.
			red_led(1);
			clear();
			print_long(pos);
			display_reading(sensors);
			
			if(pos > 2200)
			{
				set_motors(SPEED, 0);
			}
			else
			{
				set_motors(FAST,SLOW);
			}
		}
		else
		{
			red_led(1);
			clear();
			print_long(pos);
			display_reading(sensors);
			set_motors(30,30);
		}
	}
	
}


int checkAfslag()
{
	
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
	return 0;
}

int checkDistance()
{
	
	return 0;
}