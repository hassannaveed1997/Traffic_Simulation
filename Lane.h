//* Author: Dhiraj Amarnani, Hassan Naveed, Andre Koppert
//* Date: December 18 2017

#ifndef __LANE_H__
#define __LANE_H__

#include "Section.h"
#include "Intersection.h"
#include "TrafficSignal.h"

using namespace std;

//*******************************************************************
//* 
//* This header file declares the methods and data fields to be 
//* included in the Lane class. It contains a constructor and 
//* destructor methods. It also holds its direction, its respective
//* sections and intersections as well as a traffic signal. 
//* 
//*******************************************************************
class Lane
{
	
	public:
		enum Direction {N,E,S,W};
		Section** thisLane;
		Direction going;
		Intersection* one;
		Intersection* two;
		int sizeOfLane;
		TrafficSignal* myTrafficSignal;
		
	public:
		Lane(Direction to, int size, Intersection* _one, Intersection* _two, TrafficSignal* _myTrafficSignal);
		~Lane();

};

#endif