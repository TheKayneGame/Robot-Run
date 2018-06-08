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

int situations[3]={LOW, LOW, LOW};

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
	print("Go!");

}


void followLine()
{
	
	unsigned int pos = read_line(sensors,IR_EMITTERS_ON);					//write position of the robot to an unsigned int called pos
	read_line_sensors(sensors,IR_EMITTERS_ON);								//read line sensors


	clear();																//clear display
	
	if(pos < 1950)
	{
		
		green_led(1);

		if(pos < 1800)														//We are far to the right of the line: turn left.
		{
			set_motors(0,SPEED);
		}
		else
		{
			set_motors(SLOW,SPEED);											//we are to the right of the line: turn left.
		}
		
	}
	
	else if (pos > 2050)
	{
		// We are far to the left of the line: turn right.
		red_led(1);
		
		if(pos > 2200)														//We are far to the left of the line: turn right
		{
			set_motors(SPEED,0);
		}
		else
		{
			set_motors(FAST,SLOW);											//We are to the left of the line: turn right
		}
	}
	else
	{
		set_motors(SLOW,SLOW);												//we are on the line. move forward
		
	}

	
}

int checkAfslag(){
	int flag = 0;													//initialize flag and turn
	situations[0] =LOW;														//sensor left initialize
	situations[1] =LOW;														//sensor center initialize
	situations[2] =LOW;														//sensor right initialize
	read_line_sensors(sensors,IR_EMITTERS_ON);								//read line sensors
	int rangeHigh = 1000;													//set high range to 1000
	
	if(SENSOR_L > rangeHigh){
		situations[0] = HIGH;
		flag = 1;															//sensor left is high, flag = 1
	}
	if(SENSOR_C_C > rangeHigh){
		situations[1] = HIGH;
		flag = 2;															//sensor center is high, flag = 2
	}
	if(SENSOR_R > rangeHigh){
		situations[2] = HIGH;
		flag = 3;															//sensor right is high, flag = 3
	}
	
	
	
	print_long(flag);														//print flag to LCD
	lcd_goto_xy(0,1);
	print_long(situations[0]);												//print sensor data (0/1) to LCD
	print_long(situations[1]);
	print_long(situations[2]);
	clear();																//clear LCD
	return flag;
}



int checkDistance()
{
	
	sensorDistance = analog_read(ADCH5);									//write sensor data to sensorDistance
	sensorDistance2 = analog_read(ADCH7);									//write sensor data to sensorDistance2
	
	distance = (2076/(sensorDistance - 11));								//convert sensor data to distance in cm
	distance2 = (2076/(sensorDistance2 - 11));								//convert sensor data to distance in cm
	
	clear();																//clear LCD
	
	
	if(distance < close && distance > veryClose)						    //compares if distance is less than 20 cm & bigger than 10 cm
	{
		clear();
		play_from_program_space(PSTR(">g32>>c32"));							//sound warning
		print("dichtbij");													//warning on LCD
		delay_ms(200);
	}
	else if(distance < veryClose && distance > 0)						    //compares if distance is less than 10 cm
	{
		clear();
		play_from_program_space(PSTR(">f32>>a32"));							//sound warning
		print("heeeel");													//warning on LCD
		lcd_goto_xy(0,1);
		print("dichtbij");
		motorControl(STOP,'F',0.89);										//robot brakes
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