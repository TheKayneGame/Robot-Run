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
#include "Grid.h"

int situations[3]={LOW, LOW, LOW};

int integral;
int last_proportional;
int proportional;
int derivative;

void initialize()
{
	
	unsigned int counter;
	pololu_3pi_init(2000);								//initialize sensor value from 0 to 2000
	
	while(!button_is_pressed(BUTTON_B))					//this function is activated until button B is pressed.
	{
		int bat = read_battery_millivolts();
		clear();
		print_long(bat);								//print battery voltage in millivolts on the LCD
		print("mV");
		lcd_goto_xy(0,1);
		print("druk B");								//print instruction to continue
		delay_ms(100);
	}
	
	wait_for_button_release(BUTTON_B);					//button B is pressed
	delay_ms(1000);
	
	for(counter=0;counter<80;counter++)					//calibrating line sensors
	{
		if(counter < 20 || counter >= 60)
		set_motors(40,-40);
		else
		set_motors(-40,40);
		calibrate_line_sensors(IR_EMITTERS_ON);
		delay_ms(20);
	}
	
	set_motors(0,0);
	
	while(!button_is_pressed(BUTTON_B))										//function is activated until button B is pressed
	{
		unsigned int position = read_line(sensors,IR_EMITTERS_ON);			//reading the sensors to determine the position of the robot
		clear();															//clear LCD
		print("  ");
		print_long(position);												//print position of the robot compared to the line
		delay_ms(100);
	}
	
	wait_for_button_release(BUTTON_B);										//button B is pressed
	clear();																//clear LCD

}

int checkAfslag(){
	int flag;
	if(SENSOR_L < 800 && SENSOR_R < 800){
		flag = 0;
	}
	else{
		 flag = 1;
	}
	return flag;
}

void followLine(){
	// Get the position of the line.  Note that we *must* provide
	// the "sensors" argument to read_line() here, even though we
	// are not interested in the individual sensor readings.
	unsigned int position = read_line(sensors,IR_EMITTERS_ON);
	
	// The "proportional" term should be 0 when we are on the line.
	int proportional = ((int)position) - 2000;
	
	// Compute the derivative (change) and integral (sum) of the
	// position.
	int derivative = proportional - last_proportional;
	integral += proportional;
	
	// Remember the last position.
	last_proportional = proportional;

	// Compute the difference between the two motor power settings,
	// m1 - m2.  If this is a positive number the robot will turn
	// to the right.  If it is a negative number, the robot will
	// turn to the left, and the magnitude of the number determines
	// the sharpness of the turn.
	int power_difference = proportional/20 + integral/10000 + derivative*3/2;
	
	// Compute the actual motor settings.  We never set either motor
	// to a negative value.
	const int max = 60;
	if(power_difference > max)
	power_difference = max;
	if(power_difference < -max)
	power_difference = -max;
	
	if(power_difference < 0)
	set_motors(max+power_difference, max);
	else
	set_motors(max, max-power_difference);
}

int checkDistance()
{
	
	sensorDistance = analog_read(ADCH5);									//write sensor data to sensorDistance
	//sensorDistance2 = analog_read(ADCH7);									//write sensor data to sensorDistance2
	
	distance = (2076/(sensorDistance - 11));								//convert sensor data to distance in cm
	//distance2 = (2076/(sensorDistance2 - 11));								//convert sensor data to distance in cm
	
	clear();																//clear LCD
	
	if(distance < close && distance > veryClose)						    //compares if distance is less than 20 cm & bigger than 10 cm
	{
		clear();
		play_from_program_space(PSTR(">g32>>c32"));							//sound warning

	}
	else if(distance < veryClose && distance > 0)						    //compares if distance is less than 10 cm
	{
		clear();
		play_from_program_space(PSTR(">f32>>a32"));							//sound warning
		
		set_motors(0,0);
											//robot brakes
		moveObject();														//function that waits until the oject is removed
	}

	return 0;

}


void moveObject()
{
	while(!button_is_pressed(BUTTON_B))
	{
		clear();
		print("druk op");													//print instruction to LCD
		lcd_goto_xy(0,1);
		print("B knop");
		delay_ms(100);
	}
	wait_for_button_release(BUTTON_B);										//when button is released the robot will continue driving
}