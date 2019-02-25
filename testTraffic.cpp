#include <iostream>
#include "TrafficSignal.h"

using namespace std;

int main(){

	TrafficSignal* test = new TrafficSignal(3,3,3, 'G');

	for(int i = 0; i < 10; ++i){

		test -> printCurrent();
		test -> updateTimeUntilNext();
	}


	delete test;
	return 0;
}