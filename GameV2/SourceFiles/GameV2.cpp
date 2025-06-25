#include <iostream>
#include <vector>
#include <string>

#include "../HeaderFiles/App.h"

#include "../HeaderFiles/Communication/Loggers/ConsoleLogger.h"
#include "../HeaderFiles/Communication/UI/ConsoleUserInterface.h"
#include "../HeaderFiles/Communication/UI/RandomAIPlayer.h"
#include "../HeaderFiles/System/Services/Files/FileReading/BasicFileReader.h"



int main()
{
	TextFileReader textIO;
	ConsoleUI player1;
	ConsoleLogger logger;

	std::vector<std::string> commands;
	commands.push_back("botCommand1.");
	commands.push_back("botCommand2.");

	RandomUserInterface bot(commands);

	ConsoleUI player2; //Used for testing and examples.

	App app(player1, player2, logger,textIO);

	app.run();

}