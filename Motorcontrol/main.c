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
#include <math.h>

int main()
{
	play_from_program_space(PSTR(">g32>>c32"));  // Play welcoming notes.

		
		float pi = 3.14159265359;

		float motorLeftSpeed, motorRightSpeed, accelerationCounter ;

		float accelerationTimeInterval;
		float accelerationTimePeriod = 1.0; //In seconds.

		int timerStart = 0;
		
		int velocityForward = 250;
		int velocity = 150;
		
		// Print battery voltage (in mV) on the LCD.
		clear();
		print_long(read_battery_millivolts_3pi());

		red_led(1);     // Turn on the red LED.
		delay_ms(200);  // Wait for 200 ms.

		red_led(0);     // Turn off the red LED.
		delay_ms(200);  // Wait for 200 ms.


		for (accelerationCounter = 0.0; accelerationCounter < 1.0; accelerationCounter = accelerationCounter + 0.025) {

			// Start count to accelerationTimeInterval = accelerationTimePeriod/100.

			timerStart = get_ms();

			motorLeftSpeed = velocityForward * (accelerationCounter - ( (1 / (2 * pi) ) * sin((2 * pi * accelerationCounter ))  ) );
			motorRightSpeed = velocityForward * (accelerationCounter - ( (1 / (2 * pi) ) * sin((2 * pi * accelerationCounter ))  ) );
			
			set_motors(motorLeftSpeed, motorRightSpeed);

			// Unlock when accelerationTimeInterval has been reached.

			while ((get_ms() - timerStart) < (accelerationTimePeriod*10.0)){
				
				// Checking sensors? Relaying data?

			}
		}
				for (accelerationCounter = 1.0; accelerationCounter > 0.0; accelerationCounter = accelerationCounter - 0.005) {

					// Start count to accelerationTimeInterval = accelerationTimePeriod/100.

					timerStart = get_ms();

					motorLeftSpeed = velocityForward * (accelerationCounter - ( (1 / (2 * pi) ) * sin((2 * pi * accelerationCounter ))  ) );
					motorRightSpeed = velocityForward * (accelerationCounter - ( (1 / (2 * pi) ) * sin((2 * pi * accelerationCounter ))  ) );
					
					set_motors(motorLeftSpeed, motorRightSpeed);

					// Unlock when accelerationTimeInterval has been reached.

					while ((get_ms() - timerStart) < (accelerationTimePeriod*10.0)){
						
						// Checking sensors? Relaying data?

					}
				}
		
		delay_ms(1500);

for (accelerationCounter = 0.0; accelerationCounter < 1.0; accelerationCounter = accelerationCounter + 0.01) {

	// Start count to accelerationTimeInterval = accelerationTimePeriod/100.

	timerStart = get_ms();

	motorLeftSpeed = -velocity * (accelerationCounter - ( (1 / (2 * pi) ) * sin((2 * pi * accelerationCounter )) ) );
	motorRightSpeed = -velocity * (accelerationCounter - ( (1 / (2 * pi) ) * sin((2 * pi * accelerationCounter )) ) );
	set_motors(motorLeftSpeed, motorRightSpeed);

	// Unlock when accelerationTimeInterval has been reached.

	while ((get_ms() - timerStart) < (accelerationTimePeriod*10.0)){
		
		// Checking sensors? Relaying data?

	}

}
delay_ms(100);
for (accelerationCounter = 1.0; accelerationCounter > 0.0; accelerationCounter = accelerationCounter - 0.01) {

	// Start count to accelerationTimeInterval = accelerationTimePeriod/100.

	timerStart = get_ms();

	motorLeftSpeed = -velocity * (accelerationCounter - ( (1 / (2 * pi) ) * sin((2 * pi * accelerationCounter )) ) );
	motorRightSpeed = -velocity * (accelerationCounter - ( (1 / (2 * pi) ) * sin((2 * pi * accelerationCounter )) ) );
	set_motors(motorLeftSpeed, motorRightSpeed);

	// Unlock when accelerationTimeInterval has been reached.

	while ((get_ms() - timerStart) < (accelerationTimePeriod*10.0)){
		
		// Checking sensors? Relaying data?

	}

}

}
