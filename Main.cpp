//* Author: Dhiraj Amarnani, Hassan Naveed, Andre Koppert
//* Date: December 18 2017

#include <iostream>
#include <stdexcept>
#include <fstream>

#include "Section.h"
#include "TrafficSignal.h"
#include "Vehicle.h"
#include "Intersection.h"
#include "Random.h"

// define the static members in Random
std::mt19937 Random::rng(20); 
std::uniform_real_distribution<double> Random::randdouble(0,1);

#include <chrono>
#include <thread>
#include <vector>

using namespace std;

//*******************************************************************
//* int determineSize()
//* 
//* Pseudo-Randomly determines and returns the size of car to be 
//* added to the simulation. It takes probabilities car_p, suv_p
//* and returns the int size of car generated according to these
//* probabilities. (either car, suv, truck)
//* 
//* Pre-conditions: double car_p suv_p probabilities of seeing car
//* 				and suv. 
//*
//* Post-conditions: int size of car to be generated when method is
//* called. 
//*******************************************************************
int determineSize(double car_p, double suv_p){

	//create random probability between zero and one to compare
	double size_prob = Random::randdouble01();

	//car created
	if(size_prob <= car_p){
		cout << " created a car" <<endl;

		return 2;
	}
	//suv created
	else if(size_prob > car_p && size_prob <= car_p + suv_p){
		cout << " created an SUV" <<endl;
		return 3;

	}
	//truck created
	else{
		cout << "created a truck" <<endl;
		return 4;
	}

}

//*******************************************************************
//* int printLanes()
//* 
//* This method prints a graphical representation of the lanes in
//* our intersection simulation. It takes the 4 lanes, their size, 
//* and 4 intersections as arguments and does not return anything. 
//* 
//* Pre-conditions: Lanes north, south, east, west to be drawn
//* 				Intersections NE, NW, SE, SW to be drawn
//* 				int size holding size of lanes to draw
//*
//*******************************************************************
void printLanes(Lane& north, Lane& south, Lane& east, Lane& west, int size, 
				Intersection& NE, Intersection& NW, Intersection& SE, Intersection& SW){


	//print first half of north and south lanes
	for (int i = 0; i < (size/2 - 1); i++){
			
		for (int i = 0; i < (size/2 - 1); i++){
			cout << "  ";
		}

		cout << south.thisLane[i]->occupiedBy <<" " << north.thisLane[size-1-i]->occupiedBy
			<< "        " <<endl;
	}

	//print first half of West lane
	for (int i = 0; i < (size/2-1); i++){
		cout << west.thisLane[size - 1 - i]->occupiedBy << " ";
	}

	//print north intersections
	cout << NW.occupiedBy << " " << NE.occupiedBy << " ";

	//print rest of West Lane
	for (int i = (size/2 + 1); i < (size); i++){
		cout << west.thisLane[size - 1 - i]->occupiedBy << " ";
	}

	cout << endl;

	//print half of East lane
	for (int i = 0; i < (size/2-1); i++){
		cout << east.thisLane[i]->occupiedBy << " ";
	}

	//print south intersections
	cout << SW.occupiedBy << " " << SE.occupiedBy << " ";

	//print rest of East lane
	for (int i = (size/2 +1 ); i < (size); i++){
		cout << east.thisLane[i]->occupiedBy << " ";
	}

	cout << endl;

	//print rest of north and south lanes
	for (int i = (size/2 +1); i < size; i++){
		for (int i = 0; i < (size/2 - 1); i++){
			cout << "  ";
		}
			
		cout << south.thisLane[i]->occupiedBy << " " << north.thisLane[size-1-i]->occupiedBy
			<< "        " <<endl;
	}

}

//*******************************************************************
//* int main()
//* 
//* This main method initializes all the variables and objects
//* necessary to run our simulation. It also runs our simulation
//* for a pre-determined number of timesteps. 
//*
//* Post-conditions: Prints the simulation at every timestep to 
//* standard output
//*******************************************************************
int main(){

	//read mutable inputs from text file
	ifstream infile;
	infile.open("input.txt");

	double left_p = 0.0;
	double right_p = 0.0;
	double straight_p = 0.0;

	int g_ticks = 0;
	int y_ticks = 0;
	int r_ticks = 0;

	double vehicle_appear_p = 0.0;

	double car_p = 0.0;
	double suv_p = 0.0;

	while(infile.good()){

		if(!infile.eof()){
			infile >> left_p;
			infile >> right_p;
			infile >> g_ticks;
			infile >> y_ticks;
			infile >> r_ticks;
			infile >> vehicle_appear_p;
			infile >> car_p;
			infile >> suv_p;
		}
	}

	infile.close();

	straight_p = 1-left_p-right_p;

	cout << "Left Probability: " << left_p << endl;
	cout << "Right Probability: " << right_p << endl;
	cout << "Straight Probability: " << straight_p << endl;
	cout << "Green Ticks: " << g_ticks << endl;
	cout << "Yellow Ticks: " << y_ticks << endl;
	cout << "Red Ticks: " << r_ticks << endl;
	cout << "Vehicle Appear Probability: " << vehicle_appear_p << endl;
	cout << "Car Probability: " << car_p << endl;
	cout << "SUV Probability: " << suv_p << endl;
	cout << "Truck Probability: " << 1-car_p-suv_p << endl;

	//declare intersections
	Intersection NE;
	Intersection NW;
	Intersection SE;
	Intersection SW;

	//Initialize traffic signals
	TrafficSignal mysignalNS(r_ticks, y_ticks, g_ticks,'R');
	TrafficSignal mysignalEW(g_ticks + y_ticks, r_ticks/2, r_ticks-r_ticks/2,'G');

	//initialize size of lanes and lanes themselves
	int size = 20;

	Lane north(Lane::N , size, &SE, &NE, &mysignalNS);
	Lane south(Lane::S, size, &NW, &SW, &mysignalNS);
	Lane east(Lane::E , size, &SW, &SE, &mysignalEW);
	Lane west(Lane::W , size, &NE, &NW, &mysignalEW);

	//initialize vector to hold pointers to vehicles to be processed by simulation
	std::vector<Vehicle*> myQueue;
	
	int car_size = 0;

	for(int j = 0; j<100;j++){

		/*
		Code to generate vehicles according to probabilities seperately for each lane
		*/

		//for north lane, if probability generated below vehicle appearance and lane is not full
		if(Random::randdouble01() < vehicle_appear_p && north.thisLane[0] -> occupied == false){

			car_size = determineSize(car_p, suv_p);

			double dir_prob = Random::randdouble01();

			//turn left
			if(dir_prob <= left_p){

				myQueue.push_back(new Vehicle(car_size, &north, &west, Vehicle::left));
			}
			//go straight
			else if(dir_prob > left_p && dir_prob <= left_p + straight_p){

				myQueue.push_back(new Vehicle(car_size, &north, &north, Vehicle::straight));
			}
			//turn right
			else{

				myQueue.push_back(new Vehicle(car_size, &north, &east, Vehicle::right));
			}


		}

		//for south lane, if probability generated below vehicle appearance and lane is not full
		if(Random::randdouble01() < vehicle_appear_p && south.thisLane[0] -> occupied == false){

			car_size = determineSize(car_p, suv_p);

			double dir_prob = Random::randdouble01();

			//turn left
			if(dir_prob <= left_p){

				myQueue.push_back(new Vehicle(car_size, &south, &east, Vehicle::left));
			
			}
			//go straight
			else if(dir_prob > left_p && dir_prob <= left_p + straight_p){

				myQueue.push_back(new Vehicle(car_size, &south, &south, Vehicle::straight));
			
			}
			//turn right
			else{

				myQueue.push_back(new Vehicle(car_size, &south, &west, Vehicle::right));
			
			}


		}

		//for east lane, if probability generated below vehicle appearance and lane is not full
		if(Random::randdouble01() < vehicle_appear_p && east.thisLane[0] -> occupied == false){

			car_size = determineSize(car_p, suv_p);

			double dir_prob = Random::randdouble01();

			//turn left
			if(dir_prob <= left_p){

				myQueue.push_back(new Vehicle(car_size, &east, &north , Vehicle::left));
			}
			//go straight
			else if(dir_prob > left_p && dir_prob <= left_p + straight_p){

				myQueue.push_back(new Vehicle(car_size, &east, &east, Vehicle::straight));
			}
			//turn right
			else{

				myQueue.push_back(new Vehicle(car_size, &east, &south, Vehicle::right));
			}


		}

		//for west lane, if probability generated below vehicle appearance and lane is not full
		if(Random::randdouble01() < vehicle_appear_p && west.thisLane[0] -> occupied == false){

			car_size = determineSize(car_p, suv_p);

			double dir_prob = Random::randdouble01();

			//turn left
			if(dir_prob <= left_p){

				myQueue.push_back(new Vehicle(car_size, &west, &south, Vehicle::left));
			}
			//go straight
			else if(dir_prob > left_p && dir_prob <= left_p + straight_p){

				myQueue.push_back(new Vehicle(car_size, &west, &west, Vehicle::straight));
			}
			//turn right
			else{

				myQueue.push_back(new Vehicle(car_size, &west, &north, Vehicle::right));
			}


		}

		//function call to printLanes to print our lanes out 
		printLanes(north, south, east, west, size, NE, NW, SE, SW);


		/*
		Code for printing status of traffic signals
		*/
		cout << "NS Signal:";  
		mysignalNS.printCurrent();
		cout << endl;

		cout << "EW Signal:"; 
		mysignalEW.printCurrent(); 
		cout << endl;
		

		/*
		Code to update vehicles in our vector and proceed as necessary 
		*/
		for(int i = 0; i < myQueue.size(); i++){

			if (myQueue[i]->canProceed()==true){
				
				myQueue[i]->proceed();
			}
		}

		//update signal and intersections to represent 1 clock tick forward
		mysignalNS.updateTimeUntilNext();
		mysignalEW.updateTimeUntilNext();
		
		NE.updateTimeInUse();
		NW.updateTimeInUse();
		SE.updateTimeInUse();
		SW.updateTimeInUse();

		//print status of simulation at each clock tick
		cout << "Total No. of Cars Generated: " << myQueue.size() << endl;
		cout << "Current Clock Tick: " << j << endl;

		//set sleep timer at each iteration of loop to represent integer value clock
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	//delete all dynamically allocated vehicles 
	for(int i = 0; i < myQueue.size(); i++){

		delete myQueue[i];
	}

	return 0;
}
