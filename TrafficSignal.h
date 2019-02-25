//* Author: Dhiraj Amarnani, Hassan Naveed, Andre Koppert
//* Date: December 18 2017

#ifndef __TRAFFICSIGNAL_H__
#define __TRAFFICSIGNAL_H__

using namespace std;

//*******************************************************************
//* 
//* This header file declares the methods and data fields to be 
//* included in the TrafficSignal class. It contains a constructor, 
//* destructor, updateTimeUntilNext and printCurrent methods. It 
//* also contains fields for its current state, the duration of green
//* yellow, red lights and timeUntilNext light change. 
//* 
//*******************************************************************
class TrafficSignal
{

	public:

		enum State {R,Y,G};

		int redTicks;
		int yellowTicks;
		int greenTicks;

		int timeUntilNext;

		State light;

		TrafficSignal(int r, int y, int g, char initState);
		~TrafficSignal();
		void updateTimeUntilNext();
		void printCurrent();
		
};

#endif