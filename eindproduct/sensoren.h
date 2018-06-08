/*
 * sensoren.h
 *
 * Created: 3-6-2018 23:15:57
 *  Author: 2125228
 */ 


#ifndef SENSOREN_H_
#define SENSOREN_H_


void followLine();
void initialize();
void moveObject();
int checkDistance();


unsigned int sensors[5];
unsigned int sensorValues[20];
unsigned int sensorValues2[20];

int distance;
int distance2;
int sensorDistance;
int sensorDistance2;

#define high_range 1800
#define low_range 1000

#define close 20
#define veryClose 10

#define SENSOR_L sensors[0]
#define SENSOR_C_L sensors[1]
#define SENSOR_C_C sensors[2]
#define SENSOR_C_R sensors[3]
#define SENSOR_R sensors[4]

#define STOP 0
#define SPEED 60
#define ALTER 5
#define SLOW SPEED - ALTER
#define FAST SPEED + ALTER

extern int situations[3];



#endif /* SENSOREN_H_ */