#include <pololu/3pi.h>		//Here the used libraries are imported.
#include <avr/pgmspace.h>
#include <stdio.h>

int miscBatteryCheck(){		//This function checks the battery voltage and compares it with the 65% level of its total capacity. The function returns a '1' when the robot requires charging.
							//The limits used for calculating the 65% is set to 4.5 -> 6.2 V, presenting a 1.7 V capacity window.
	int batteryVoltage = read_battery_millivolts();		//The current battery voltage in mV is loaded into the defined variable 'batteryVoltage'.
	
	if (batteryVoltage < 5600){							//The 65% mark is reached when the battery voltage drops below 5600 mV -> 5.6 V.
		print("Battery");								//The robot displays "Battery Low!" on the LCD when the battery voltage drops below the lower limit.
		print("Low!")
		miscBatteryCharge();							//The robot calls the 'miscBatteryCharge()' function when the battery voltage drops too low. This will send the robot to its charging station.
		return 1;
	}
	
	else{
		return 0;
	}
}

void miscBatteryCharge(){								//This sub routine sends the robot to its charging station after it has finished with delivering the current products to the home station.
	//Send robot to charging station.
}