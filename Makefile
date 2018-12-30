all: car_api.c car_api.h
	gcc -c car_api.c -lwiringPi

clean: 
	rm car_api.o