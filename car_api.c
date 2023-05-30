#include "car_api.h"
#include <math.h>
#include <unistd.h>
#include <sys/time.h>

struct timeval start_time,stop_time;

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
