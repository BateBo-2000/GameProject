#pragma once
#ifndef SAVE_COMMAND_H
#define SAVE_COMMAND_H

#include "../ICommand.h"
#include <vector>
#include <string>

class IGameSaveFileHandler;
class IUserInterface;
class IGameEngine;

class SaveCommand : public ICommand {
public:
    SaveCommand(IGameSaveFileHandler& handler, IUserInterface& ui, IGameEngine& gameEngine);
    ~SaveCommand() override = default;

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

#endif // SAVE_COMMAND_H