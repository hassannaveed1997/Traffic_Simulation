//* Author: Dhiraj Amarnani, Hassan Naveed, Andre Koppert
//* Date: December 18 2017

#ifndef __random_h__
#define __random_h__

#include <random>

//*******************************************************************
//* 
//* This header file declares and implements the methods and data 
//* fields to be included in the Random class. The method 
//* randdouble01 generates a pseudo-random number between a pre-
//* specified bound. 
//* 
//*******************************************************************
class Random
{
   private:
     static std::mt19937 rng;
     static std::uniform_real_distribution<double> randdouble;

   public:
      inline static double  randdouble01() { return Random::randdouble(Random::rng); }
      //generates pseudo-random number between 0 and 1. 
      inline static double  randdouble01(int a, int b)
      {
         double u = Random::randdouble(Random::rng);
         double    mappedValue = a + ((b - a )*u);
         
         return(mappedValue);
      }

};

#endif