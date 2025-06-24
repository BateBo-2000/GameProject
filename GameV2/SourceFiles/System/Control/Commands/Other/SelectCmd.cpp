#include "../../HeaderFiles/System/Control/Commands/Other/SelectCmd.h"
#include "../../HeaderFiles/System/GameEngine/IGameEngine.h"
#include "../../HeaderFiles/Communication/UI/IUserInterFace.h"
#include <sstream>

const std::string SelectUnitsCmd::NAME = "select";
const std::string SelectUnitsCmd::DESCRIPTION = "Select units for the duel: select units <unitType> <count>";

SelectUnitsCmd::SelectUnitsCmd(IGameEngine& engine, IUserInterface& ui)
    : engine(engine), ui(ui)
{
}

ICommand* SelectUnitsCmd::clone() const {
    return new SelectUnitsCmd(*this);
}

bool SelectUnitsCmd::isThisMe(const std::vector<std::string>& args) const {
    return args.size() >= 2 && args[0] == "select" && args[1] != "boss";
}

bool SelectUnitsCmd::execute(const std::vector<std::string>& args) const {
    if (args.size() != 3) {
        ui.error("Usage: select <unitType> <count>");
        return false;
    }

    const std::string& unitType = args[1];
    unsigned count;

    try {
        count = std::stoul(args[2]);
    }
    catch (...) {
        ui.error("Invalid number: '" + args[2] + "'.");
        return false;
    }

    try {
        engine.selectUnits(unitType, count);
        ui.inform("Selected " + std::to_string(count) + " unit(s) of type '" + unitType + "'.");
        return true;
    }
    catch (const std::exception& ex) {
        ui.error("Failed to select units: " + std::string(ex.what()));
        return false;
    }
}

const std::string& SelectUnitsCmd::getName() const {
    return NAME;
}

const std::string& SelectUnitsCmd::getDescription() const {
    return DESCRIPTION;
}
