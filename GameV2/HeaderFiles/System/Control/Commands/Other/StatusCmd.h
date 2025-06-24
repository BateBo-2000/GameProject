#pragma once
#ifndef STATUS_COMMAND_H
#define STATUS_COMMAND_H

#include "../ICommand.h"
#include <string>
#include <vector>

class IGameEngine;
class IUserInterface;

class StatusCmd : public ICommand {
public:
    StatusCmd(IGameEngine& engine);
    ~StatusCmd() override = default;

    ICommand* clone() const override;

    bool isThisMe(const std::vector<std::string>& args) const override;
    bool execute(const std::vector<std::string>& args, IUserInterface& ui) const override;

    const std::string& getDescription() const override;
    const std::string& getName() const override;

private:
    static const std::string NAME;
    static const std::string DESCRIPTION;

    IGameEngine& engine;
};

#endif // STATUS_COMMAND_H
