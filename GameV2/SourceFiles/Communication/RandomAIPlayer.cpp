#include "../../HeaderFiles/Communication/UI/RandomAIPlayer.h"

#include <cstdlib>
#include <ctime>

RandomUserInterface::RandomUserInterface(const std::vector<std::string>& commands)
    : commands(commands) {
    //seed the random generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

RandomUserInterface* RandomUserInterface::clone() const {
    return new RandomUserInterface(*this);
}

void RandomUserInterface::inform(const std::string& msg) const {
    (void)msg;  
    /*
        read in stack overflow that this is the way to tell the compiler that i know im not using them 
        https://stackoverflow.com/questions/7354786/what-does-void-variable-name-do-at-the-beginning-of-a-c-function    
    */
}

void RandomUserInterface::warn(const std::string& msg) const {
    (void)msg;
}

void RandomUserInterface::printInvalidArg(const std::string& msg) const {
    (void)msg;
}

void RandomUserInterface::error(const std::string& msg) const
{
    (void)msg;
}

bool RandomUserInterface::confirm(const std::string& q) const {
    (void)q;
    return (std::rand() % 2) == 0;
}

int RandomUserInterface::askForNumber(const std::string& q) const {
    (void)q;
    return std::rand() % 10; // numbers form 0 - 9
}

std::string RandomUserInterface::askQuestion(const std::string& q) const {
    (void)q;
    if (commands.empty()) return std::string();
    size_t index = static_cast<size_t>(std::rand()) % commands.size();
    return commands[index];
}