//Raspberry Pi api for controlling a car using GPIO pins
//Author: Abhi Singh
//Created: December 28th 2018

#include <wiringPi.h>
// this makes use of the wiringPi interface for GPIO control
// found at http://wiringpi.com/download-and-install/

#if  defined __has_include
#if __has_include ("pins.h")
#include "pins.h"
#else
#define PINS_DEFAULT {0,2,3,4}
#endif
#else
#define PINS_DEFAULT {0,2,3,4}
#endif

struct Car{
	int left_pin_0;
	int left_pin_1;
	int right_pin_0;
	int right_pin_1;
	float avg_acceleration_during_startup;//measured average acceleration until a consistent velocity is achieved
	float time_till_max_acceleration;//time it takes to achieve max speed
	float max_velocity;//the maximum speed the car acheives
	float distance_till_max_velocity;//distance the car travels till it achieves max speed

	float turning_radius;//radius the car requires to turn
	float angular_velocity;//degrees the car turns per unit time
};

struct Car setup_new_car(int lp0,int lp1,int rp0,int rp1){//specify which pins correspond to which side of the car
	struct Car new_car;
	new_car.left_pin_0=lp0;
	new_car.left_pin_1=lp1;
	new_car.right_pin_0=rp0;
	new_car.right_pin_1=rp1;
	wiringPiSetup();// sets up the wiring pi library
	pinMode(lp0,OUTPUT);//setup each pin to output mode
	pinMode(lp1,OUTPUT);
	pinMode(rp0,OUTPUT);
	pinMode(rp1,OUTPUT);
	return new_car;
}

struct Car setup_default_car(){
    return setup_new_car(PINS_DEFAULT[0], PINS_DEFAULT[1], PINS_DEFAULT[2], PINS_DEFAULT[3]);
}

void move_car_fwd(struct Car car){//moves the car forward at max motor speed
	digitalWrite(car.left_pin_0,HIGH);
	digitalWrite(car.left_pin_1,LOW);
	digitalWrite(car.right_pin_0,HIGH);
	digitalWrite(car.right_pin_1,LOW);
}
void move_car_bwd(struct Car car){//moves the car backward
	digitalWrite(car.left_pin_0,LOW);
	digitalWrite(car.left_pin_1,HIGH);
	digitalWrite(car.right_pin_0,LOW);
	digitalWrite(car.right_pin_1,HIGH);
}

void stop_car(struct Car car){//stop the vehicle
	digitalWrite(car.left_pin_0,LOW);
	digitalWrite(car.left_pin_1,LOW);
	digitalWrite(car.right_pin_0,LOW);
	digitalWrite(car.right_pin_1,LOW);
}

void move_car_left(struct Car car){//moves the car left
	digitalWrite(car.left_pin_0,LOW);
	digitalWrite(car.left_pin_1,LOW);
	digitalWrite(car.right_pin_0,HIGH);
	digitalWrite(car.right_pin_1,LOW);
}

void move_car_right(struct Car car){// moves the car right
	digitalWrite(car.left_pin_0,HIGH);
	digitalWrite(car.left_pin_1,LOW);
	digitalWrite(car.right_pin_0,LOW);
	digitalWrite(car.right_pin_1,LOW);
}
