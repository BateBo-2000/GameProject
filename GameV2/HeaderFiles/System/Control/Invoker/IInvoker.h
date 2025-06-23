#pragma once
#ifndef I_INVOKER_H
#define I_INVOKER_H

#include "../../HeaderFiles/System/Faction.h"

#include <string>

class ICommand;


class IInvoker {
public:
	virtual ~IInvoker() = default;
	virtual void registerCommand(ICommand* c) = 0;
	virtual bool executeCommandLine(const std::string& line) = 0;
	virtual Faction getCurrentFaction() const = 0;
	virtual bool shouldExit() = 0;
	virtual void requestExit() = 0;
};


#endif // !I_INVOKER_H
