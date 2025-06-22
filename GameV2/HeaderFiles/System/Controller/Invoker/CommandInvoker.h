#pragma once

#ifndef COMMAND_INVOKER_H
#define COMMAND_INVOKER_H

#include <vector>
#include <string>
#include "IInvoker.h"

class ICommand;

class CommandInvoker: public IInvoker {
public:
	CommandInvoker() ;
	~CommandInvoker() override ;
	CommandInvoker(const CommandInvoker& other);
	CommandInvoker& operator=(const CommandInvoker& other);

	void registerCommand(ICommand* cmd) override;
	void executeCommandLine(const std::string line) override;

private:
	std::vector<ICommand*> commands;
};

#endif
