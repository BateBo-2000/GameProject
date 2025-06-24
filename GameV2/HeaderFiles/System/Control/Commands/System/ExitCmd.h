    #pragma once
#ifndef EXIT_COMMAND_H
#define EXIT_COMMAND_H

#include "../ICommand.h"

#include <vector>
#include <string>

class IInvoker;
class IUserInterface;

class ExitCommand : public ICommand {
public:
    ExitCommand(IInvoker& invoker, IUserInterface& adminPlayer);
    ~ExitCommand() override = default;
    ICommand* clone() const override;

    bool isThisMe(const std::vector<std::string>& args) const override;
    bool execute(const std::vector<std::string>& args, IUserInterface& ui) const override;

    const std::string& getDescription() const override;
    const std::string& getName() const override;

private:
    static const std::string NAME;
    static const std::string DESCRIPTION;

    IInvoker& invoker;
    IUserInterface& adminUI;
};

#endif // EXIT_COMMAND_H