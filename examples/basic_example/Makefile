all: ../../car_api.o basic_example.o
	gcc -Wall basic_example.o ../../car_api.o -lwiringPi

basic_example.o: basic_example.c
	gcc -c basic_example.c

clean:
	rm basic_example.o a.out
