#include <iostream>

#include "Random.h"

// let's define the static members in Random
std::mt19937 Random::rng(2); 
std::uniform_real_distribution<double> Random::randdouble(0,1);


using namespace std;

int main()
{
   for (int i = 0; i < 10; i++){
      cout << Random::randdouble01() << endl;
   }

   return 0;
}