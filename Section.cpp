//* Author: Dhiraj Amarnani, Hassan Naveed, Andre Koppert
//* Date: December 18 2017

#include "Section.h"
#include <iostream>

using namespace std;

//*******************************************************************
//* Section()
//* 
//* The constructor of our section class. Creates a new empty 
//* section instance of our section class. It does not take any 
//* parameters and does not return anything. 
//* 
//*******************************************************************
Section::Section(){

	//set occupied to false by default
	occupied = false;

	//if not occupied, set to '.' character for printing to standard output 
	occupiedBy = '.';
}

//*******************************************************************
//* ~Section()
//* 
//* The destructor of our Section class. It does not take any 
//* parameters or return anything. 
//* 
//*******************************************************************
Section::~Section(){

}