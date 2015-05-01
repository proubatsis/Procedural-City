/*
	Created by Panagiotis Roubatsis
	Description: Generates a population map to determine what types
	of tiles/buildings will be put in what part of the city.
*/

#ifndef POPULATION_MAP_H
#define POPULATION_MAP_H

#include <vector>

namespace Procedural
{
	namespace Map
	{
		//Generates a population map using 2-Dimensional perlin noise
		std::vector<std::vector<float> > generatePopulationMap(const int& width, const int& height);
	};
};

#endif