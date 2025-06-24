#include "../../HeaderFiles/System/Control/Commands/Other/StartCmd.h"
#include "../../HeaderFiles/System/GameEngine/IGameEngine.h"
#include "../../HeaderFiles/Communication/UI/IUserInterFace.h"

const std::string StartDuelCmd::NAME = "start";
const std::string StartDuelCmd::DESCRIPTION = "Start the duel after selecting units and a boss.";

StartDuelCmd::StartDuelCmd(IGameEngine& engine)
    : engine(engine)
{
}

ICommand* StartDuelCmd::clone() const {
    return new StartDuelCmd(*this);
}

bool StartDuelCmd::isThisMe(const std::vector<std::string>& args) const {
    return !args.empty() && args[0] == "start";
}

bool StartDuelCmd::execute(const std::vector<std::string>& args, IUserInterface& ui) const {
    if (args.size() != 1) {
        ui.error("Usage: start");
        return false;
    }

    try {
        engine.startDuel();
        ui.inform("Duel has started.");
        return true;
    }
    catch (const std::exception& ex) {
        ui.error("Failed to start duel: " + std::string(ex.what()));
        return false;
    }
}

const std::string& StartDuelCmd::getName() const {
    return NAME;
}

const std::string& StartDuelCmd::getDescription() const {
    return DESCRIPTION;
}
