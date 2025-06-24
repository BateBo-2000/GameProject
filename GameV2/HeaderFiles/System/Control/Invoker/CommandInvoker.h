#pragma once
#ifndef COMMAND_INVOKER_H
#define COMMAND_INVOKER_H

#include <vector>
#include <string>
#include "IInvoker.h"



class ICommand;
class IGameEngine;

class CommandInvoker : public IInvoker {
public:
    CommandInvoker(IGameEngine& engine);
    CommandInvoker(const CommandInvoker& other);
    CommandInvoker& operator=(const CommandInvoker& other);
    ~CommandInvoker() override;

    void registerCommand(ICommand* c) override; //takes ownership
    bool executeCommandLine(const std::string& line, IUserInterface& executingPlayerUI) override;

    const std::vector<ICommand*> getCommands() override;

    Faction getCurrentFaction() const override;
    bool shouldExit() override;
    void requestExit() override;
private:
    std::vector<ICommand*> commands;
    IGameEngine& receiver;
    bool exitRequested;
};

#endif // COMMAND_INVOKER_H