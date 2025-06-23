#include "../../HeaderFiles/Communication/Loggers/ConsoleLogger.h"

ConsoleLogger* ConsoleLogger::clone() const
{
	return new ConsoleLogger(*this);
}

void ConsoleLogger::log(const std::string& msg) {
	std::cout << "\033[0m[LOG] " << msg << "\033[0m" <<  std::endl;
}

void ConsoleLogger::warn(const std::string& msg) {
	std::cout << "\033[33m[WARN] " << msg << "\033[0m" << std::endl;
}

void ConsoleLogger::error(const std::string& msg) {
	std::cerr << "\033[31m[ERROR] " << msg << "\033[0m" << std::endl;
}
