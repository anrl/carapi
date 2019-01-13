#include "car_api.h"
#include "JAMScript/deps/cellulariot/src/cellulariot.h"
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
	pinMode (lp0, OUTPUT) ;//setup each pin to output mode
	pinMode (lp1, OUTPUT) ;
	pinMode (rp0, OUTPUT) ;
	pinMode (rp1, OUTPUT) ;
	return new_car;
}

void move_car_fwd(struct Car car){//moves the car forward at max motor speed
	digitalWrite(car.left_pin_0,HIGH);
	digitalWrite(car.left_pin_1,LOW);
	digitalWrite(car.right_pin_0,HIGH);
	digitalWrite(car.right_pin_1,LOW);
	return;
} 
void move_car_bwd(struct Car car){//moves the car backward
	digitalWrite(car.left_pin_0,LOW);
	digitalWrite(car.left_pin_1,HIGH);
	digitalWrite(car.right_pin_0,LOW);
	digitalWrite(car.right_pin_1,HIGH);
	return;
};

void stop_car(struct Car car){//stop the vehicle
	digitalWrite(car.left_pin_0,LOW);
	digitalWrite(car.left_pin_1,LOW);
	digitalWrite(car.right_pin_0,LOW);
	digitalWrite(car.right_pin_1,LOW);
	return;
}

void move_car_left(struct Car car){//moves the car left
	digitalWrite(car.left_pin_0,LOW);
	digitalWrite(car.left_pin_1,LOW);
	digitalWrite(car.right_pin_0,HIGH);
	digitalWrite(car.right_pin_1,LOW);
	return;
}

void move_car_right(struct Car car){// moves the car right
	digitalWrite(car.left_pin_0,HIGH);
	digitalWrite(car.left_pin_1,LOW);
	digitalWrite(car.right_pin_0,LOW);
	digitalWrite(car.right_pin_1,LOW);
	return;
}

void initialise_car_acceleration(struct Car car){//initialise car accelerometer values
	stop_car(car);
	sleep(1);//give car time to stop
	int accelerometer_data[3];
	int accelerometer_at_zero[3]={0,0,0};//accelerometer reading when car is stopped
	
	int num_readings=100;
	for (int x=0;x<num_readings;x++){//take average to minimise error
		read_acc(accelerometer_data);
		accelerometer_at_zero[0]+=accelerometer_data[0];
		accelerometer_at_zero[1]+=accelerometer_data[1];
		accelerometer_at_zero[2]+=accelerometer_data[2];
		}
	accelerometer_at_zero[0]=accelerometer_at_zero[0]/num_readings;
	accelerometer_at_zero[1]=accelerometer_at_zero[1]/num_readings;
	accelerometer_at_zero[2]=accelerometer_at_zero[2]/num_readings;
	
		
	int acc_summation[3]={0,0,0};//accumulate all acceleration readings
	int counter=0;//counter
	clock_gettime(&start_time,NULL);//clock start
	move_car_fwd(car);
	float curr_acc_magnitude=0;
	
	do{
		read_acc(accelerometer_data);
		accelerometer_data[0]-=accelerometer_at_zero[0];
		accelerometer_data[1]-=accelerometer_at_zero[1];
		accelerometer_data[2]-=accelerometer_at_zero[2];
		acc_summation[0]+=accelerometer_data[0];
		acc_summation[1]+=accelerometer_data[1];
		acc_summation[2]+=accelerometer_data[2];
		counter+=1;
		curr_acc_magnitude=sqrt(pow(accelerometer_data[0],2)+pow(accelerometer_data[1],2)+pow(accelerometer_data[2],2));
		}
	while(!(curr_acc_magnitude<=(5)));//while not achieved constant velocity
	gettimeofday(&stop_time,NULL);
	
	car.avg_acceleration_during_startup=sqrt(pow(acc_summation[0]/counter,2)+pow(acc_summation[1]/counter,2)+pow(acc_summation[2]/counter,2));
	car.time_till_max_acceleration=stop_time.tv_usec-start_time.tv_usec;
	car.max_velocity=car.avg_acceleration_during_startup*car.time_till_max_acceleration;
	car.distance_till_max_velocity=car.max_velocity*car.time_till_max_acceleration;
	
	
	
	return;
}
