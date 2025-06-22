#pragma once
#ifndef CREATE_COMMAND_H
#define CREATE_COMMAND_H

#include <vector>
#include <string>

#include "../ICommand.h"

class IUserInterface;

class CreateCmd : public ICommand {
public:
    CreateCmd(IUserInterface& ui);
    virtual bool isThisMe(const std::vector<std::string>& args) const override;
    virtual void execute(const std::vector<std::string>& args) const override;
    virtual ICommand* clone() const override;
private:
    static constexpr const char* myName = "create";
    IUserInterface& ui;
};

#endif // !CREATE_COMMAND_H
