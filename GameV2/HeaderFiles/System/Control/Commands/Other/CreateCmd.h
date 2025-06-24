#pragma once
#ifndef CREATE_UNIT_CMD_H
#define CREATE_UNIT_CMD_H

#include "../ICommand.h"
#include <string>
#include <vector>

class IGameEngine;
class IUserInterface;

class CreateUnitCmd : public ICommand {
public:
    CreateUnitCmd(IGameEngine& engine);
    ~CreateUnitCmd() override = default;

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

#endif // CREATE_UNIT_CMD_H
