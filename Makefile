CELLULARIOT_DIR=JAMScript/deps/cellulariot
all: car_api.o cellulariot.a
	ar -x $(CELLULARIOT_DIR)/target/cellulariot.a
	ar rcs  car_api.a *.o
	rm *.o

car_api.o: car_api.c car_api.h 
	gcc -c car_api.c -lwiringPi

cellulariot.a: $(CELLULARIOT_DIR)/src/cellulariot.h $(CELLULARIOT_DIR)/src/cellulariot.c
	cd $(CELLULARIOT_DIR);\
	make

clean: 
	rm *.o *.a;
