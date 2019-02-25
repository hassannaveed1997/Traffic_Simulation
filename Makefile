CC = g++        # the compiler to use
LD = $(CC)      # command used to link objects (usually same as compiler)
INCDIR = -I../  # additional directories to look for include files
CCFLAGS = -g -c -std=gnu++11   # compiler options
LDFLAGS = -g -std=gnu++11               # linker options

run: Main.o Section.o Lane.o Intersection.o Vehicle.o TrafficSignal.o
	$(LD) $(LDFLAGS) Main.o Section.o Lane.o Vehicle.o TrafficSignal.o Intersection.o -o run
Main.o: Main.cpp Section.cpp Lane.cpp Vehicle.cpp TrafficSignal.cpp Intersection.cpp
	$(CC) $(CCFLAGS) Main.cpp Section.cpp Lane.cpp Vehicle.cpp TrafficSignal.cpp Intersection.cpp
Section.o: Section.cpp Section.h
	$(CC) $(CCFLAGS) Section.cpp
Lane.o: Lane.cpp Lane.h Section.h Intersection.h TrafficSignal.h
	$(CC) $(CCFLAGS) Lane.cpp
Intersection.o: Intersection.cpp Intersection.h Section.h
	$(CC) $(CCFLAGS) Intersection.cpp
Vehicle.o: Vehicle.cpp Vehicle.h Lane.h TrafficSignal.h
	$(CC) $(CCFLAGS) Vehicle.cpp
TrafficSignal.o: TrafficSignal.cpp TrafficSignal.h
	$(CC) $(CCFLAGS) TrafficSignal.cpp
clean:
	/bin/rm -f Main.o Section.o Lane.o Intersection.o Vehicle.o TrafficSignal.o run
