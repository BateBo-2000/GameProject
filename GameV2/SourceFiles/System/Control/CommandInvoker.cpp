#include "../../HeaderFiles/System/Control/Invoker/CommandInvoker.h"

#include "../../HeaderFiles/Util/Split.h"
#include "../../HeaderFiles/System/Control/Commands/ICommand.h"
#include "../../HeaderFiles/System/GameEngine/IGameEngine.h"
#include "../../HeaderFiles/Communication/UI/IUserInterFace.h"

#include <stdexcept>

CommandInvoker::CommandInvoker(IGameEngine& engine):receiver(engine), exitRequested(false) {}

CommandInvoker::CommandInvoker(const CommandInvoker& other) :receiver(other.receiver), exitRequested(other.exitRequested) {
    for (size_t i = 0; i < other.commands.size(); ++i) {
        commands.push_back(other.commands[i]->clone());
    }
}
CommandInvoker& CommandInvoker::operator=(const CommandInvoker& other) {
    if (this != &other) {
        std::vector<ICommand*> temp;

        for (size_t i = 0; i < other.commands.size(); ++i) {
            temp.push_back(other.commands[i]->clone());
        }

        for (size_t i = 0; i < this->commands.size(); ++i) {
            delete this->commands[i];
        }
        this->commands.clear();
        this->commands = std::move(temp);
        this->receiver = other.receiver;
    }
    return *this;
}

CommandInvoker::~CommandInvoker() {
    for (size_t i = 0; i < commands.size(); ++i) {
        delete commands[i];
    }
    commands.clear();
}

void CommandInvoker::registerCommand(ICommand* c) { 
    if (!c) return;

    for (size_t i = 0; i < commands.size(); i++)
    {
        if (commands[i]->getName() == c->getName()) {
            std::string name = c->getName();
            delete c;
            throw std::invalid_argument("Command " + name + " is already registered!");
        }
            
    }
    commands.push_back(c);
}

bool CommandInvoker::executeCommandLine(const std::string& line, IUserInterface& executingPlayerUI) {
    std::vector<std::string> args = split(line, ' ');
    
    if (args.empty()) {
        return false;
    }

    for (size_t i = 0; i < commands.size(); ++i) {
        if (commands[i]->isThisMe(args)) {
            return commands[i]->execute(args, executingPlayerUI);
        }
    }
    throw std::runtime_error("Unknown command: " + args[0]);
    return false;
}

const std::vector<ICommand*> CommandInvoker::getCommands()
{
    return commands;
}

Faction CommandInvoker::getCurrentFaction() const {
    return receiver.getWhoseTurnItIsNow();
}

bool CommandInvoker::shouldExit()
{
    return exitRequested;
}

void CommandInvoker::requestExit()
{
    exitRequested = true;
}
