/*
 * sensoren.h
 *
 * Created: 3-6-2018 23:15:57
 *  Author: 2125228
 */ 


#ifndef SENSOREN_H_
#define SENSOREN_H_


void followLine();
void objectOmzeilen();
void load_custom_characters();
void initialize();
int checkDistance();
int checkAfslag();

unsigned int sensors[5];
unsigned int sensorValues[20];
unsigned int sensorValues2[20];

int distance;
int distance2;
int sensorDistance;
int sensorDistance2;

#define high_range 1800
#define low_range 1000

#define dichtbij 20
#define heelDichtbij 10

#define STRAIGHT 0
#define T_LEFT 1
#define T_RIGHT 2
#define T_LEFT_RIGHT 3
#define FOUR_WAY_JOINT 4
#define LEFT 5
#define RIGHT 6
#define DEAD_END 7
#define GRID_HOME 8

#define SENSOR_L sensors[0]
#define SENSOR_C_L sensors[1]
#define SENSOR_C_C sensors[2]
#define SENSOR_C_R sensors[3]
#define SENSOR_R sensors[4]

#define SPEED 60
#define ALTER 0
#define SLOW SPEED - ALTER
#define FAST SPEED + ALTER


#endif /* SENSOREN_H_ */