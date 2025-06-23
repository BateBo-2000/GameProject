#include "../../HeaderFiles/System/Control/Commands/System/RestartCmd.h"

#include "../../HeaderFiles/Communication/UI/IUserInterFace.h"
#include "../../HeaderFiles/System/Services/SaveLoadFiles/ISaveLoadFile.h"
#include "../../HeaderFiles/System/GameEngine/IGameEngine.h"

RestartCommand::RestartCommand(IGameEngine& engine, IUserInterface& ui)
    : gameEngine(engine)
    , ui(ui)
{
}

ICommand* RestartCommand::clone() const {
    return new RestartCommand(*this);
}

bool RestartCommand::isThisMe(const std::vector<std::string>& args) const {
    return !args.empty() && args[0] == NAME;
}

bool RestartCommand::execute(const std::vector<std::string>& args) const {
    if (args.size() != 1) {
        ui.printInvalidArg("Usage: restart");
        return true;
    }

    if (!ui.confirm("Are you sure you want to restart?\nAll progress in the current game will be lost.")) {
        return true;
    }

    try
    {
        gameEngine.restartTheGame();
        ui.inform("Game has been restarted.");
    }
    catch (const std::exception& e)
    {
        ui.error(string("Game restart failed:\n") + e.what());
    }

   
    return true;
}

const std::string& RestartCommand::getDescription() const {
    return DESCRIPTION;
}

const std::string& RestartCommand::getName() const {
    return NAME;
}

static const std::string  NAME = "restart";
static const std::string  DESCRIPTION = "Restarts the whole game from scratch. Wipes all progress.";