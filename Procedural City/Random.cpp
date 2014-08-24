#include "Random.h"

std::mt19937 Random::_randomEngine;

void Random::setSeed(std::mt19937::result_type s)
{
	_randomEngine.seed(s);
}

float Random::nextFloat(float min, float max)
{
	std::uniform_real_distribution<float> range(min, max);
	return range(_randomEngine);
}

float Random::nextFloat()
{
	return nextFloat(0, 1);
}

int Random::nextInt(int min, int max)
{
	std::uniform_int_distribution<int> range(min, max);
	return range(_randomEngine);
}