#include "../../HeaderFiles/System/Control/Commands/Other/CreateCmd.h"
#include "../../HeaderFiles/System/GameEngine/IGameEngine.h"
#include "../../HeaderFiles/Communication/UI/IUserInterFace.h"

CreateUnitCmd::CreateUnitCmd(IGameEngine& engine, IUserInterface& ui)
    : engine(engine), ui(ui)
{
}

ICommand* CreateUnitCmd::clone() const {
    return new CreateUnitCmd(*this);
}

bool CreateUnitCmd::isThisMe(const std::vector<std::string>& args) const {
    return !args.empty() && args[0] == NAME;
}

bool CreateUnitCmd::execute(const std::vector<std::string>& args) const {
    if (args.size() != 2) {
        ui.error("Usage: create <unitType>");
        return false;
    }

    const std::string& unitType = args[1];

    try {
        engine.create(unitType);
        ui.inform("Unit '" + unitType + "' created.");
        return true;
    }
    catch (const std::exception& ex) {
        ui.error("Failed to create unit: " + std::string(ex.what()));
        return false;
    }
}

const std::string& CreateUnitCmd::getName() const {
    return NAME;
}

const std::string& CreateUnitCmd::getDescription() const {
    return DESCRIPTION;
}

const std::string CreateUnitCmd::NAME = "create";
const std::string CreateUnitCmd::DESCRIPTION = "Create a new unit for the player: create <unitType>";