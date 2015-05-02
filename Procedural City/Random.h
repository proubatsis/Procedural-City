/*
    Copyright (C) 2015 Panagiotis Roubatsis

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

/*
	Created by Panagiotis Roubatsis
	Description: Uses the built in mersenne twister
	random number generator. It allows you to set a seed,
	generate a floating point number, or generate an integer.
*/

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