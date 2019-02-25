//* Author: Dhiraj Amarnani, Hassan Naveed, Andre Koppert
//* Date: December 18 2017

#include "Intersection.h"
#include <iostream>

using namespace std;

//*******************************************************************
//* Intersection()
//* 
//* The constructor of our Intersection class. Creates a new empty 
//* Intersection instance of our Intersection class. It does not take any 
//* parameters and does not return anything.
//* 
//*******************************************************************
Intersection::Intersection() : Section(){

	//default value zero for time in use
	timeInUse = 0;
}

//*******************************************************************
//* ~Section()
//* 
//* The destructor of our Intersection class. It does not take any 
//* parameters or return anything. 
//* 
//*******************************************************************
Intersection::~Intersection(){

}

//*******************************************************************
//* updateTimeInUse()
//* 
//* This method updates the time in use of our intersection after 
//* every call. 
//* 
//*******************************************************************
void Intersection::updateTimeInUse(){

	//update time in use by decrementing one at every call.
	if(timeInUse > 0){

		timeInUse -= 1;
	}
}