#include <iostream>

#include "../../HeaderFiles/System/Services/Files/FileReading/BasicFileReader.h"

int main()
{
	TextFileReader file("C:/Users/boian/source/repos/GameV2/GameV2/Game.config");
	std::string fileContents; 
	file.readFileContents(fileContents);
	std::cout << fileContents;
}