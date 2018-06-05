/*
 * sensoren.h
 *
 * Created: 3-6-2018 23:15:57
 *  Author: 2125228
 */ 


#ifndef SENSOREN_H_
#define SENSOREN_H_



#define STRAIGHT 0
#define T_LEFT 5
#define T_RIGHT 4
#define T_LEFT_RIGHT 3
#define FOUR_WAY_JOINT 6
#define LEFT 2
#define RIGHT 1

#define highRange
#define lowRange

#define SENSOR_L sensors[0]
#define SENSOR_C_L sensors[1]
#define SENSOR_C_C sensors[2]
#define SENSOR_C_R sensors[3]
#define SENSOR_R sensors[4]

#define SPEED 60
#define ALTER 15
#define SLOW SPEED - ALTER
#define FAST SPEED + ALTER

int checkAfslag();
void followLine();
void initialize();
void display_readings(const unsigned int *calibrated_values);
void load_custom_characters();

#endif /* SENSOREN_H_ */