#pragma once

#ifndef I_CONTROLLER
#define I_CONTROLLER

class IUserInterface;
class ILogger;

class IController {
public:
	virtual ~IController() = default;

	virtual void run() = 0;

};


#endif // !I_CONTROLLER