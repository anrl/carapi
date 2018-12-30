//Raspberry Pi api for controlling a car using GPIO pins
//Author: Abhi Singh
//Created: December 28th 2018

#include <wiringPi.h>
// this makes use of the wiringPi interface for GPIO control 
// found at http://wiringpi.com/download-and-install/
// you must run your c program by linking to the object car_api.o file and compile with -lwiringPi
struct Car{
	int left_pin_0;
	int left_pin_1;
	int right_pin_0;
	int right_pin_1;
};

struct Car setup_new_car(int lp0,int lp1,int rp0,int rp1);//create a new car and specify corresponding WIRINGPi Pin numbers (NOTE THAT THIS IS DIFFERENT FROM BOTH BCM AND PIN NUMBERS). 
//WIRING PI PIN NUMBERS ARE FOUND HERE: https://pinout.xyz/ Hover over the corresponding pin with the mouse to find the WIRING PI Numbers

void move_car_fwd(struct Car car);// move car forward constantly

void move_car_bwd(struct Car car);// move car backwards constantly

void move_car_left(struct Car car);// turn car left constantly

void move_car_right(struct Car car);// turn car right constantly

void stop_car(struct Car car);// stop car


//future goals: specify degrees of turning using accelormeter
//set speed of vehicle


