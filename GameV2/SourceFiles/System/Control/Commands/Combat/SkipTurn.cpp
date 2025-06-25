#include "../../HeaderFiles/System/Control/Commands/Combat/SkipTurnCmd.h"

#include "../../HeaderFiles/Communication/UI/IUserInterFace.h"
#include "../../HeaderFiles/System/GameEngine/IGameEngine.h"


SkipTurnCmd::SkipTurnCmd(IGameEngine& engine)
    : engine(engine)
{
}

ICommand* SkipTurnCmd::clone() const {
    return new SkipTurnCmd(*this);
}

bool SkipTurnCmd::isThisMe(const std::vector<std::string>& args) const {
    // allow either "skip" or "skip turn"
    return !args.empty() && args[0] == "skip" && (args.size() == 1 || (args.size() > 1 && args[1] == "turn"));
}

bool SkipTurnCmd::execute(const std::vector<std::string>& args, IUserInterface& ui) const {

    if (args.size() > 2) {
        ui.error("Usage: 'skip turn' with no arguments");
        return false;
    }

    try {
        engine.skipTurn();
        ui.inform("Turn skipped.");
        return true;
    }
    catch (const std::exception& e) {
        ui.error("Failed to skip turn: " + std::string(e.what()));
        return false;
    }
}

const std::string& SkipTurnCmd::getName() const {
    return NAME;
}

const std::string& SkipTurnCmd::getDescription() const {
    return DESCRIPTION;
}

const std::string SkipTurnCmd::NAME = "skip turn";
const std::string SkipTurnCmd::DESCRIPTION = "Skip the current unit's turn and advance to the next.";
