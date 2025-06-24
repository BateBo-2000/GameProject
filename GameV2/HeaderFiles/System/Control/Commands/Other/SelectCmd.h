#pragma once
#ifndef SELECT_UNITS_CMD_H
#define SELECT_UNITS_CMD_H

#include "../ICommand.h"
#include <string>
#include <vector>

class IGameEngine;
class IUserInterface;

class SelectUnitsCmd : public ICommand {
public:
    SelectUnitsCmd(IGameEngine& engine);
    ~SelectUnitsCmd() override = default;

    ICommand* clone() const override;

    bool isThisMe(const std::vector<std::string>& args) const override;
    bool execute(const std::vector<std::string>& args, IUserInterface& ui) const override;

    const std::string& getName() const override;
    const std::string& getDescription() const override;

private:
    static const std::string NAME;
    static const std::string DESCRIPTION;

    IGameEngine& engine;
};

#endif // SELECT_UNITS_CMD_H
