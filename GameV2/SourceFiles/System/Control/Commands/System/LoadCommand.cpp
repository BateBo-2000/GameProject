#include "../../HeaderFiles/System/Control/Commands/System/LoadCmd.h"

#include "../../HeaderFiles/Communication/UI/IUserInterFace.h"
#include "../../HeaderFiles/System/Services/SaveLoadFiles/ISaveLoadFile.h"
#include "../../HeaderFiles/System/GameEngine/IGameEngine.h"

LoadCommand::LoadCommand(IGameSaveFileHandler& handler, IUserInterface& ui, IGameEngine& gameEngine)
    : handler(handler), ui(ui), gameEngine(gameEngine)
{
}

ICommand* LoadCommand::clone() const {
    return new LoadCommand(*this);
}

bool LoadCommand::isThisMe(const std::vector<std::string>& args) const {
    return !args.empty() && args[0] == NAME;
}

bool LoadCommand::execute(const std::vector<std::string>& args) const {
    if (args.size() < 2) {
        ui.printInvalidArg("Usage: load <filepath>");
        return true;    // command recognized, but missing args
    }

    if (ui.confirm("Any unsaved progress will be lost!\Do you want to continoue?"))  return true;

    try {
        handler.loadFromFile(args[1], gameEngine.getGameState());
        ui.inform("Game loaded from " + args[1]);
        return true;
    }
    catch (const std::exception& e) {
        ui.error("Failed to load game: " + std::string(e.what()));
        return false;
    }
}

const std::string& LoadCommand::getDescription() const {
    return DESCRIPTION;
}

const std::string& LoadCommand::getName() const {
    return NAME;
}

static const std::string  NAME = "load";
static const std::string  DESCRIPTION = "Load a saved game state from a file: load <filepath>";