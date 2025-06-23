#pragma once
#ifndef SELECT_COMMAND_H
#define SELECT_COMMAND_H

#include <vector>
#include <string>

#include "../ICommand.h"

class IUserInterface;

class SelectCmd : public ICommand {
public:
    SelectCmd(IUserInterface& ui);
    virtual bool isThisMe(const std::vector<std::string>& args) const override;
    virtual void execute(const std::vector<std::string>& args) const override;
    virtual ICommand* clone() const override;
private:
    static constexpr const char* myName = "select";
    IUserInterface& ui;
};

#endif // !SELECT_COMMAND_H
