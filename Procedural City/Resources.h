/*
	Created by Panagiotis Roubatsis
	Description: Loads external resources.
*/

#ifndef RESOURCES_H
#define RESOURCES_H

#include <iostream>

class Resources
{
public:
	static std::string getTextFileAsString(std::string fileName);
};

#endif