#include <iostream>

#include "Random.h"

// let's define the static members in Random
std::mt19937 Random::rng(8675309);
std::uniform_real_distribution<double> Random::randdouble(0.0,1.0);


int main()
{
   for (int i = 0; i < 1000000; i++)
      std::cout << Random::randdouble01(0,1) << std::endl;

   return 0;
}