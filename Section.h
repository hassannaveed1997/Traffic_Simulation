//* Author: Dhiraj Amarnani, Hassan Naveed, Andre Koppert
//* Date: December 18 2017

#ifndef __SECTION_H__
#define __SECTION_H__

using namespace std;

//*******************************************************************
//* 
//* This header file declares the methods and data fields to be 
//* included in the Section class. It contains a constructor, 
//* destructor and fields to determine its occupied status. 
//* 
//*******************************************************************
class Section
{

	public:
		bool occupied;
		char occupiedBy;

		Section();
		~Section();

};

#endif