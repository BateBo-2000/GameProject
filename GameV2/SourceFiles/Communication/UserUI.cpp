#include "../../HeaderFiles/Communication/UI/ConsoleUserInterface.h"

ConsoleUI* ConsoleUI::clone() const
{
	return new ConsoleUI(*this);
}

void ConsoleUI::inform(const string& msg) const
{
	std::cout << "\033[36m[INFO] " << msg << "\033[0m" << std::endl;
}

void ConsoleUI::warn(const string& msg) const
{
	std::cout << "\033[33m[WARNING] " << msg << "\033[0m" << std::endl;
}

void ConsoleUI::printInvalidArg(const string& msg) const
{
	std::cout << "\033[31m[INVALID] " << msg << "\033[0m" << std::endl;
}

void ConsoleUI::error(const std::string& msg) const
{
	std::cout << "\033[31m[ERROR] " << msg << "\033[0m" << std::endl;
}

bool ConsoleUI::confirm(const string& q) const
{
	std::cout << "\033[35m[CONFIRM]\033[0m " << q << " (y/n): ";
	char input;
	std::cin >> input;
	std::cin.ignore();
	return input == 'y' || input == 'Y' || input == '1';
}

int ConsoleUI::askForNumber(const string& q) const
{
	std::cout << "\033[32m[INPUT/NUM]\033[0m " << q << " ";
	int number;
	std::cin >> number;
	std::cin.ignore();
	return number;
}

string ConsoleUI::askQuestion(const string& q) const 
{
	std::cout << "\033[32m[INPUT/TEXT]\033[0m " << q << " ";
	std::string input;
	std::getline(std::cin, input);
	return input;
}
