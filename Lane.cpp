//* Author: Dhiraj Amarnani, Hassan Naveed, Andre Koppert
//* Date: December 18 2017

#include "Lane.h"
#include <iostream>

using namespace std;


//*******************************************************************
//* Lane()
//* 
//* The constructor of our Lane class that creates a new 
//* instance of our Lane class. It takes a enum direction to, int
//* size, intersections one and two as well as a traffic signal. It
//* does not return anything
//*
//* Pre-conditions: Direction to initializes the lane direction.
//* 				int size initializes the size of the lane.
//*					Intersection* _one _two to add to this lane.
//*					TrafficSignal* _myTrafficSignal to add to this 
//* 				lane.
//* 
//*******************************************************************
Lane::Lane(Direction to, int size, Intersection* _one, Intersection* _two, TrafficSignal* _myTrafficSignal){
	
	going = to;
	sizeOfLane = size;
	one = _one;
	two = _two;
	myTrafficSignal = _myTrafficSignal;

	//initialize thisLane array as pointers to sections
	thisLane = new Section*[size];
	for(int i = 0 ; i < size; i++){

		thisLane[i] = new Section;
	}
	//delete sections to free memory
	delete thisLane[size/2];
	delete thisLane[size/2 -1];
	//reallocate freed memory above to intersection
	thisLane[( sizeOfLane/2 )- 1] = one;
	thisLane[( sizeOfLane/2 )] = two;

}
	
//*******************************************************************
//* ~Lane()
//* 
//* The destructor of our Lane class. It does not take any parameters 
//* or return anything. 
//* 
//*******************************************************************
Lane::~Lane(){

	//delete all sections in thisLane array of pointers
	for (int i = 0; i < this-> sizeOfLane; i++){

		if (i != this->sizeOfLane/2 && i != this-> sizeOfLane/2-1){

			delete thisLane[i];
		}
	}

	//delete the lane itself 
	delete [] thisLane;
}