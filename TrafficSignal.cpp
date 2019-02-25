//* Author: Dhiraj Amarnani, Hassan Naveed, Andre Koppert
//* Date: December 18 2017

#include "TrafficSignal.h"
#include <iostream>

using namespace std;

//*******************************************************************
//* TrafficSignal()
//* 
//* The constructor of our TrafficSignal class that creates a new 
//* instance of our trafficSignal class. It takes the red (r), yellow
//* (y) and green (g) ticks for the light duration and its initial
//* light color. It does not return anything. 
//*
//* Pre-conditions: Int r,y,g for red, yellow green light durations.
//* 				Char initState for its initial state
//* 
//*******************************************************************
TrafficSignal::TrafficSignal(int r, int y, int g, char initState){

	//initialize red, yellow, green light durations
	redTicks = r;
	yellowTicks = y;
	greenTicks = g;

	switch(initState){
		case 'R':
			timeUntilNext = r;
			light = R;
			break;
		case 'G':
			timeUntilNext = g;
			light = G;
			break;
	}
	
}

//*******************************************************************
//* ~TrafficSignal()
//* 
//* The destructor of our TrafficSignal class. It does not take any 
//* parameters or return anything. 
//* 
//*******************************************************************
TrafficSignal::~TrafficSignal(){

}

//*******************************************************************
//* updateTimeUntilNext()
//* 
//* This method updates the time until the light changes every time
//* it is called. It does not take any parameters or return anything.
//* 
//*******************************************************************
void TrafficSignal::updateTimeUntilNext(){

	//decrement time until next
	timeUntilNext = timeUntilNext - 1;

	//change light and timeUntilNext light accordingly
	if(timeUntilNext == 0){

		if(light == R){

			light = G;
			timeUntilNext = greenTicks;
		}
		else if(light == G){

			light = Y;
			timeUntilNext = yellowTicks;
		}
		else{

			light = R;
			timeUntilNext = redTicks;
		}

	}
}

//*******************************************************************
//* printCurrent()
//* 
//* This method prints the current state of this trafficSignal every
//* time it is called. It prints the time until the next change and
//* the current light. It does not take any parameters or return
//* anything. 
//* 
//*******************************************************************
void TrafficSignal::printCurrent(){

	//print following to standard output 
	cout << "Time Until Next: " << timeUntilNext << endl;

	switch(light){
		case R:
			cout << "Red" << endl;
			break;
		case Y:
			cout << "Yellow" << endl;
			break;
		case G:
			cout << "Green" << endl;
			break;
	}


}


