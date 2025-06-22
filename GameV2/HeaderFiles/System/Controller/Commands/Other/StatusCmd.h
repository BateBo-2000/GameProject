#pragma once
#ifndef STATUS_COMMAND_H
#define STATUS_COMMAND_H

#include <vector>
#include <string>

#include "../ICommand.h"

class IUserInterface;

class StatusCmd : public ICommand {
public:
    StatusCmd(IUserInterface& ui);
    virtual bool isThisMe(const std::vector<std::string>& args) const override;
    virtual void execute(const std::vector<std::string>& args) const override;
    virtual ICommand* clone() const override;
private:
    static constexpr const char* myName = "status";
    IUserInterface& ui;
};

#endif // !STATUS_COMMAND_H
