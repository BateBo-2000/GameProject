#pragma once
#ifndef HELP_COMMAND_H
#define HELP_COMMAND_H

#include <vector>
#include <string>

#include "../ICommand.h"

class IUserInterface;
class IInvoker;

class HelpCmd : public ICommand {
public:
    HelpCmd(IUserInterface& ui, IInvoker& invoker);
    ~HelpCmd() override = default;

    bool isThisMe(const std::vector<std::string>& args) const override;
    bool execute(const std::vector<std::string>& args) const override;

    const std::string& getDescription() const;
    const std::string& getName() const override;

    virtual ICommand* clone() const override;
private:
    static const std::string NAME;
    static const std::string DESCRIPTION;

    IUserInterface& ui;
    IInvoker& invoker;
};

#endif // !HELP_COMMAND_H
