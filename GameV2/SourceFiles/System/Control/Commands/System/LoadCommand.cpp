#include "../../HeaderFiles/System/Control/Commands/System/LoadCmd.h"

#include "../../HeaderFiles/Communication/UI/IUserInterFace.h"
#include "../../HeaderFiles/System/GameEngine/IGameEngine.h"

LoadCommand::LoadCommand(IGameEngine& gameEngine, IUserInterface& adminPlayer)
    :gameEngine(gameEngine), adminUI(adminPlayer)
{
}

ICommand* LoadCommand::clone() const {
    return new LoadCommand(*this);
}

bool LoadCommand::isThisMe(const std::vector<std::string>& args) const {
    return !args.empty() && args[0] == NAME;
}

bool LoadCommand::execute(const std::vector<std::string>& args, IUserInterface& ui) const {
    if (&ui != &adminUI) {
        ui.inform("You dont have administrator privileges.");
        return false;
    }

    if (args.size() < 2) {
        ui.printInvalidArg("Usage: load <filepath>");
        return false;
    }

    if (!ui.confirm("Any unsaved progress will be lost!\nDo you want to continue?"))  return true;

    if (gameEngine.loadTheGameFromFile(args[1])) {
        ui.inform("Game loaded from " + args[1]);
        return true;
    }
    else {
        ui.error("Failed to load game.");
        return false;
    }
}

const std::string& LoadCommand::getDescription() const {
    return DESCRIPTION;
}

const std::string& LoadCommand::getName() const {
    return NAME;
}

const std::string  LoadCommand::NAME = "load";
const std::string  LoadCommand::DESCRIPTION = "Load a saved game state from a file: load <filepath>";