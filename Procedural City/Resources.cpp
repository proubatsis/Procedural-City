#include "Resources.h"
#include <fstream>

std::string Resources::getTextFileAsString(std::string fileName)
{
	std::ifstream file(fileName);

	std::string fileContents(
			std::istreambuf_iterator<char>(file),
			(std::istreambuf_iterator<char>())
		);

	file.close();

	return fileContents;
}