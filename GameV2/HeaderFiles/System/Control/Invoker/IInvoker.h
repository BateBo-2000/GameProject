#pragma once
#ifndef I_INVOKER_H
#define I_INVOKER_H

#include "../../HeaderFiles/System/Faction.h"

#include <string>
#include <vector>

class ICommand;
class IUserInterface;

class IInvoker {
public:
	virtual ~IInvoker() = default;
	virtual void registerCommand(ICommand* c) = 0;
	virtual bool executeCommandLine(const std::string& line, IUserInterface& executingPlayerUI) = 0;
	
	//used to get the description
	virtual const std::vector<ICommand*> getCommands() = 0; 

	virtual Faction getCurrentFaction() const = 0;
	virtual bool shouldExit() = 0;
	virtual void requestExit() = 0;

};


#endif // !I_INVOKER_H
