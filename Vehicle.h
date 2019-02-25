//* Author: Dhiraj Amarnani, Hassan Naveed, Andre Koppert
//* Date: December 18 2017

#ifndef __VEHICLE_H__
#define __VEHICLE_H__

#include "Lane.h"
#include "TrafficSignal.h"

using namespace std;

//*******************************************************************
//* 
//* This header file declares the methods and data fields to be 
//* included in the Vehicle class. It contains a constructor, 
//* destructor, and methods that proceed that car in its respective
//* direction. It also contains fields that hold its intended 
//* direction of turning, its current and future lanes, its position 
//* in the lane and its size. 
//* 
//*******************************************************************
class Vehicle
{

	public:
		enum RelativeTurn{right, left, straight};
		RelativeTurn myTurn;
		Lane* to;
		Lane* from;
		int size;
		int positionInLane;
		Section** occupiedSections; //pointer to array of pointers to sections car currently occupies
		Lane* currentLane;

		Vehicle(int sizeOfVehicle, Lane* goingFrom, Lane* goingTo, RelativeTurn turn);
		~Vehicle();
		bool canProceed();
		void proceed();
		char type();

	private:
		void proceedStraight();
		void proceedLeft();
		void proceedRight();

};

#endif