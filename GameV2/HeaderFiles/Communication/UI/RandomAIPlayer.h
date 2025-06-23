#pragma once

#include "IUserInterface.h"
#include <vector>
#include <string>

/**
  * This is "AIPLayer" acting as the computer.
  * just answers with random stuff
 */
class RandomUserInterface : public IUserInterface {
public:
    //list of commands for the askQuestion function
    RandomUserInterface(const std::vector<std::string>& commands);
    RandomUserInterface* clone() const override;

    void inform(const std::string& msg) const override;
    void warn(const std::string& msg) const override;
    void printInvalidArg(const std::string& msg) const override;
    bool confirm(const std::string& q) const override;
    int askForNumber(const std::string& q) const override;
    std::string askQuestion(const std::string& q) const override;

private:
    std::vector<std::string> commands;
};