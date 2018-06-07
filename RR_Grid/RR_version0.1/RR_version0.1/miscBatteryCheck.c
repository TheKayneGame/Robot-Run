#include <pololu/3pi.h>
#include <avr/pgmspace.h>
#include <stdio.h>

int miscBatteryCheck(){
	int batteryVoltage = read_battery_millivolts();
	
	if (batteryVoltage < 5600){
		print("Battery");
		print("Low!")
		miscBatteryCharge();
		return 1;
	}
	
	else{
		return 0;
	}
}

void miscBatteryCharge(){
	//Send robot to charging station.
}