#ifndef __random_h__
#define __random_h__

#include <random>

class Random
{
   protected:
     static std::mt19937 rng;
     static std::uniform_real_distribution<double> randdouble;

   public:
      inline static double  randdouble01() { return Random::randdouble(Random::rng); }
      inline static double  randdouble01(int a, int b)
      {
         double u = Random::randdouble(Random::rng);
         double    mappedValue = a + ((b - a )*u);
         return(mappedValue);
      }
};

// static members must be defined @ file-level scope

#endif