/* Test application RobotRun G6 - an application for the Pololu 3pi Robot
*
* This application uses the Pololu AVR C/C++ Library.  For help, see:
* -User's guide: http://www.pololu.com/docs/0J20
* -Command reference: http://www.pololu.com/docs/0J18
*
* Created: 5/14/2018 3:07:29 PM
*  Author: Jonathan
*/

#include <pololu/3pi.h>			//Including the library's
#include <avr/pgmspace.h>
#include <stdio.h>
#include <math.h>

enum directions{ F=0,B,R,L};	//Defining the direction variables.

int speedCurrent = 0;			//Defining the current speeds.
int speedCurrentRight = 0;
int speedCurrentLeft = 0;

void motorControl(int speed, char direction, float aggressionFactor){		//This function is an upgrade over the existing motor control function written by Pololu. This function moves the robot with an entered speed and acceleration time in a desired direction.
																			//The function offers an acceleration curve based on the swept sinus formula. This reduces the jerk significantly, allowing for smoother acceleration in all directions.
	float accelerationCounter, motorLeftSpeed, motorRightSpeed;				//The acceleration variables are defined as floats because of the Sinus output.
	int timerStart = 0;
	
	int setSpeed = 0;														//The variables in charge of transforming the input speed into the actual speed are defined here.
	int setSpeedRight = 0;
	int setSpeedLeft = 0;
	
	//directions direction;

	switch (direction){														//This switch case switches between the directions based on the user input.
		case 'F':															//This case handles the forward movement of the 3PI robot.
		
		setSpeed = speed - speedCurrent;
		
		for (accelerationCounter = 0.0; accelerationCounter < 1.0; accelerationCounter = accelerationCounter + 0.01){	//This for loop increases the speed of the current speed to the desired speed with a total of a 100 increments.
			timerStart = get_ms();
			
			motorLeftSpeed = motorRightSpeed = speedCurrent + setSpeed * (accelerationCounter - ( ( 1 / ( 2*M_PI ) ) * sin ( 2* M_PI * accelerationCounter ) ) );		//This function transfers the input speed to a segmented speed increase based on the swept sinusoidal curve.
			
			set_motors(motorLeftSpeed, motorRightSpeed);

			while ( (get_ms() - timerStart ) < (aggressionFactor * 10.0) ) {											//This while loop temporarily freezes the system to make sure that the increments are spaced properly to facilitate a fluent and consequent increase in speed.
				//Change the aggression factor to manipulate the acceleration time. A shorter time increases the overall jerk of the acceleration.
			}
		}
		speedCurrent = speed;
		break;
		
		case 'B':		//This case handles the backward movement of the robot. While the robot does not require this function in the standard routine, it is desired when operating the robot in manual mode.
		
		setSpeed = speed - speedCurrent;
		
		for (accelerationCounter = 0.0; accelerationCounter < 1.0; accelerationCounter = accelerationCounter + 0.01){
			timerStart = get_ms();
			
			motorLeftSpeed = motorRightSpeed = speedCurrent + setSpeed * (accelerationCounter - ( ( 1 / ( 2 * M_PI ) ) * sin ( 2 * M_PI * accelerationCounter ) ) );
			
			set_motors(motorLeftSpeed, motorRightSpeed);

			while ( (get_ms() - timerStart ) < (aggressionFactor * 10.0) ) {
				//change for optimal acceleration time.
			}
		}
		speedCurrent = speed;
		break;

		case 'R':		//This case handles the rotation of the robot 90 degrees to the right. The robot accelerates and decelerates with the same method used with forward and backward movement.
		
		setSpeedRight = speed + speedCurrentRight;
		setSpeedLeft = speed - speedCurrentLeft;
		
		for (accelerationCounter = 0.0; accelerationCounter < 1.0; accelerationCounter = accelerationCounter + 0.01){
			timerStart = get_ms();
			
			motorRightSpeed = speedCurrent + (speedCurrentRight - (setSpeedRight * (accelerationCounter + ( ( 1 / ( 2 * M_PI ) ) * sin ( 2 * M_PI * accelerationCounter ) ) ) ) );
			
			motorLeftSpeed = speedCurrent + (speedCurrentLeft + (setSpeedLeft * (accelerationCounter + ( ( 1 / ( 2 * M_PI ) ) * sin ( 2 * M_PI * accelerationCounter ) ) ) ) );
			
			set_motors(motorLeftSpeed, motorRightSpeed);

			while ( (get_ms() - timerStart ) < (aggressionFactor * 10.0) ) {
				//change for optimal acceleration time.
			}
		}
		speedCurrentRight = -speed;
		speedCurrentLeft = speed;

		speed = 0;
		
		setSpeedRight = speed + speedCurrentRight;
		setSpeedLeft = speed - speedCurrentLeft;
		
		for (accelerationCounter = 0.0; accelerationCounter < 1.0; accelerationCounter = accelerationCounter + 0.01){
			timerStart = get_ms();
			
			motorRightSpeed = speedCurrent + (speedCurrentRight - (setSpeedRight * (accelerationCounter + ( ( 1 / ( 2 * M_PI ) ) * sin ( 2 * M_PI * accelerationCounter ) ) ) ) );
			
			motorLeftSpeed = speedCurrent + (speedCurrentLeft + (setSpeedLeft * (accelerationCounter + ( ( 1 / ( 2 * M_PI ) ) * sin ( 2 * M_PI * accelerationCounter ) ) ) ) );
			
			set_motors(motorLeftSpeed, motorRightSpeed);

			while ( (get_ms() - timerStart ) < (aggressionFactor * 10.0) ) {
				//change for optimal acceleration time.
			}
		}
		speedCurrentRight = -speed;
		speedCurrentLeft = speed;
		
		break;

		case 'L': //This case handles the rotation of the robot 90 degrees to the left. The robot accelerates and decelerates with the same method used with forward and backward movement.
		
		setSpeedRight = speed - speedCurrentRight;
		setSpeedLeft = speed + speedCurrentLeft;
		
		for (accelerationCounter = 0.0; accelerationCounter < 1.0; accelerationCounter = accelerationCounter + 0.01){
			timerStart = get_ms();
			
			motorRightSpeed = speedCurrentRight + (setSpeedRight * (accelerationCounter + ( ( 1 / ( 2 * M_PI ) ) * sin ( 2 * M_PI * accelerationCounter ) ) ) );
			
			motorLeftSpeed = speedCurrentLeft - (setSpeedLeft * (accelerationCounter + ( ( 1 / ( 2 * M_PI ) ) * sin ( 2 * M_PI * accelerationCounter ) ) ));
			
			set_motors(motorLeftSpeed, motorRightSpeed);

			while ( (get_ms() - timerStart ) < (aggressionFactor * 10.0) ) {
				//change for optimal acceleration time.
			}
		}
		speedCurrentRight = speed;
		speedCurrentLeft = -speed;
		
		speed = 0;
		
		setSpeedRight = speed - speedCurrentRight;
		setSpeedLeft = speed + speedCurrentLeft;
		
		for (accelerationCounter = 0.0; accelerationCounter < 1.0; accelerationCounter = accelerationCounter + 0.01){
			timerStart = get_ms();
			
			motorRightSpeed = speedCurrentRight + (setSpeedRight * (accelerationCounter + ( ( 1 / ( 2 * M_PI ) ) * sin ( 2 * M_PI * accelerationCounter ) ) ) );
			
			motorLeftSpeed = speedCurrentLeft - (setSpeedLeft * (accelerationCounter + ( ( 1 / ( 2 * M_PI ) ) * sin ( 2 * M_PI * accelerationCounter ) ) ));
			
			set_motors(motorLeftSpeed, motorRightSpeed);

			while ( (get_ms() - timerStart ) < (aggressionFactor * 10.0) ) {
				//change for optimal acceleration time.
			}
		}
		speedCurrentRight = speed;
		speedCurrentLeft = -speed;
		break;
		
		default:		//The default case puts the robot into a full stop and is only used in emergency situations. Using this case is not recommended as it applies the brakes instantaneously and therefore creates an extreme jerk in the acceleration curve.
		set_motors(0,0);
		break;
	}
}