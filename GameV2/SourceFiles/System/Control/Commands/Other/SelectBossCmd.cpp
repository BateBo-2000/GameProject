#include "../../HeaderFiles/System/Control/Commands/Other/SelectBossCmd.h"
#include "../../HeaderFiles/System/GameEngine/IGameEngine.h"
#include "../../HeaderFiles/Communication/UI/IUserInterFace.h"

SelectBossCmd::SelectBossCmd(IGameEngine& engine)
    : engine(engine)
{
}

ICommand* SelectBossCmd::clone() const {
    return new SelectBossCmd(*this);
}

bool SelectBossCmd::isThisMe(const std::vector<std::string>& args) const {
    return args.size() >= 2 && args[0] == "select" && args[1] == "boss";
}

bool SelectBossCmd::execute(const std::vector<std::string>& args, IUserInterface& ui) const {
    if (args.size() != 3) {
        ui.error("Usage: select boss <bossType>");
        return false;
    }

    const std::string& bossType = args[2];

    try {
        engine.selectBoss(bossType);
        ui.inform("Boss '" + bossType + "' selected.");
        return true;
    }
    catch (const std::exception& ex) {
        ui.error("Failed to select boss: " + std::string(ex.what()));
        return false;
    }
}

const std::string& SelectBossCmd::getName() const {
    return NAME;
}

const std::string& SelectBossCmd::getDescription() const {
    return DESCRIPTION;
}

const std::string SelectBossCmd::NAME = "select boss";
const std::string SelectBossCmd::DESCRIPTION = "Select a boss for the duel: select boss <bossType>";