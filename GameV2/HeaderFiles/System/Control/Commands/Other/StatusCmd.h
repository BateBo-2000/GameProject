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
    StatusCmd(IGameEngine& engine, IUserInterface& ui);
    ~StatusCmd() override = default;

    ICommand* clone() const override;

    bool isThisMe(const std::vector<std::string>& args) const override;
    bool execute(const std::vector<std::string>& args) const override;

    const std::string& getDescription() const override;
    const std::string& getName() const override;

private:
    static const std::string NAME;
    static const std::string DESCRIPTION;

    IGameEngine& engine;
    IUserInterface& ui;
};

#endif // STATUS_COMMAND_H
