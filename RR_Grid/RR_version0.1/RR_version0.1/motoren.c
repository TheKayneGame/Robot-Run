/* Test application RobotRun G6 - an application for the Pololu 3pi Robot
*
* This application uses the Pololu AVR C/C++ Library.  For help, see:
* -User's guide: http://www.pololu.com/docs/0J20
* -Command reference: http://www.pololu.com/docs/0J18
*
* Created: 5/14/2018 3:07:29 PM
*  Author: Jonathan
*/

#include <pololu/3pi.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <math.h>

enum directions{ F=0,B,R,L};

int speedCurrent = 0;
int speedCurrentRight = 0;
int speedCurrentLeft = 0;

void motorControl(int speed, char direction, float aggressionFactor){
	
	float accelerationCounter, motorLeftSpeed, motorRightSpeed;
	int timerStart = 0;
	
	int setSpeed = 0;
	int setSpeedRight = 0;
	int setSpeedLeft = 0;
	
	//directions direction;

	switch (direction){
		case 'F':
		
		setSpeed = speed - speedCurrent;
		
		for (accelerationCounter = 0.0; accelerationCounter < 1.0; accelerationCounter = accelerationCounter + 0.01){
			timerStart = get_ms();
			
			motorLeftSpeed = motorRightSpeed = speedCurrent + setSpeed * (accelerationCounter - ( ( 1 / ( 2*M_PI ) ) * sin ( 2* M_PI * accelerationCounter ) ) );
			
			set_motors(motorLeftSpeed, motorRightSpeed);

			while ( (get_ms() - timerStart ) < (aggressionFactor * 10.0) ) {
				//change for optimal acceleration time.
			}
		}
		speedCurrent = speed;
		break;
		
		case 'B':
		
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

		case 'R':
		
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

		case 'L':
		
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
		
		default:
		set_motors(0,0);
		break;
	}
}