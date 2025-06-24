#pragma once
#ifndef RESTART_COMMAND_H
#define RESTART_COMMAND_H

#include "../ICommand.h"
#include <vector>
#include <string>

class IGameEngine;
class IUserInterface;


class RestartCommand : public ICommand {
public:
    RestartCommand(IGameEngine& engine, IUserInterface& adminPlayer);
    ~RestartCommand() override = default;

    ICommand* clone() const override;

    bool isThisMe(const std::vector<std::string>& args) const override;
    bool execute(const std::vector<std::string>& args, IUserInterface& ui) const override;

    const std::string& getDescription() const override;
    const std::string& getName() const override;

private:
    static const std::string NAME;
    static const std::string DESCRIPTION;

    IGameEngine& gameEngine;
    IUserInterface& adminUI;
};

#endif // RESTART_COMMAND_H