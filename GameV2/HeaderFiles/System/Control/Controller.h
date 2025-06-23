#pragma once

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "IController.h"
#include "Invoker/IInvoker.h"

//Comunication
class ILogger;
class IUserInterface;

class IInvoker;

class Controller: public IController {
public:
	Controller(ILogger& logger, IUserInterface& livingUi, IUserInterface& undeadUi, IInvoker& invoker);
	Controller(const Controller& other) = delete;
	Controller& operator=(const Controller& other) = delete;
	~Controller() override;

	virtual void run() override;
private:
	ILogger& logger;
	IUserInterface& livingUi;
	IUserInterface& undeadUi;
	IInvoker& invoker;
};

#endif //CONTROLLER_H
