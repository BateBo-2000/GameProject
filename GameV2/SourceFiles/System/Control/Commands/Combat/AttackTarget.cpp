#include "../../HeaderFiles/System/Control/Commands/Combat/AttackTargetCmd.h"

#include "../../HeaderFiles/Communication/UI/IUserInterFace.h"
#include "../../HeaderFiles/System/GameEngine/IGameEngine.h"


AttackTargetCmd::AttackTargetCmd(IGameEngine& engine)
    : engine(engine)
{
}

ICommand* AttackTargetCmd::clone() const {
    return new AttackTargetCmd(*this);
}

bool AttackTargetCmd::isThisMe(const std::vector<std::string>& args) const {
    if (args.empty() || args[0] != std::string(NAME)) return false;
    // allow "attack <name>" or "attack target <name>"
    return args.size() >= 2 &&
        (args.size() == 2 || (args.size() > 2 && args[1] == "target"));
}

bool AttackTargetCmd::execute(const std::vector<std::string>& args, IUserInterface& ui) const {
    if (args.size() != 2 && args.size() != 3 ) {
        ui.error("Usage: attack <name> or attack target <name>");
        return true;
    }

    const std::string& target = (args.size() > 2) ? args[2] : args[1];

    try {
        engine.attackTarget(target);
        ui.inform("Attacked " + target + ".");
        return true;
    }
    catch (const std::exception& ex) {
        ui.error("Attack failed: " + std::string(ex.what()));
        return false;
    }
}

const std::string& AttackTargetCmd::getName() const {
    return NAME;
}

const std::string& AttackTargetCmd::getDescription() const {
    return DESCRIPTION;
}

const std::string  AttackTargetCmd::NAME = "attack";
const std::string  AttackTargetCmd::DESCRIPTION = "Attack a named enemy: attack <name> or attack target <name>.";