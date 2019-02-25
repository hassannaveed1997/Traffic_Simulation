//* Author: Dhiraj Amarnani, Hassan Naveed, Andre Koppert
//* Date: December 18 2017

#ifndef __INTERSECTION_H__
#define __INTERSECTION_H__

#include "Section.h"

using namespace std;

//*******************************************************************
//* 
//* This header file declares the methods and data fields to be 
//* included in the Intersection class that is extended from section.
//* It contains a constructor, destructor and a method and field to
//* determine and manipulate how much longer it will be in use. 
//* 
//*******************************************************************
class Intersection : public Section
{

	public:
		int timeInUse;

		Intersection();
		~Intersection();

		void updateTimeInUse();

};

#endif