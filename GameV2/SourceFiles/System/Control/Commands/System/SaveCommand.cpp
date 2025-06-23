#include "../../HeaderFiles/System/Control/Commands/System/SaveCmd.h"

#include "../../HeaderFiles/Communication/UI/IUserInterFace.h"
#include "../../HeaderFiles/System/Services/SaveLoadFiles/ISaveLoadFile.h"
#include "../../HeaderFiles/System/GameEngine/IGameEngine.h"

SaveCommand::SaveCommand(IGameSaveFileHandler& handler, IUserInterface& ui, IGameEngine& gameEngine)
    : handler(handler), ui(ui), gameEngine(gameEngine)
{
}

ICommand* SaveCommand::clone() const {
    return new SaveCommand(*this);
}

bool SaveCommand::isThisMe(const std::vector<std::string>& args) const {
    return !args.empty() && args[0] == NAME;
}

bool SaveCommand::execute(const std::vector<std::string>& args) const {

    if (args.size() < 2) {
        ui.printInvalidArg("Usage: save <filepath>");
        return false;
    }

    const std::string& filepath = args[1];

    try {
        handler.saveToFile(filepath, gameEngine.getGameState());
        ui.inform("Game saved to " + filepath);
        return true;
    }
    catch (const std::exception& ex) {
        ui.error(std::string("Failed to save game: ") + ex.what());
        return false;
    }
}

const std::string& SaveCommand::getDescription() const {
    return DESCRIPTION;
}

const std::string& SaveCommand::getName() const {
    return NAME;
}


static const std::string  NAME = "save";
static const std::string  DESCRIPTION = "Save the current game state to a file: save <filepath>";