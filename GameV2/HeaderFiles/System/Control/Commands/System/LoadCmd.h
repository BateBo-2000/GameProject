#pragma once
#ifndef LOAD_COMMAND_H
#define LOAD_COMMAND_H

#include "../ICommand.h"
#include <vector>
#include <string>

class IGameSaveFileHandler;
class IUserInterface;
class IGameEngine;

class LoadCommand : public ICommand {
public:
    LoadCommand(IGameSaveFileHandler& handler, IUserInterface& ui, IGameEngine& gameEngine);
    ~LoadCommand() override = default;

    ICommand* clone() const override;

    bool isThisMe(const std::vector<std::string>& args) const override;
    bool execute(const std::vector<std::string>& args) const override;

    const std::string& getDescription() const override;
    const std::string& getName() const override;

private:
    static const std::string NAME;
    static const std::string DESCRIPTION;

    IGameSaveFileHandler& handler;
    IUserInterface& ui;
    IGameEngine& gameEngine;
};

#endif // LOAD_COMMAND_H