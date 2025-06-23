#pragma once
#ifndef EXIT_COMMAND_H
#define EXIT_COMMAND_H

#include "../ICommand.h"
#include "../../HeaderFiles/System/Control/Invoker/IInvoker.h"
#include "../../HeaderFiles/Communication/UI/IUserInterFace.h"
#include <vector>
#include <string>

class ExitCommand : public ICommand {
public:
    ExitCommand(IInvoker& invoker, IUserInterface& ui);
    ~ExitCommand() override = default;
    bool isThisMe(const std::vector<std::string>& args) const override;
    bool execute(const std::vector<std::string>& args) const override;
    ICommand* clone() const override;
private:
    IUserInterface& ui;
    IInvoker& invoker;
};

#endif // EXIT_COMMAND_H