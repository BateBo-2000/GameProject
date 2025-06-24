#include "../../HeaderFiles/System/Control/Commands/System/RestartCmd.h"

#include "../../HeaderFiles/Communication/UI/IUserInterFace.h"
#include "../../HeaderFiles/System/GameEngine/IGameEngine.h"

RestartCommand::RestartCommand(IGameEngine& engine, IUserInterface& adminPlayer)
    : gameEngine(engine), adminUI(adminPlayer)
{
}

ICommand* RestartCommand::clone() const {
    return new RestartCommand(*this);
}

bool RestartCommand::isThisMe(const std::vector<std::string>& args) const {
    return !args.empty() && args[0] == NAME;
}

bool RestartCommand::execute(const std::vector<std::string>& args, IUserInterface& ui) const {

    if (&ui != &adminUI) {
        ui.inform("You don't have administrator privileges.");
        return false;
    }

    if (args.size() != 1) {
        ui.printInvalidArg("Usage: restart");
        return true;
    }

    if (!ui.confirm("Are you sure you want to restart?\nAll progress in the current game will be lost.")) {
        return true;
    }


    if (gameEngine.restartWipeTheGame()) {
        ui.inform("Game restarted.");
        return true;
    }
    else {
        ui.error("Game restart failed.");
        return false;
    }
}

const std::string& RestartCommand::getDescription() const {
    return DESCRIPTION;
}

const std::string& RestartCommand::getName() const {
    return NAME;
}

const std::string  RestartCommand::NAME = "restart";
const std::string  RestartCommand::DESCRIPTION = "Restarts the whole game from scratch. Wipes all progress.";