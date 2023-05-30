all: ../../car_api.o pin_permute.o
	gcc -Wall -o pin_permute pin_permute.o ../../car_api.o -lwiringPi

pin_permute.o: pin_permute.c
	gcc -c pin_permute.c

clean:
	rm pin_permute.o pin_permute
