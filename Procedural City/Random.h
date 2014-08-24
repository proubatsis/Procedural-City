#ifndef RANDOM_H
#define RANDOM_H

#include <random>

//Encapsulate <random> specialized for
//this game. Given a seed the same city
//should be generated.
class Random
{
private:
	static std::mt19937 _randomEngine;

public:
	//Sets the seed to use. Only call at the
	//start of the application.
	static void setSeed(std::mt19937::result_type s);

	//Returns a random float within the
	//given range.
	static float nextFloat(float min, float max);

	//Returns a random float between 0 and 1.
	static float nextFloat();

	//Returns a random integer within
	//given range.
	static int nextInt(int min, int max);
};

#endif