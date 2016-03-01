CFLAGS = `pkg-config --cflags opencv`
LIBS = `pkg-config --libs opencv`

cpu: RegionOfInterest.o UcharSerialCamShift.o main.o
	g++ RegionOfInterest.o UcharSerialCamShift.o main.o -o cpu `pkg-config opencv --cflags --libs`
main.o: main.cpp
	g++ -c main.cpp `pkg-config opencv --cflags --libs`
RegionOfInterest.o: RegionOfInterest.cpp
	g++ -c RegionOfInterest.cpp `pkg-config opencv --cflags --libs`
UcharSerialCamShift.o: UcharSerialCamShift.cpp
	g++ -c UcharSerialCamShift.cpp `pkg-config opencv --cflags --libs`
clean:
	rm *.o ./cpu
run:
	./cpu perry.mov input/windows.txt;
