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