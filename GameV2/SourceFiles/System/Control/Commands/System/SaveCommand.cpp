#include "../../HeaderFiles/System/Control/Commands/System/SaveCmd.h"

#include "../../HeaderFiles/Communication/UI/IUserInterFace.h"
#include "../../HeaderFiles/System/GameEngine/IGameEngine.h"

SaveCommand::SaveCommand(IGameEngine& gameEngine, IUserInterface& adminPlayer)
    :gameEngine(gameEngine), adminUI(adminPlayer)
{
}

ICommand* SaveCommand::clone() const {
    return new SaveCommand(*this);
}

bool SaveCommand::isThisMe(const std::vector<std::string>& args) const {
    return !args.empty() && args[0] == NAME;
}

bool SaveCommand::execute(const std::vector<std::string>& args, IUserInterface& ui) const {

    if (&ui != &adminUI) {
        ui.inform("You dont have administrator privileges.");
        return false;
    }

    std::string filepath;

    if (args.size() < 2) {
        filepath = "";
    }
    else {
        filepath = args[1];
    }

    if (gameEngine.saveTheGameToFile(filepath)) {
        ui.inform("Game saved to " + (filepath.empty()? string("the same location."): filepath));
        return true;
    }
    else {
        ui.error(std::string("Failed to save game."));
        return false;
    }
}

const std::string& SaveCommand::getDescription() const {
    return DESCRIPTION;
}

const std::string& SaveCommand::getName() const {
    return NAME;
}


const std::string  SaveCommand::NAME = "save";
const std::string  SaveCommand::DESCRIPTION = "Save the current game state to a file: save <filepath>";