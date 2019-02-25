//* Author: Dhiraj Amarnani, Hassan Naveed, Andre Koppert
//* Date: December 18 2017

#include "Vehicle.h"
#include <iostream>

using namespace std;

//*******************************************************************
//* Vehicle()
//* 
//* The constructor of our Vehicle class that creates a new instance 
//* of our Vehicle class. It takes an int sizeOfVehicle, lanes 
//* goingFrom and goingTo and enum turn as parameters and does not
//* return anything. 
//*
//* Pre-conditions: int sizeOfVehicle initializes the size of vehicle
//*					Lane* goingFrom goingTo to determine lanes the 
//*					vehicle will occupy. 
//*					RelativeTurn turn to initialize its intended
//*					final direction. 
//* 
//*******************************************************************
Vehicle::Vehicle(int sizeOfVehicle, Lane* goingFrom, Lane* goingTo, RelativeTurn turn){

	//initialize the variables passed as arguments to constructor
	size = sizeOfVehicle;
	to = goingTo;
	from = goingFrom;
	myTurn = turn;
	currentLane = goingFrom;

	//set position in lane to start and dynamically allocate array of pointers to sections
	positionInLane = 0;
	occupiedSections = new Section*[size];

	//set first section occupied by car
	occupiedSections[0] = goingFrom->thisLane[0];
	occupiedSections[0]->occupied = true;
}

//*******************************************************************
//* ~Vehicle()
//* 
//* The destructor of our Vehicle class. It does not take any 
//* parameters or return anything. 
//* 
//*******************************************************************
Vehicle::~Vehicle(){

	delete [] occupiedSections;
}

//*******************************************************************
//* canProceed()
//* 
//* This method determines if this car can proceed forward or its
//* intended direction in its call. It does not take any parameters 
//* and returns a boolean true or false if all conditions to proceed
//* are met. 
//*
//* Post-Conditions: bool true if conditions to proceed are met, false
//* 				 otherwise. 
//* 
//*******************************************************************
bool Vehicle::canProceed(){ 

	//if the car is not at the end of the lane, then checks whether the next position is open to move.
	if( (positionInLane+1) < currentLane->sizeOfLane ){

		if(currentLane->thisLane[positionInLane+1]->occupied == true ){

			return false;
		}
	}

	//initialize the variable cleartime to determine how long it will take car to clear the intersection
	int clearTime; 
	switch(myTurn){
		case straight:
			clearTime = size + 2;
			break;
		case right:
			clearTime = size + 1;
			break;
		case left:
			clearTime = size + 3;
			break;
	}

	//first checks if the car is at the intersection
		//if it is at the intersection, vehicle looks at status of lights to see if it can clear intersection in time
	if(positionInLane == ((from -> sizeOfLane)/2 - 2) ){ 

		if(from -> myTrafficSignal -> light == TrafficSignal::R){

			return false;
		}
		else if(from -> myTrafficSignal -> light == TrafficSignal::Y){

			if(from -> myTrafficSignal -> timeUntilNext < clearTime){

				return false;
			}
		}
		else if(from -> myTrafficSignal -> light == TrafficSignal::G){

			if(((from -> myTrafficSignal -> timeUntilNext) + (from -> myTrafficSignal -> yellowTicks)) < clearTime){

				return false;
			}
		}

		//determines if intersections that will be crossed by this vehicle (based on turning direction) is clear before entering intersection
		switch(myTurn){

			case straight:

				if (currentLane-> one ->timeInUse > 0 || currentLane -> two->timeInUse > 1 ){

					return false;
				}
				break;
			case right:

				if (currentLane -> one-> timeInUse > 0 ){

					return false;
				}
				break;
			case left:

				if (from->one->timeInUse > 0 || to -> one->timeInUse > 1 || to ->two -> timeInUse > 2){

					return false;
				}
				break;
		}

	}

	//if not at intersection and no cars in front of it, canProceed returns true
	return true;
}

//*******************************************************************
//* proceed()
//* 
//* This method proceeds the car one section in front. Should be 
//* called subsequently after canProceed checked and returned true.
//* It does not take any parameters and does not return anything. 
//* 
//*******************************************************************
void Vehicle::proceed(){

	//if the car is entering the lane, move each occupied section by car by one
	if(positionInLane<size-1){

		//initialize remaining occupied sections in car and update lane. 
		for (int i = 0; i < size; i++){

			if (positionInLane+1-i<0){
				//do nothing
			}

			else{

				occupiedSections[i] = currentLane->thisLane[positionInLane+1-i];
				occupiedSections[i]->occupied = true;
				occupiedSections[i]->occupiedBy = type();
			}


		}

		//increment position in lane
		positionInLane++;
	}
	//if car is leaving simulation
	else if(positionInLane == currentLane->sizeOfLane-1){
		
		positionInLane--;
		proceedStraight();
		positionInLane++;
	}
	else{

		//If car is entering intersection, we update the appropriate time of uses (according to turning direction)
		if(positionInLane == ( currentLane->sizeOfLane / 2 ) -2){

			switch(myTurn){
				case straight:
					currentLane->one->timeInUse = size + 1;
					currentLane->two->timeInUse = size + 2;
					break;
				case right:
					from->one->timeInUse = size + 1;
					break;
				case left:
					from->one->timeInUse = size + 1;
					from->two->timeInUse = size + 2;
					to -> two->timeInUse = size + 3;
					break;
			}

		}


		switch(myTurn){
			case straight:
				break;
			//if its turning right and its time to swap lanes, we call proceed right method
			case right:
				if( (positionInLane == currentLane->sizeOfLane /2 -1) ){
					proceedRight();
				}
				break;
			//if its turning left and its time to swap lanes and we havent swapped lanes yet, we call proceed left method
			case left:
				if ( (positionInLane == currentLane->sizeOfLane /2)
						&& ( currentLane == from) ){
					proceedLeft();
				}
				break;
		}

		
		



		//finally, we call the proceed straight method and increment position in lane
		proceedStraight();
		positionInLane++;
	}


}

//*******************************************************************
//* proceedStraight()
//* 
//* This private helper method proceeds the car in its current 
//* direction one section forward. It does not take any parameters
//* and does not return anything 
//* 
//*******************************************************************
void Vehicle::proceedStraight(){

	//save the last position of the car
	Section* temp = occupiedSections[size-1];

	//set pointers in occupied sections of this vehicle to the next except the head
	for (int i = size-1 ; i > 0 ; i--){
		occupiedSections[i] = occupiedSections[i-1];
	}

	//set the head to next position
	occupiedSections[0] = currentLane->thisLane[positionInLane+1];
	occupiedSections[0]->occupied = true;
	occupiedSections[0]->occupiedBy = type();

	//set previous last section to unoccupied to finally move car forward one section
	temp->occupied = false;
	temp->occupiedBy = '.';

}

//*******************************************************************
//* proceedRight()
//* 
//* This private helper method changes the direction of the car to
//* turn right. It does not take any parameters and does not return 
//* anything. 
//* 
//*******************************************************************
void Vehicle::proceedRight(){

	//swaps lanes and increments the position counter
	currentLane = to;
	positionInLane++;
}

//*******************************************************************
//* proceedRight()
//* 
//* This private helper method changes the direction of the car to
//* turn left. It does not take any parameters and does not return 
//* anything. 
//* 
//*******************************************************************
void Vehicle::proceedLeft(){

	//swaps lanes and decrements the position counter
	currentLane = to;
	positionInLane--;
}

//*******************************************************************
//* type()
//* 
//* This method returns the char type of vehicle denoted by the 
//* following characters: 'c' for car, 's' for SUV, 't' for truck.
//*
//* Post Conditions: char representing vehicle type. 
//* 
//*******************************************************************
char Vehicle::type(){

	if (size == 2){
		return 'c';
	} else if (size == 3){
		return 's';
	} else {
		return 't';
	}
}