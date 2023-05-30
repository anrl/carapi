all: car_api.o
	ar rcs  car_api.a *.o
	rm *.o

car_api.o: car_api.c car_api.h
	gcc -c car_api.c -lwiringPi

clean:
	rm *.o *.a;
