#pragma once

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "IController.h"

//Comunication
class ILogger;
class IUserInterface;

class IInvoker;

class Controller: public IController {
public:
	Controller(ILogger& logger, IUserInterface& ui);
	Controller(const Controller& other);
	Controller& operator=(const Controller& other);
	~Controller() override;

	virtual void run() override;
private:
	IInvoker* invoker;
	ILogger& logger;
	IUserInterface& ui;
};

#endif //CONTROLLER_H
